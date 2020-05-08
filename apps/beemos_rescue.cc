// Copyright (c) 2020 [Sue Wee]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/audio/audio.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include <iostream>
#include "beemos_rescue.h"
#include <mylibrary/playing_field.h>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::TextBox;
using cinder::ColorA;
using std::string;

const size_t kTilePixelLength = 64;
const size_t kPlayingFieldTileWidth = 12;
const size_t kPlayingFieldTileHeight = 8;
const size_t kTextTileHeight = 4;
const size_t kDescriptionTileWidth = 7;
const size_t kInventoryTileWidth = 2;
const size_t kStatsTileWidth = 3;

const string kUp = "up";
const string kDown = "down";
const string kLeft = "left";
const string kRight = "right";

bool is_action_queued = false;
size_t total_ammo_available;
ci::audio::VoiceRef background_music;

GameEngine::GameEngine() {
    game_state = GameState::kTitle;
}

void GameEngine::setup() {
    ci::app::setWindowSize(kPlayingFieldTileWidth * kTilePixelLength,
                           (kPlayingFieldTileHeight + kTextTileHeight) * kTilePixelLength);
    scene_one = mylibrary::PlayingField("stage_one.txt", kTilePixelLength, kPlayingFieldTileWidth, kPlayingFieldTileHeight);
    scene_two = mylibrary::PlayingField("stage_two.txt", kTilePixelLength, kPlayingFieldTileWidth, kPlayingFieldTileHeight);
    current_scene = scene_one;
    beemo = mylibrary::Character(1,8,64,"beemo/beemo right.gif");
    total_ammo_available = scene_one.GetAmmoCount() + scene_two.GetAmmoCount();

    ci::audio::SourceFileRef sourceFile = ci::audio::load( ci::app::loadAsset( "teemo i love you.mp3"));
    background_music = ci::audio::Voice::create(sourceFile);
    background_music->start();
}

void GameEngine::update() {
    if (is_action_queued) {
        if (game_state == GameState::kDealDamage) {
            current_scene.DealBossDamage(beemo.GetTotalAP());
        } else if (game_state == GameState::kTakeDamage && current_scene.GetFinalBoss().GetCurrentHealth() != 0) {
            beemo.TakeDamage(current_scene.GetFinalBoss().GetDamage());
        }
        is_action_queued = false;
    }
    if (game_state == GameState::kPlaying) {
        if (current_scene.GetFinalBoss().GetCurrentHealth() != 0 && total_ammo_available == 0) {
            game_state = GameState::kOutOfAmmo;
        }
        if (beemo.GetCurrentHP() == 0) {
            game_state = GameState::kOutOfHealth;
        }
    }
}

void GameEngine::draw() {
    if (game_state == GameState::kTitle) {
        DrawTitleScreen();
    } else if (game_state == GameState::kInstructions) {
        DrawIntroduction();
    } else if (game_state == GameState::kPlaying) {
        DrawCurrentScene();
    } else if (game_state == GameState::kDealDamage) {
        DrawCurrentScene();
    } else if (game_state == GameState::kTakeDamage) {
        if (current_scene.GetFinalBoss().GetCurrentHealth() == 0) {
            game_state = GameState::kPlaying;
        } else {
            DrawCurrentScene();
        }
    }
    if (game_state == GameState::kGameWon || game_state == GameState::kOutOfHealth ||
        game_state == GameState::kOutOfAmmo) {
        DrawEndScreen();
    }
}

void GameEngine::keyDown(KeyEvent event) {
    if (event.getCode() == KeyEvent::KEY_m) {
        if (background_music->isPlaying()) {
            background_music->stop();
        } else {
            background_music->start();
        }
    }
    if (game_state == GameState::kTitle) {
        if (event.getCode() == KeyEvent::KEY_SPACE || event.getCode() == KeyEvent::KEY_e) {
            game_state = GameState::kInstructions;
        }
    } else if (game_state == GameState::kInstructions) {
        if (event.getCode() == KeyEvent::KEY_SPACE || event.getCode() == KeyEvent::KEY_e) {
            game_state = GameState::kPlaying;
        }
    } else if (game_state == GameState::kDealDamage) {
        if (event.getCode() == KeyEvent::KEY_SPACE || event.getCode() == KeyEvent::KEY_e) {
            is_action_queued = true;
            beemo.SetImage(beemo.GetOrientation());
            current_scene.SetBossAttackMode();
            game_state = GameState::kTakeDamage;
        }
    } else if (game_state == GameState::kTakeDamage) {
        if (event.getCode() == KeyEvent::KEY_SPACE || event.getCode() == KeyEvent::KEY_e) {
            current_scene.SetBossDefaultMode();
            game_state = GameState::kPlaying;
        }
    } else if (game_state == GameState::kPlaying) {
        GetPlayingStateResponse(event);
    }
}

void GameEngine::DrawCurrentScene() {
    cinder::gl::clear();
    DrawDescription();
    DrawInventory();
    DrawStats();
    current_scene.draw();
    beemo.GetImage()->draw(beemo.GetXStartPixel(),beemo.GetYStartPixel(),
                           beemo.GetXEndPixel(), beemo.GetYEndPixel());
}

void GameEngine::DrawIntroduction() {
    ci::gl::clear();
    const size_t font_height = 30;
    const cinder::ivec2 size = {kPlayingFieldTileWidth * kTilePixelLength,
                                (kTextTileHeight + kPlayingFieldTileHeight) * kTilePixelLength};
    const Color color = Color::white();
    string text_to_print("INSTRUCTIONS"
                         "\n\n You are playing as BEEMO, the cute little League of Legends champion."
                         "\n\n You are on a mission to save your good friend, a PORO! In order to defeat the game, "
                         "you must defeat the NEXUS TURRET."
                         "\n\n You can collect items that are hidden on the map for special buffs. Once you pick up "
                         "an item, you cannot drop it. And remember, you only have a maximum of 6 item slots. "
                         "Defeating MINIONS will reveal items with stronger buffs than those hidden elsewhere. "
                         "However, choose wisely, because if you expend all your BEES on the MINIONS, you will not "
                         "have enough to fight the NEXUS TURRET in the end."
                         "\n\n Use [WASD] or the [ARROW KEYS] to move. Use [SPACE] or [Q] to attack or uncover "
                         "objects, and [SPACE] or [E] to add objects to your inventory. Press [M] to start/stop the music."
                         "\n\n\nAre you ready to begin your adventures?"
                         "\nPress [SPACE] or [E] to start.");
    const cinder::vec2 top_left_point = {0,0};
    DrawTextBox(font_height, size, color, text_to_print, top_left_point);
}

void GameEngine::DrawTitleScreen() {
    ci::gl::clear();
    string text_to_print = "\nBEEMO'S RESCUE";
    size_t font_height = 70;
    size_t text_height_scale = 2;
    cinder::ivec2 size = {getWindowWidth(), font_height * text_height_scale};
    const Color color = Color::white();
    cinder::vec2 top_left_point = {0, 0};
    DrawTextBox(font_height, size, color, text_to_print, top_left_point);

    // Image source: https://www.mobafire.com/league-of-legends/skin/teemo-beemo-980
    cinder::gl::Texture2dRef image = cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("beemo splash.jpg")));
    size_t height_divisor = 2;
    float scaled_factor = ((float)getWindowHeight() / height_divisor) / image->getHeight();
    size_t start_x = ((float)getWindowWidth() / height_divisor) - ((image->getWidth() * scaled_factor) / height_divisor);
    size_t end_x = start_x + (image->getWidth() * scaled_factor);
    size_t start_y = ((float)getWindowHeight() / height_divisor) - ((image->getHeight() * scaled_factor) / height_divisor);
    size_t end_y = ((float)getWindowHeight() / height_divisor) + ((image->getHeight() * scaled_factor) / height_divisor);
    ci::Rectf drawRect(start_x, start_y, end_x, end_y);
    ci::gl::draw(image, drawRect);

    text_to_print = "\n\nPress [SPACE] or [E] to continue.";
    font_height = 25;
    text_height_scale = 3;
    size = {getWindowWidth(), font_height * text_height_scale};
    top_left_point = {0, end_y};
    DrawTextBox(font_height, size, color, text_to_print, top_left_point);
}

void GameEngine::DrawEndScreen() {
    ci::gl::clear();
    string text_to_print;
    if (game_state == GameState::kOutOfHealth) {
        text_to_print = "You ran out of HEALTH! As you collapse to the ground, you see the "
                        "PORO crying quietly in the corner. "
                        "\nYou have no way of saving it. It will spend its days stuck in the enemy base. :(";
    } else if (game_state == GameState::kOutOfAmmo) {
        text_to_print = "You ran out of BEES! There is no way for you to defeat the NEXUS TURRET now."
                        "\nThe PORO cries quietly in the corner -- you have no way of saving it. :(";
    } else if (game_state == GameState::kGameWon) {
        text_to_print = "CONGRATULATIONS! "
                        "\nYou saved the PORO! His teary eyes start to shine as he thanks you for your efforts."
                        "\nHe bounds away and quickly returns with a mouthful of Poro Snax, offering one to you too. "
                        "He happily munches away, grateful to be freed. <3";
    }

    const size_t font_height = 50;
    const cinder::ivec2 size = {getWindowWidth(), getWindowHeight() / 2};
    const Color color = Color::white();
    const cinder::vec2 top_left_point = {0, 0};
    DrawTextBox(font_height, size, color, text_to_print, top_left_point);
    DrawEndImage();
}

void GameEngine::DrawEndImage() {
    cinder::gl::Texture2dRef image;
    if (game_state == GameState::kOutOfAmmo || game_state == GameState::kOutOfHealth) {
        //Image Source: https://www.pngkit.com/view/u2w7o0u2q8y3t4r5_this-poro-hurt-its-tiny-head-when-it/
        image = cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("poro cry.png")));
    } else if (game_state == GameState::kGameWon) {
        //Image source: https://steamcommunity.com/sharedfiles/filedetails/?id=1813586504
        image = cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("poro happy.jpg")));
    }
    float scaled_factor = ((float)getWindowHeight() / 2) / image->getHeight();
    size_t start_x = ((float)getWindowWidth() / 2) - ((image->getWidth() * scaled_factor) / 2);
    size_t end_x = start_x + (image->getWidth() * scaled_factor);
    size_t start_y = getWindowHeight() / 2;
    size_t end_y = getWindowHeight();
    ci::Rectf drawRect(start_x, start_y, end_x, end_y);
    ci::gl::draw(image, drawRect);
}

bool GameEngine::IsFrontTileBuff() {
    return (GetFrontTile().GetDynamicType() != "BEE" && GetFrontTile().GetDynamicType() != "END" &&
            !GetFrontTile().IsUndefeated() && !GetFrontTile().IsUndiscovered() && GetFrontTile().IsDynamic());
}

bool GameEngine::IsFrontTileBoss() {
    return GetFrontTile().GetDynamicType() == "BOS";
}

string GameEngine::GetDescriptionText() {
    string text_to_print;
    if (game_state == GameState::kPlaying) {
        if (IsFrontTileBoss()) {
            text_to_print = current_scene.GetFinalBoss().GetDescription() +
                            current_scene.GetFinalBoss().GetInteractionInstructions();
        } else {
            text_to_print = GetFrontTile().GetDescription();
            if (IsFrontTileBuff() && beemo.IsInventoryFull()) {
                text_to_print += "\n\nYou have no more room in your inventory! You cannot pick up any more items.";
            } else {
                text_to_print += GetFrontTile().GetInteractionInstructions();
            }
        }
    } else if (game_state == GameState::kDealDamage) {
        text_to_print = "You deal " + std::to_string(beemo.GetTotalAP()) + " damage!";
        if (current_scene.GetFinalBoss().GetCurrentHealth() == 0) {
            text_to_print += "\nYou defeated the NEXUS TURRET!";
        } else {
            text_to_print += "\nThe NEXUS TURRET is now at " +
                             std::to_string(current_scene.GetFinalBoss().GetCurrentHealth()) + " HP. ";
        }
        text_to_print += "\nPress [SPACE] or [E] to continue.";
    } else if (game_state == GameState::kTakeDamage) {
        text_to_print = "The NEXUS TURRET deals " + std::to_string(current_scene.GetFinalBoss().GetDamage()) +
                        " damage! You are now at " + std::to_string(beemo.GetCurrentHP()) + " HP."
                        "\n Press [SPACE] or [E] to continue.";
    }
    return text_to_print;
}

void GameEngine::DrawTextBox(size_t font_height, const cinder::ivec2& size, const Color& color,
                             const string& text_to_print, const cinder::vec2& top_left_point) {
    cinder::gl::color(color);
    auto box = TextBox()
            .alignment(TextBox::CENTER)
            .font(cinder::Font("Arial", font_height))
            .size(size)
            .color(color)
            .backgroundColor(ColorA(0, 0, 0, 0))
            .text(text_to_print);
    const auto box_size = box.getSize();
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, top_left_point);
}

void GameEngine::DrawDescription() {
    ci::gl::clear();
    const size_t font_height = 30;
    const cinder::ivec2 size = {kDescriptionTileWidth * kTilePixelLength, kTextTileHeight * kTilePixelLength};
    const Color color = Color::white();
    string text_to_print = GetDescriptionText();

    const cinder::vec2 top_left_point = {0, kPlayingFieldTileHeight * kTilePixelLength};
    DrawTextBox(font_height, size, color, text_to_print, top_left_point);
}

void GameEngine::DrawStats() {
    const size_t font_height = 25;
    const cinder::ivec2 size = {kStatsTileWidth * kTilePixelLength, kTextTileHeight * kTilePixelLength};
    const Color color = Color::white();
    string text_to_print = "STATS:"
                           "\n\nABILITY POWER (AP): " + std::to_string(beemo.GetTotalAP()) +
                           "\nHEALTH (HP): " + std::to_string(beemo.GetCurrentHP()) + "/" +
                           std::to_string(beemo.GetTotalHP()) + "\nAMMO (BEES): " +
                           std::to_string(beemo.GetCurrentAmmoCount());
    const cinder::vec2 top_left_point = {(kPlayingFieldTileWidth - kStatsTileWidth) * kTilePixelLength,
                                         kPlayingFieldTileHeight * kTilePixelLength};
    DrawTextBox(font_height, size, color, text_to_print, top_left_point);
}

void GameEngine::DrawInventory() {
    const size_t font_height = 25;
    const cinder::ivec2 size = {kInventoryTileWidth * kTilePixelLength,  kTilePixelLength};
    const Color color = Color::white();
    string text_to_print = "\nINVENTORY";
    const cinder::vec2 top_left_point = {kDescriptionTileWidth * kTilePixelLength,
                                         kPlayingFieldTileHeight * kTilePixelLength};
    DrawTextBox(font_height, size, color, text_to_print, top_left_point);

    size_t item_columns = 2;
    size_t item_rows = 3;
    size_t inventory_title_tile_height = 1;
    size_t x_start = kDescriptionTileWidth * kTilePixelLength;
    size_t y_start = (kPlayingFieldTileHeight + inventory_title_tile_height) * kTilePixelLength;
    DrawInventoryItems(item_columns, item_rows, x_start, y_start);
}

void GameEngine::DrawInventoryItems(size_t column_count, size_t row_count, size_t x_start_pixel, size_t y_start_pixel) {
    size_t inventory_size = beemo.GetInventory().size();
    size_t counter = 0;
    if (!beemo.GetInventory().empty()) {
        for (size_t row = 0; row < row_count; row ++) {
            size_t y_end = y_start_pixel + kTilePixelLength;
            for (size_t col = 0; col < column_count; col++) {
                size_t x_end = x_start_pixel + kTilePixelLength;
                beemo.GetInventory()[counter].GetImage()->draw(x_start_pixel, y_start_pixel, x_end, y_end);
                if ((counter + 1 ) % column_count == 0) {
                    x_start_pixel = x_start_pixel - kTilePixelLength;
                } else {
                    x_start_pixel = x_end;
                }
                counter++;
                if (counter == inventory_size) {
                    return;
                }
            }
            y_start_pixel = y_end;
        }
    }
}

bool GameEngine::CanMove(const string& direction) {
    if (!IsWithinSceneBounds(direction)) {
        return false;
    }
    mylibrary::Tile potential_tile = GetFrontTile();
    return (!potential_tile.IsSolid());
}

bool GameEngine::IsWithinSceneBounds(const string& direction) {
    if (direction == kUp) {
        if (beemo.GetYTile() != 1) {
            return true;
        }
    } else if (direction == kDown) {
        if (beemo.GetYTile() != current_scene.GetMaxYTiles()) {
            return true;
        }
    } else if (direction == kLeft) {
        if (beemo.GetXTile() != 1) {
            return true;
        }
    } else if (direction == kRight) {
        if (beemo.GetXTile() != current_scene.GetMaxXTiles()) {
            return true;
        }
    }
    return false;
}

mylibrary::Tile GameEngine::GetFrontTile() {
    mylibrary::Tile potential_tile;
    if (beemo.GetOrientation() == kUp) {
        if (beemo.GetYTile() == 1) {
            return mylibrary::Tile();
        } else {
            size_t index_above = beemo.GetYTile() - 1;
            potential_tile = current_scene.GetTile(beemo.GetXTile(), index_above);
        }
    } else if (beemo.GetOrientation() == kDown) {
        if (beemo.GetYTile() == current_scene.GetMaxYTiles()) {
            return mylibrary::Tile();
        } else {
            size_t index_below = beemo.GetYTile() + 1;
            potential_tile = current_scene.GetTile(beemo.GetXTile(), index_below);
        }
    } else if (beemo.GetOrientation() == kLeft) {
        if (beemo.GetXTile() == 1) {
            return mylibrary::Tile();
        } else {
            size_t index_left = beemo.GetXTile() - 1;
            potential_tile = current_scene.GetTile(index_left, beemo.GetYTile());
        }
    } else if (beemo.GetOrientation() == kRight) {
        if (beemo.GetXTile() == current_scene.GetMaxXTiles()) {
            return mylibrary::Tile();
        } else {
            size_t index_right = beemo.GetXTile() + 1;
            potential_tile = current_scene.GetTile(index_right, beemo.GetYTile());
        }
    }
    return potential_tile;
}

size_t GameEngine::GetFrontTileX() {
    if (beemo.GetOrientation() == kLeft) {
        return beemo.GetXTile() - 1;
    } else if (beemo.GetOrientation() == kRight) {
        return beemo.GetXTile() + 1;
    } else {
        return beemo.GetXTile();
    }
}

size_t GameEngine::GetFrontTileY() {
    if (beemo.GetOrientation() == kUp) {
        return beemo.GetYTile() - 1;
    } else if (beemo.GetOrientation() == kDown) {
        return beemo.GetYTile() + 1;
    } else {
        return beemo.GetYTile();
    }
}

void GameEngine::GetPlayingStateResponse(const KeyEvent& event) {
    switch (event.getCode()) {
        case KeyEvent::KEY_UP:
        case KeyEvent::KEY_w: {
            string direction = kUp;
            GetDirectionResponse(direction);
            break;
        }
        case KeyEvent::KEY_DOWN:
        case KeyEvent::KEY_s: {
            string direction = kDown;
            GetDirectionResponse(direction);
            break;
        }
        case KeyEvent::KEY_LEFT:
        case KeyEvent::KEY_a: {
            string direction = kLeft;
            GetDirectionResponse(direction);
            break;
        }
        case KeyEvent::KEY_RIGHT:
        case KeyEvent::KEY_d: {
            string direction = kRight;
            GetDirectionResponse(direction);
            break;
        }
        case KeyEvent::KEY_SPACE: {
            if (GetFrontTile().IsUndefeated() || GetFrontTile().GetDynamicType() == "BOS") {
                GetAttackResponse();
            } else {
                GetInteractResponse();
            }
            break;
        }
        case KeyEvent::KEY_q: {
            GetAttackResponse();
            break;
        }
        case KeyEvent::KEY_e: {
            GetInteractResponse();
            break;
        }
    }
}

void GameEngine::GetAttackResponse() {
    if (GetFrontTile().IsUndefeated() && beemo.GetCurrentAmmoCount() > 0) {
        beemo.UseAmmo();
        beemo.Uncover();
        total_ammo_available--;
        current_scene.Reveal(GetFrontTileX(), GetFrontTileY());
    } else if (GetFrontTile().GetDynamicType() == "BOS" && beemo.GetCurrentAmmoCount() > 0) {
        beemo.UseAmmo();
        beemo.Uncover();
        total_ammo_available--;
        game_state = GameState::kDealDamage;
        is_action_queued = true;
    }
}

void GameEngine::GetInteractResponse() {
    if (GetFrontTile().GetDynamicType() == "END") {
        game_state = GameState::kGameWon;
    } else if (GetFrontTile().IsUndiscovered()) {
        beemo.Uncover();
        current_scene.Reveal(GetFrontTileX(), GetFrontTileY());
    } else if (GetFrontTile().GetDynamicType() == "BEE") {
        beemo.Grab(GetFrontTile().GetItem());
        current_scene.Remove(GetFrontTileX(), GetFrontTileY());
    } else if (!beemo.IsInventoryFull() && GetFrontTile().IsDynamic() && !GetFrontTile().IsUndefeated()) {
        beemo.Grab(GetFrontTile().GetItem());
        current_scene.Remove(GetFrontTileX(), GetFrontTileY());
    }
}

void GameEngine::GetDirectionResponse(const string& direction) {
    beemo.SetImage(direction);
    if (direction == kUp) {
        if (CanMove(direction)) {
            beemo.SetYTile(beemo.GetYTile() - 1);
        }
    } else if (direction == kDown) {
        if (CanMove(direction)) {
            beemo.SetYTile(beemo.GetYTile() + 1);
        }
    } else if (direction == kLeft) {
        if (current_scene == scene_two &&
            current_scene.GetTile(beemo.GetXTile(), beemo.GetYTile()).IsTeleport()) {
            scene_two = current_scene;
            current_scene = scene_one;
            beemo.SetXTile(scene_one.GetMaxXTiles());
            return;
        } else if (CanMove(direction)) {
            beemo.SetXTile(beemo.GetXTile() - 1);
        }
    } else if (direction == kRight) {
        if (current_scene == scene_one &&
            current_scene.GetTile(beemo.GetXTile(), beemo.GetYTile()).IsTeleport()) {
            scene_one = current_scene;
            current_scene = scene_two;
            beemo.SetXTile(1);
            return;
        } else if (CanMove(direction)) {
            beemo.SetXTile(beemo.GetXTile() + 1);
        }
    }
}

}  // namespace myapp

