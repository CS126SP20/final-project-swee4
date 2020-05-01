// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "mylibrary/ciAnimatedGif.h"

#include <cinder/app/App.h>
#include <mylibrary/playing_field.h>
#include <iostream>


namespace myapp {

using cinder::app::KeyEvent;
    using cinder::Color;
    using cinder::TextBox;
    using cinder::ColorA;
    using std::string;

    cinder::ciAnimatedGifRef teemo_default;
    cinder::ciAnimatedGifRef teemo_attack;

    std::string parsed_file = "cheese";

MyApp::MyApp() {
}
void MyApp::setup() {
    teemo_default = cinder::ciAnimatedGif::create( loadAsset("beemo default.gif"));
    teemo_attack = cinder::ciAnimatedGif::create( loadAsset("beemo attack.gif"));
    ci::app::setWindowSize(12*64,12*64);
    scene_one = mylibrary::PlayingField("stage_one.txt");
    scene_two = mylibrary::PlayingField("stage_two.txt");
    current_scene = scene_one;
    beemo = mylibrary::Character(1,8,64,"beemo default.gif");
}

void MyApp::update() { }

void MyApp::draw() {
    cinder::gl::clear();

    const cinder::vec2 center = getWindowCenter();
    const size_t font_height = 20;
    const cinder::ivec2 size = {500, font_height*5};
    const Color color = Color::white();

    cinder::gl::color(color);
    auto box = TextBox()
            .alignment(TextBox::CENTER)
            .font(cinder::Font("Arial", font_height))
            .size(size)
            .color(color)
            .backgroundColor(ColorA(0, 0, 0, 0))
            .text(parsed_file);


    const auto box_size = box.getSize();
    const cinder::vec2 locp = {center.x - box_size.x / 2, center.y - box_size.y / 2};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, locp);


    std::vector<std::vector<mylibrary::Tile>> tiles = current_scene.GetTileMap();

    for (size_t current_y_tile = 1; current_y_tile <= current_scene.GetMaxYTiles(); current_y_tile++) {
        for (size_t current_x_tile = 1; current_x_tile <= current_scene.GetMaxXTiles(); current_x_tile++) {
            mylibrary::Tile current_tile = tiles[current_y_tile - 1][current_x_tile - 1];
            size_t start_x = current_scene.GetXStartPixel(current_x_tile);
            size_t end_x = current_scene.GetXEndPixel(current_x_tile);
            size_t start_y = current_scene.GetYStartPixel(current_y_tile);
            size_t end_y = current_scene.GetYEndPixel(current_y_tile);
            ci::Rectf drawRect(start_x, start_y, end_x, end_y);
            ci::gl::draw(current_tile.GetStillMapImage(), drawRect);
            if (current_tile.IsDynamic()) {
                current_tile.GetDynamicImage()->draw(start_x, start_y, end_x, end_y);
            }
        }
    }
    //teemo_default->draw(0,0,64,64);

    beemo.GetImage()->draw(beemo.GetXStartPixel(),beemo.GetYStartPixel(), beemo.GetXEndPixel(), beemo.GetYEndPixel());
}

bool MyApp::CanBeemoMove(const string& direction) {
    if (!IsWithinSceneBounds(direction)) {
        return false;
    }
    mylibrary::Tile potential_tile;
    if (direction == "up") {
        size_t index_above = beemo.GetYTile() - 1;
        potential_tile = current_scene.GetTile(beemo.GetXTile(), index_above);
    } else if (direction == "down") {
        size_t index_below = beemo.GetYTile() + 1;
        potential_tile = current_scene.GetTile(beemo.GetXTile(), index_below);
    } else if (direction == "left") {
        size_t index_left = beemo.GetXTile() - 1;
        potential_tile = current_scene.GetTile(index_left, beemo.GetYTile());
    } else if (direction == "right") {
        size_t index_right = beemo.GetXTile() + 1;
        potential_tile = current_scene.GetTile(index_right, beemo.GetYTile());
    }
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

void MyApp::keyDown(KeyEvent event) {
    switch (event.getCode()) {
        case KeyEvent::KEY_UP:
        case KeyEvent::KEY_w: {
            string direction = "up";
            beemo.SetImage(direction);
            if (CanBeemoMove(direction)) {
                beemo.SetYTile(beemo.GetYTile() - 1);
            }
            break;
        }
        case KeyEvent::KEY_DOWN:
        case KeyEvent::KEY_s: {
            string direction = "down";
            beemo.SetImage(direction);
            if (CanBeemoMove(direction)) {
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
                //TODO: check if game state can be preserved between scenes
                current_scene = scene_one;
                beemo.SetXTile(scene_one.GetMaxXTiles());
                break;
            } else if (CanBeemoMove(direction)) {
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
                    //TODO: check if game state can be preserved between scenes
                current_scene = scene_two;
                beemo.SetXTile(1);
                break;
            } else if (CanBeemoMove(direction)) {
                beemo.SetXTile(beemo.GetXTile() + 1);
            }
            break;
        }
    }
}

}  // namespace myapp
