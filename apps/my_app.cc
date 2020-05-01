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

MyApp::MyApp() { }

void MyApp::setup() {
    ci::app::setWindowSize(kPlayingFieldTileWidth * kTilePixelLength,
            (kPlayingFieldTileHeight + kTextTileHeight) * kTilePixelLength);
    scene_one = mylibrary::PlayingField("stage_one.txt");
    scene_two = mylibrary::PlayingField("stage_two.txt");
    current_scene = scene_one;
    beemo = mylibrary::Character(1,8,64,"beemo right.gif");
}

void MyApp::update() {
}

void MyApp::draw() {
    cinder::gl::clear();

    DrawDescription();
    DrawInventory();
    DrawStats();

    current_scene.draw();
    beemo.GetImage()->draw(beemo.GetXStartPixel(),beemo.GetYStartPixel(),
            beemo.GetXEndPixel(), beemo.GetYEndPixel());
}

void MyApp::DrawDescription() {
    const size_t font_height = 30;
    const cinder::ivec2 size = {kDescriptionTileWidth * kTilePixelLength, kTextTileHeight * kTilePixelLength};
    const Color color = Color::white();
    string text_to_print;
    if (beemo.IsInventoryFull()) {
        if (GetFrontTile().GetDynamicType() != "BEE" && !GetFrontTile().IsUndefeated() &&
            !GetFrontTile().IsUndiscovered() && GetFrontTile().IsDynamic()) {
            text_to_print = GetFrontTile().GetDescription() +
                    "\n\nYou have no more room in your inventory! You cannot pick up any more items.";
        } else {
            text_to_print = GetFrontTile().GetDescription() + GetFrontTile().GetInteractionInstructions();
        }
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
    const cinder::vec2 locp = {0, kPlayingFieldTileHeight * kTilePixelLength};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, locp);
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
                         "\nABILITY POWER (AP): " + std::to_string(beemo.GetStat("AP")) +
                         "\nHEALTH (HP): " + std::to_string(beemo.GetStat("HP")) +
                         "\nAMMO (BEES): " + std::to_string(beemo.GetStat("BE")));


        const auto box_size = box.getSize();
        const cinder::vec2 locp = {(kPlayingFieldTileWidth - kStatsTileWidth) * kTilePixelLength,
                                   kPlayingFieldTileHeight * kTilePixelLength};
        const auto surface = box.render();
        const auto texture = cinder::gl::Texture::create(surface);
        cinder::gl::draw(texture, locp);
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
    const cinder::vec2 locp = {kDescriptionTileWidth * kTilePixelLength,
                               kPlayingFieldTileHeight * kTilePixelLength};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, locp);
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
        case KeyEvent::KEY_SPACE:
        case KeyEvent::KEY_x: {
            scene_one.GetTile(1,2).Reveal();
            if (GetFrontTile().IsUndiscovered() || (GetFrontTile().IsUndefeated() && beemo.GetStat("BE") > 0)) {
                if (GetFrontTile().IsUndefeated()) {
                    beemo.UseAmmo();
                }
                beemo.AttackMode();
                current_scene.Reveal(GetFrontTileX(), GetFrontTileY());
            } else if (GetFrontTile().GetDynamicType() == "BEE") {
                beemo.Grab(GetFrontTile().GetItem());
                current_scene.Remove(GetFrontTileX(), GetFrontTileY());
            } else if (!beemo.IsInventoryFull() && GetFrontTile().IsDynamic() && !GetFrontTile().IsUndefeated()) {
                beemo.Grab(GetFrontTile().GetItem());
                current_scene.Remove(GetFrontTileX(), GetFrontTileY());
            }
        }
    }
}

}  // namespace myapp
