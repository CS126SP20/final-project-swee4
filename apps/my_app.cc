// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "mylibrary/ciAnimatedGif.h"

#include <cinder/app/App.h>
#include <mylibrary/playing_field.h>
#include <fstream>
#include <iostream>


namespace myapp {

using cinder::app::KeyEvent;
    using cinder::Color;
    using cinder::TextBox;
    using cinder::ColorA;

    cinder::ciAnimatedGifRef mGif;
    cinder::ciAnimatedGifRef teemo_default;
    cinder::ciAnimatedGifRef teemo_attack;

MyApp::MyApp() { }

void MyApp::setup() {
    mBackground_ = cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("grass.png")));
    mGif = cinder::ciAnimatedGif::create( loadAsset("cherry-blossom.gif"));
    teemo_default = cinder::ciAnimatedGif::create( loadAsset("beemo default.gif"));
    teemo_attack = cinder::ciAnimatedGif::create( loadAsset("beemo attack.gif"));
    scene_one = mylibrary::PlayingField();
    ci::app::setWindowSize(12*64,12*64);
    //scene_one = mylibrary::PlayingField("stage_one.txt");

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


    std::string parsed_file = "cheese";

    /** THIS WORKS DONT TOUCH **/
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
                } else {
                    for (size_t index = 0; index < line_to_read.size() - 1; index += 3) {
                        current_type = line_to_read.substr(index, 3);
                        row.push_back(current_type);
                    }
                    map_types.push_back(row);
                }
            }
        }
    }

    std::vector<std::vector<mylibrary::Tile>> tiles;
    for (size_t current_y_tile = 1; current_y_tile <= scene_one.GetMaxYTiles(); current_y_tile++) {
        std::vector<mylibrary::Tile> row;
        for (size_t current_x_tile = 1; current_x_tile <= scene_one.GetMaxXTiles(); current_x_tile++) {
           row.emplace_back(mylibrary::Tile(" G ", "BEE"));
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
            tiles[current_y_tile - 1][current_x_tile - 1].GetDynamicImage()->draw(start_x,start_y,end_x,end_y);
        }
    }

     */
    /** END OF DONT TOUCH **/

    //------------- WORKS ON FIRST LINE ONLY

    /*
    std::string parsed_file = "cheese";

    std::vector<std::vector<std::string>> map_types;
    std::ifstream file_reader;
    file_reader.open(getAssetPath( "stage_one.txt"));
    if (!file_reader) {
        parsed_file = "didn't read";
    }

    if (file_reader.is_open()) {
        std::string line_to_read;
        bool is_map_section = true;
        std::vector<std::string> row;
        while (std::getline(file_reader, line_to_read)) {
            std::string current_type;
            for (size_t index = 0; index < line_to_read.size() - 1; index += 3) {
                current_type = line_to_read.substr(index, 3);
                row.push_back(current_type);
            }
            map_types.push_back(row);
            file_reader.close();
        }
        std::vector<std::string> ending;
        ending.push_back("end");
        map_types.push_back(ending);
    }


    for (std::vector<std::string> row : map_types) {
        for (std::string current : row) {
            parsed_file += current;
        }
    }

     */
    //------------ END OF WORKS ON FIRST LINE ONLY

    //------------ BEGIN OF WORKS ON FIRST THREE CHARACTERS ONLY

    /*
    std::string parsed_file = "cheese";

    std::vector<std::vector<std::string>> map_types;
    std::ifstream file_reader;
    file_reader.open(getAssetPath( "stage_one.txt"));
    if (!file_reader) {
        parsed_file = "didn't read";
    }
        std::string line_to_read;
        while (std::getline(file_reader, line_to_read)) {
            std::vector<std::string> row;
            for (size_t index = 0; index < 3; index += 3) {
                std::string current_type;
                current_type = line_to_read.substr(index, 3);
                row.push_back(current_type);
            }
            map_types.push_back(row);
            //file_reader.close();
        }
        std::vector<std::string> ending;
        ending.emplace_back("end");
        map_types.push_back(ending);


    for (std::vector<std::string> row : map_types) {
        for (std::string current : row) {
            parsed_file += current;
        }
    }

     */
    //------------ END OF WORKS ON FIRST THREE CHARACTERS ONLY


    /*
    std::string parsed_file = "cheese";

    std::vector<std::vector<std::string>> map_types;
    std::ifstream file_reader;
    file_reader.open(getAssetPath( "stage_one.txt"));
    if (!file_reader) {
        parsed_file = "didn't read";
    }
    std::string line_to_read;
    while (std::getline(file_reader, line_to_read)) {
        std::vector<std::string> row;
        for (size_t index = 0; index < 3; index += 3) {
            std::string current_type;
            current_type = line_to_read.substr(index, 3);
            row.push_back(current_type);
        }
        map_types.push_back(row);
        //file_reader.close();
    }
    std::vector<std::string> ending;
    ending.emplace_back("end");
    map_types.push_back(ending);


    for (std::vector<std::string> row : map_types) {
        for (std::string current : row) {
            parsed_file += current;
        }
    }
    */



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


    /*
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
     */

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
