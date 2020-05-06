// Copyright (c) 2020 [Sue Wee]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include <iostream>
#include "my_app.h"
#include "mylibrary/ciAnimatedGif.h"
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

    bool is_action_queued = false;
    size_t total_ammo_available;

    cinder::ciAnimatedGifRef sized_32;
    cinder::ciAnimatedGifRef sized_64;

MyApp::MyApp() {
    game_state = {GameState::kIntroduction};
}

void MyApp::setup() {
    ci::app::setWindowSize(kPlayingFieldTileWidth * kTilePixelLength,
            (kPlayingFieldTileHeight + kTextTileHeight) * kTilePixelLength);
    scene_one = mylibrary::PlayingField("stage_one.txt");
    scene_two = mylibrary::PlayingField("stage_two.txt");
    current_scene = scene_one;
    beemo = mylibrary::Character(1,8,64,"beemo right.gif");
    total_ammo_available = scene_one.GetAmmoCount() + scene_two.GetAmmoCount();

    sized_32 = cinder::ciAnimatedGif::create( ci::app::loadAsset("32 scaled.gif"));
    sized_64 = cinder::ciAnimatedGif::create( ci::app::loadAsset("64 scaled.gif"));
}

void MyApp::update() {
    if (is_action_queued) {
        if (game_state == GameState::kDealDamage) {
            current_scene.DealBossDamage(beemo.GetTotalAP());
        } else if (game_state == GameState::kTakeDamage) {
            beemo.TakeDamage(current_scene.GetFinalBoss().GetDamage());
        }
        is_action_queued = false;
    }
}

void MyApp::draw() {
    //sized_32->draw(384,0,512,128);
    //sized_64->draw(384,128,512,256);
    if (game_state == GameState::kIntroduction) {
        DrawIntroduction();
    } else if (game_state == GameState::kPlaying) {
        if (current_scene.GetFinalBoss().GetCurrentHealth() != 0 && total_ammo_available == 0) {
            game_state = GameState::kOutOfAmmo;
        }
        if (beemo.GetCurrentHP() == 0) {
            game_state = GameState::kOutOfHealth;
        }
        cinder::gl::clear();
        DrawDescription();
        DrawInventory();
        DrawStats();
        current_scene.draw();
        beemo.GetImage()->draw(beemo.GetXStartPixel(),beemo.GetYStartPixel(),
                               beemo.GetXEndPixel(), beemo.GetYEndPixel());
    } else if (game_state == GameState::kGameWon) {
        DrawEndScreen();
    } else if (game_state == GameState::kDealDamage) {
        cinder::gl::clear();
        DrawDamageDealtDescription();
        DrawInventory();
        DrawStats();
        current_scene.draw();
        beemo.GetImage()->draw(beemo.GetXStartPixel(),beemo.GetYStartPixel(),
                               beemo.GetXEndPixel(), beemo.GetYEndPixel());
    } else if (game_state == GameState::kTakeDamage) {
        if (current_scene.GetFinalBoss().GetCurrentHealth() == 0) {
            game_state = GameState::kPlaying;
        } else {
            cinder::gl::clear();
            DrawDamageReceivedDescription();
            DrawInventory();
            DrawStats();
            current_scene.draw();
            beemo.GetImage()->draw(beemo.GetXStartPixel(), beemo.GetYStartPixel(),
                                   beemo.GetXEndPixel(), beemo.GetYEndPixel());
        }
    } else if (game_state == GameState::kOutOfHealth) {
        DrawEndScreen();
    } else if (game_state == GameState::kOutOfAmmo) {
        DrawEndScreen();
    }
}

void MyApp::DrawIntroduction() {
    ci::gl::clear();
    const size_t font_height = 30;
    const cinder::ivec2 size = {kPlayingFieldTileWidth * kTilePixelLength, (kTextTileHeight + kPlayingFieldTileHeight) * kTilePixelLength};
    const Color color = Color::white();

    cinder::gl::color(color);
    auto box = TextBox()
            .alignment(TextBox::CENTER)
            .font(cinder::Font("Arial", font_height))
            .size(size)
            .color(color)
            .backgroundColor(ColorA(0, 0, 0, 0))
            .text("Welcome to Beemo's Adventures!"
                  "\n\n You are playing as BEEMO, the cute little League of Legends champion."
                  "\n\n You are on a mission to save your good friend, a PORO! In order to defeat the game, you must "
                  "defeat the NEXUS TURRET."
                  "\n\n You can collect items that are hidden on the map for special buffs. Once you pick up an item, "
                  "you cannot drop it. And remember, you only have a maximum of 6 item slots. Defeating MINIONS will "
                  "reveal items with stronger buffs than those hidden elsewhere. However, choose wisely, because "
                  "if you expend all your BEES on the MINIONS, you will not have enough to fight the NEXUS TURRET "
                  "in the end."
                  "\n\n Use [WASD] or the [ARROW KEYS] to move. Use [SPACE] or [Q] to attack or uncover objects, and "
                  "[SPACE] or [E] to add objects to your inventory."
                  "\n\n\nAre you ready to begin your adventures?"
                  "\nPress [SPACE] or [E] to start.");

    const auto box_size = box.getSize();
    const cinder::vec2 top_left_point = {0,0};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, top_left_point);
}

void MyApp::DrawEndScreen() {
    string text_to_print;
    if (game_state == GameState::kOutOfHealth) {
        text_to_print = "You ran out of HEALTH! As you collapse to the ground, you see the "
                        "PORO crying quietly in the corner. "
                        "\nYou have no way of saving it. It will spend its days stuck in the enemy base. :(";
    } else if (game_state == GameState::kOutOfAmmo) {
        text_to_print = "You ran out of BEES! There is no way for you to defeat the NEXUS TURRET now."
                        "\nThe PORO cries quietly in the corner -- you have no way of saving it. :(";
    } else if (game_state == GameState::kGameWon) {
        text_to_print = "CONGRATULATIONS! \n You saved the PORO! <3";
    }

    ci::gl::clear();
    const size_t font_height = 50;
    const cinder::ivec2 size = {getWindowWidth(), getWindowHeight() / 2};
    const Color color = Color::white();

    cinder::gl::color(color);
    auto box = TextBox()
            .alignment(TextBox::CENTER)
            .font(cinder::Font("Arial", font_height))
            .size(size)
            .color(color)
            .backgroundColor(ColorA(0, 0, 0, 0))
            .text(text_to_print);

    const auto box_size = box.getSize();
    const cinder::vec2 top_left_point = {0, 0};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, top_left_point);
}

void MyApp::DrawDescription() {
    const size_t font_height = 30;
    const cinder::ivec2 size = {kDescriptionTileWidth * kTilePixelLength, kTextTileHeight * kTilePixelLength};
    const Color color = Color::white();
    string text_to_print;
    if (beemo.IsInventoryFull()) {
        if (GetFrontTile().GetDynamicType() != "BEE" && GetFrontTile().GetDynamicType() != "END" && !GetFrontTile().IsUndefeated() &&
            !GetFrontTile().IsUndiscovered() && GetFrontTile().IsDynamic()) {
            text_to_print = GetFrontTile().GetDescription() +
                    "\n\nYou have no more room in your inventory! You cannot pick up any more items.";
        } else if (GetFrontTile().GetDynamicType() == "BOS") {
            text_to_print = current_scene.GetFinalBoss().GetDescription() +
                            current_scene.GetFinalBoss().GetInteractionInstructions();
        } else {
            text_to_print = GetFrontTile().GetDescription() + GetFrontTile().GetInteractionInstructions();
        }
    } else if (GetFrontTile().GetDynamicType() == "BOS") {
        text_to_print = current_scene.GetFinalBoss().GetDescription() +
                        current_scene.GetFinalBoss().GetInteractionInstructions();
    } else {
        text_to_print = GetFrontTile().GetDescription() + GetFrontTile().GetInteractionInstructions();
    }

    cinder::gl::color(color);
    auto box = TextBox()
            .alignment(TextBox::CENTER)
            .font(cinder::Font("Arial", font_height))
            .size(size)
            .color(color)
            .backgroundColor(ColorA(0, 0, 0, 0))
            .text(text_to_print);


    const auto box_size = box.getSize();
    const cinder::vec2 top_left_point = {0, kPlayingFieldTileHeight * kTilePixelLength};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, top_left_point);
}

void MyApp::DrawDamageDealtDescription() {
        const size_t font_height = 30;
        const cinder::ivec2 size = {kDescriptionTileWidth * kTilePixelLength, kTextTileHeight * kTilePixelLength};
        const Color color = Color::white();
        string text_to_print;
        if (current_scene.GetFinalBoss().GetCurrentHealth() == 0) {
            text_to_print = "You deal " + std::to_string(beemo.GetTotalAP()) + " damage!"
                            "\nYou defeated the NEXUS TURRET!"
                            "\nPress [SPACE] or [E] to continue.";
        } else {
            text_to_print = "You deal " + std::to_string(beemo.GetTotalAP()) + " damage!"
                            "\nThe NEXUS TURRET is now at " +
                            std::to_string(current_scene.GetFinalBoss().GetCurrentHealth()) + " HP. "
                            "\nPress [SPACE] or [E] to continue.";
        }


        cinder::gl::color(color);
        auto box = TextBox()
                .alignment(TextBox::CENTER)
                .font(cinder::Font("Arial", font_height))
                .size(size)
                .color(color)
                .backgroundColor(ColorA(0, 0, 0, 0))
                .text(text_to_print);


        const auto box_size = box.getSize();
        const cinder::vec2 top_left_point = {0, kPlayingFieldTileHeight * kTilePixelLength};
        const auto surface = box.render();
        const auto texture = cinder::gl::Texture::create(surface);
        cinder::gl::draw(texture, top_left_point);
    }

    void MyApp::DrawDamageReceivedDescription() {
        const size_t font_height = 30;
        const cinder::ivec2 size = {kDescriptionTileWidth * kTilePixelLength, kTextTileHeight * kTilePixelLength};
        const Color color = Color::white();
        string text_to_print;
        text_to_print = "The NEXUS TURRET deals " + std::to_string(current_scene.GetFinalBoss().GetDamage()) + " damage! "
                        "You are now at " + std::to_string(beemo.GetCurrentHP()) + " HP."
                        "\n Press [SPACE] or [E] to continue.";

        cinder::gl::color(color);
        auto box = TextBox()
                .alignment(TextBox::CENTER)
                .font(cinder::Font("Arial", font_height))
                .size(size)
                .color(color)
                .backgroundColor(ColorA(0, 0, 0, 0))
                .text(text_to_print);


        const auto box_size = box.getSize();
        const cinder::vec2 top_left_point = {0, kPlayingFieldTileHeight * kTilePixelLength};
        const auto surface = box.render();
        const auto texture = cinder::gl::Texture::create(surface);
        cinder::gl::draw(texture, top_left_point);
    }

    void MyApp::DrawStats() {
        const size_t font_height = 25;
        const cinder::ivec2 size = {kStatsTileWidth * kTilePixelLength, kTextTileHeight * kTilePixelLength};
        const Color color = Color::white();

        cinder::gl::color(color);
        auto box = TextBox()
                .alignment(TextBox::CENTER)
                .font(cinder::Font("Arial", font_height))
                .size(size)
                .color(color)
                .backgroundColor(ColorA(0, 0, 0, 0))
                .text("\nSTATS:"
                         "\nABILITY POWER (AP): " + std::to_string(beemo.GetTotalAP()) +
                         "\nHEALTH (HP): " + std::to_string(beemo.GetCurrentHP()) + "/" +
                         std::to_string(beemo.GetTotalHP()) + "\nAMMO (BEES): " +
                         std::to_string(beemo.GetCurrentAmmoCount()));


        const auto box_size = box.getSize();
        const cinder::vec2 top_left_point = {(kPlayingFieldTileWidth - kStatsTileWidth) * kTilePixelLength,
                                   kPlayingFieldTileHeight * kTilePixelLength};
        const auto surface = box.render();
        const auto texture = cinder::gl::Texture::create(surface);
        cinder::gl::draw(texture, top_left_point);
}

void MyApp::DrawInventory() {
    const size_t font_height = 25;
    const cinder::ivec2 size = {kInventoryTileWidth * kTilePixelLength,  kTilePixelLength};
    const Color color = Color::white();

    cinder::gl::color(color);
    auto box = TextBox()
            .alignment(TextBox::CENTER)
            .font(cinder::Font("Arial", font_height))
            .size(size)
            .color(color)
            .backgroundColor(ColorA(0, 0, 0, 0))
            .text("\nINVENTORY");


    const auto box_size = box.getSize();
    const cinder::vec2 top_left_point = {kDescriptionTileWidth * kTilePixelLength,
                               kPlayingFieldTileHeight * kTilePixelLength};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, top_left_point);
    size_t inventory_size = beemo.GetInventory().size();
    size_t counter = 0;
    size_t x_start = kDescriptionTileWidth * kTilePixelLength;
    size_t y_start = (kPlayingFieldTileHeight + 1) * kTilePixelLength;
    if (inventory_size > 0) {
        //beemo.GetInventory()[0].GetImage()->draw(448, 640 - 64, 512, 704 - 64);

        for (size_t row = 0; row < 3; row ++) {
            size_t y_end = y_start + kTilePixelLength;
            for (size_t col = 0; col < 2; col++) {
                size_t x_end = x_start + kTilePixelLength;
                beemo.GetInventory()[counter].GetImage()->draw(x_start, y_start, x_end, y_end);
                if ((counter + 1 )% 2 == 0) {
                    x_start = x_start - kTilePixelLength;
                } else {
                    x_start = x_end;
                }
                counter++;
                if (counter == inventory_size) {
                    return;
                }
            }
            y_start = y_end;
        }

    }
}

bool MyApp::CanMove(const string& direction) {
    if (!IsWithinSceneBounds(direction)) {
        return false;
    }
    mylibrary::Tile potential_tile = GetFrontTile();
    return (!potential_tile.IsSolid());
}

bool MyApp::IsWithinSceneBounds(const string& direction) {
    if (direction == "up") {
        if (beemo.GetYTile() != 1) {
            return true;
        }
    } else if (direction == "down") {
        if (beemo.GetYTile() != current_scene.GetMaxYTiles()) {
            return true;
        }
    } else if (direction == "left") {
        if (beemo.GetXTile() != 1) {
            return true;
        }
    } else if (direction == "right") {
        if (beemo.GetXTile() != current_scene.GetMaxXTiles()) {
            return true;
        }
    }
    return false;
}

mylibrary::Tile MyApp::GetFrontTile() {
    mylibrary::Tile potential_tile;
    if (beemo.GetOrientation() == "up") {
        if (beemo.GetYTile() == 1) {
            return mylibrary::Tile();
        } else {
            size_t index_above = beemo.GetYTile() - 1;
            potential_tile = current_scene.GetTile(beemo.GetXTile(), index_above);
        }
    } else if (beemo.GetOrientation() == "down") {
        if (beemo.GetYTile() == current_scene.GetMaxYTiles()) {
            return mylibrary::Tile();
        } else {
            size_t index_below = beemo.GetYTile() + 1;
            potential_tile = current_scene.GetTile(beemo.GetXTile(), index_below);
        }
    } else if (beemo.GetOrientation() == "left") {
        if (beemo.GetXTile() == 1) {
            return mylibrary::Tile();
        } else {
            size_t index_left = beemo.GetXTile() - 1;
            potential_tile = current_scene.GetTile(index_left, beemo.GetYTile());
        }
    } else if (beemo.GetOrientation() == "right") {
        if (beemo.GetXTile() == current_scene.GetMaxXTiles()) {
            return mylibrary::Tile();
        } else {
            size_t index_right = beemo.GetXTile() + 1;
            potential_tile = current_scene.GetTile(index_right, beemo.GetYTile());
        }
    }
    return potential_tile;
}

size_t MyApp::GetFrontTileX() {
    if (beemo.GetOrientation() == "left") {
        return beemo.GetXTile() - 1;
    } else if (beemo.GetOrientation() == "right") {
        return beemo.GetXTile() + 1;
    } else {
        return beemo.GetXTile();
    }
}

size_t MyApp::GetFrontTileY() {
    if (beemo.GetOrientation() == "up") {
        return beemo.GetYTile() - 1;
    } else if (beemo.GetOrientation() == "down") {
        return beemo.GetYTile() + 1;
    } else {
        return beemo.GetYTile();
    }
}

void MyApp::keyDown(KeyEvent event) {
    if (game_state == GameState::kIntroduction) {
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
        switch (event.getCode()) {
            case KeyEvent::KEY_UP:
            case KeyEvent::KEY_w: {
                string direction = "up";
                beemo.SetImage(direction);
                if (CanMove(direction)) {
                    beemo.SetYTile(beemo.GetYTile() - 1);
                }
                break;
            }
            case KeyEvent::KEY_DOWN:
            case KeyEvent::KEY_s: {
                string direction = "down";
                beemo.SetImage(direction);
                if (CanMove(direction)) {
                    beemo.SetYTile(beemo.GetYTile() + 1);
                }
                break;
            }
            case KeyEvent::KEY_LEFT:
            case KeyEvent::KEY_a: {
                string direction = "left";
                beemo.SetImage(direction);
                if (current_scene == scene_two &&
                    current_scene.GetTile(beemo.GetXTile(), beemo.GetYTile()).IsTeleport()) {
                    scene_two = current_scene;
                    current_scene = scene_one;
                    beemo.SetXTile(scene_one.GetMaxXTiles());
                    break;
                } else if (CanMove(direction)) {
                    beemo.SetXTile(beemo.GetXTile() - 1);
                }
                break;
            }
            case KeyEvent::KEY_RIGHT:
            case KeyEvent::KEY_d: {
                string direction = "right";
                beemo.SetImage(direction);
                if (current_scene == scene_one &&
                    current_scene.GetTile(beemo.GetXTile(), beemo.GetYTile()).IsTeleport()) {
                    scene_one = current_scene;
                    current_scene = scene_two;
                    beemo.SetXTile(1);
                    break;
                } else if (CanMove(direction)) {
                    beemo.SetXTile(beemo.GetXTile() + 1);
                }
                break;
            }
            case KeyEvent::KEY_SPACE: {
                if (GetFrontTile().GetDynamicType() == "END") {
                    game_state = GameState::kGameWon;
                } else if (GetFrontTile().IsUndiscovered()) {
                    beemo.AttackMode();
                    current_scene.Reveal(GetFrontTileX(), GetFrontTileY());
                } else if (GetFrontTile().IsUndefeated() && beemo.GetCurrentAmmoCount() > 0) {
                    beemo.UseAmmo();
                    beemo.AttackMode();
                    total_ammo_available--;
                    current_scene.Reveal(GetFrontTileX(), GetFrontTileY());
                } else if (GetFrontTile().GetDynamicType() == "BEE") {
                    beemo.Grab(GetFrontTile().GetItem());
                    current_scene.Remove(GetFrontTileX(), GetFrontTileY());
                } else if (!beemo.IsInventoryFull() && GetFrontTile().IsDynamic() && !GetFrontTile().IsUndefeated()) {
                    beemo.Grab(GetFrontTile().GetItem());
                    current_scene.Remove(GetFrontTileX(), GetFrontTileY());
                } else if (GetFrontTile().GetDynamicType() == "BOS" && beemo.GetCurrentAmmoCount() > 0) {
                    beemo.UseAmmo();
                    beemo.AttackMode();
                    total_ammo_available--;
                    game_state = GameState::kDealDamage;
                    is_action_queued = true;
                }
                break;
            }
            case KeyEvent::KEY_q: {
                if (GetFrontTile().IsUndefeated() && beemo.GetCurrentAmmoCount() > 0) {
                    beemo.UseAmmo();
                    beemo.AttackMode();
                    total_ammo_available--;
                    current_scene.Reveal(GetFrontTileX(), GetFrontTileY());
                } else if (GetFrontTile().GetDynamicType() == "BOS" && beemo.GetCurrentAmmoCount() > 0) {
                    beemo.UseAmmo();
                    beemo.AttackMode();
                    total_ammo_available--;
                    game_state = GameState::kDealDamage;
                    is_action_queued = true;
                }
                break;
            }
            case KeyEvent::KEY_e: {
                if (GetFrontTile().GetDynamicType() == "END") {
                    game_state = GameState::kGameWon;
                } else if (GetFrontTile().IsUndiscovered() && event.getCode()) {
                    beemo.AttackMode();
                    current_scene.Reveal(GetFrontTileX(), GetFrontTileY());
                } else if (GetFrontTile().GetDynamicType() == "BEE") {
                    beemo.Grab(GetFrontTile().GetItem());
                    current_scene.Remove(GetFrontTileX(), GetFrontTileY());
                } else if (!beemo.IsInventoryFull() && GetFrontTile().IsDynamic() && !GetFrontTile().IsUndefeated()) {
                    beemo.Grab(GetFrontTile().GetItem());
                    current_scene.Remove(GetFrontTileX(), GetFrontTileY());
                }
                break;
            }
        }
    }
}

}  // namespace myapp
