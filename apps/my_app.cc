// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "mylibrary/ciAnimatedGif.h"

#include <cinder/app/App.h>
#include <mylibrary/playing_field.h>


namespace myapp {

using cinder::app::KeyEvent;

    cinder::ciAnimatedGifRef mGif;
    cinder::ciAnimatedGifRef teemo_default;
    cinder::ciAnimatedGifRef teemo_attack;

MyApp::MyApp() { }

void MyApp::setup() {
    mBackground_ = cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("grass.png")));
    mGif = cinder::ciAnimatedGif::create( loadAsset("cherry-blossom.gif"));
    teemo_default = cinder::ciAnimatedGif::create( loadAsset("beemo default.gif"));
    teemo_attack = cinder::ciAnimatedGif::create( loadAsset("beemo attack.gif"));
    //scene_one = mylibrary::PlayingField();
    ci::app::setWindowSize(12*64,12*64);
    scene_one = mylibrary::PlayingField("stage_one.txt");

}

void MyApp::update() { }

void MyApp::draw() {
    //ci::gl::translate(1,1);
    cinder::gl::clear();
    //mGif->draw(0,0,getWindowWidth(), getWindowHeight());
    teemo_default->draw();
    teemo_attack->draw(704,448,768,512);
    /*
    for (size_t current_y_tile = 1; current_y_tile <= scene_one.GetMaxYTiles(); current_y_tile++) {
        for (size_t current_x_tile = 1; current_x_tile <= scene_one.GetMaxXTiles(); current_x_tile++) {
            size_t start_x = scene_one.GetXStartPixel(current_x_tile);
            size_t end_x = scene_one.GetXEndPixel(current_x_tile);
            size_t start_y = scene_one.GetYStartPixel(current_y_tile);
            size_t end_y =scene_one.GetYEndPixel(current_y_tile);
            ci::Rectf drawRect(start_x, start_y, end_x, end_y);
            ci::gl::draw(mBackground_, drawRect);
            teemo_default->draw(start_x, start_y, end_x, end_y);
        }
    }
    //ci::Rectf drawRect(0, 0, 64, 64);
    //ci::gl::draw(mBackground_, drawRect);
    teemo_default->draw();
    teemo_attack->draw(704,448,768,512);
     */

    std::vector<std::vector<mylibrary::Tile>> tiles;
    for (size_t current_y_tile = 1; current_y_tile <= scene_one.GetMaxYTiles(); current_y_tile++) {
        std::vector<mylibrary::Tile> row;
        for (size_t current_x_tile = 1; current_x_tile <= scene_one.GetMaxXTiles(); current_x_tile++) {
           row.emplace_back();
        }
        tiles.push_back(row);
    }

    for (size_t current_y_tile = 1; current_y_tile <= scene_one.GetMaxYTiles(); current_y_tile++) {
        for (size_t current_x_tile = 1; current_x_tile <= scene_one.GetMaxXTiles(); current_x_tile++) {
            size_t start_x = scene_one.GetXStartPixel(current_x_tile);
            size_t end_x = scene_one.GetXEndPixel(current_x_tile);
            size_t start_y = scene_one.GetYStartPixel(current_y_tile);
            size_t end_y =scene_one.GetYEndPixel(current_y_tile);
            ci::Rectf drawRect(start_x, start_y, end_x, end_y);
            ci::gl::draw(tiles[current_y_tile - 1][ current_x_tile - 1].GetStillMapImage(), drawRect);
        }
    }

    /*
    std::vector<std::vector<std::string>> map_types;
    std::ifstream file_reader("stage_one.txt");
    if (file_reader.is_open()) {
        std::cout << "file open";
        std::string line_to_read;
        bool is_map_section = true;
        while (std::getline(file_reader, line_to_read)) {
            if (is_map_section) {
                std::vector <std::string> row;
                std::string current_type;
                if (line_to_read.empty()) {
                    is_map_section = false;
                }
                for (size_t index = 0; index < line_to_read.size(); index += 3) {
                    current_type = line_to_read.substr(index, 3);
                    row.push_back(current_type);
                }
                map_types.push_back(row);
            }
        }
    }

    */


    //scene_one.draw();


    for (size_t current_y_tile = 1; current_y_tile <= scene_one.GetMaxYTiles(); current_y_tile++) {
        for (size_t current_x_tile = 1; current_x_tile <= scene_one.GetMaxXTiles(); current_x_tile++) {
            size_t start_x = scene_one.GetXStartPixel(current_x_tile);
            size_t end_x = scene_one.GetXEndPixel(current_x_tile);
            size_t start_y = scene_one.GetYStartPixel(current_y_tile);
            size_t end_y = scene_one.GetYEndPixel(current_y_tile);
            ci::Rectf drawRect(start_x, start_y, end_x, end_y);
            ci::gl::draw(mBackground_, drawRect);
            teemo_default->draw(start_x, start_y, end_x, end_y);
        }
    }


    /*

    for (size_t current_y_tile = 1; current_y_tile <= scene_one.GetMaxYTiles(); current_y_tile++) {
        for (size_t current_x_tile = 1; current_x_tile <= scene_one.GetMaxXTiles(); current_x_tile++) {
            size_t start_x = scene_one.GetXStartPixel(current_x_tile);
            size_t end_x = scene_one.GetXEndPixel(current_x_tile);
            size_t start_y = scene_one.GetYStartPixel(current_y_tile);
            size_t end_y =scene_one.GetYEndPixel(current_y_tile);
            ci::Rectf drawRect(start_x, start_y, end_x, end_y);
            ci::gl::draw(scene_one.GetTileMap()[current_y_tile - 1][ current_x_tile - 1].GetStillMapImage(), drawRect);
        }
    }
     */
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
