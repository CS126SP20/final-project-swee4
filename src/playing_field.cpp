// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/playing_field.h>
#include <iostream>
#include <fstream>

namespace mylibrary {
    using std::ifstream;

    PlayingField::PlayingField() {
        tile_size = 64;
        max_x_tiles = 12;
        max_y_tiles = 8;
        max_x_pixels = max_x_tiles * tile_size;
        max_y_pixels = max_y_tiles * tile_size;
    }

PlayingField::PlayingField(const string& file_name) {
    tile_size = 64;
    max_x_tiles = 12;
    max_y_tiles = 8;
    max_x_pixels = max_x_tiles * tile_size;
    max_y_pixels = max_y_tiles * tile_size;
    vector<vector<string>> map_types;
    vector<vector<string>> dynamic_types;

    /**
    ifstream file_reader(file_name);
    if (file_reader.is_open()) {
        std::cout << "file open";
        string line_to_read;
        bool is_map_section = true;
        while (std::getline(file_reader, line_to_read)) {
            if (is_map_section) {
                vector<string> row;
                string current_type;
                if (line_to_read.size() == 0) {
                    is_map_section = false;
                }
                for (size_t index = 0; index < line_to_read.size(); index += 3) {
                    current_type = line_to_read.substr(index, 3);
                    row.push_back(current_type);
                }
                map_types.push_back(row);
            }

     **/
            /*
             * else {
                vector<string> row;
                string current_type;
                for (size_t index = 0; index < line_to_read.size(); index += 3) {
                    current_type = line_to_read.substr(index, 3);
                    row.push_back(current_type);
                }
                dynamic_types.push_back(row);
            }

             */

    std::ifstream file_reader("stage_one.txt");
    if (file_reader.is_open()) {
        std::string line_to_read;
        bool is_map_section = true;
        while (std::getline(file_reader, line_to_read)) {
            if (is_map_section) {
                std::vector<std::string> row;
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

            for (size_t row = 0; row < 8; row++) {
                vector<Tile> tile_row;
                for (size_t col = 0; col < 12; col++) {
                    string current_map_type = map_types[row][col];
                    //string current_dynamic_type = dynamic_types[col][row];
                    string current_dynamic_type = "BEE";
                    tile_row.emplace_back(current_map_type, current_dynamic_type);
                }
                tiles.push_back(tile_row);
            }
        }
    }
}

void PlayingField::draw() {
    for (size_t row = 0; row < GetMaxYTiles(); row++) {
        for (size_t col = 0; col < GetMaxXTiles(); col++) {
            size_t start_x = GetXStartPixel(col);
            size_t end_x = GetXEndPixel(col);
            size_t start_y = GetYStartPixel(row);
            size_t end_y = GetYEndPixel(row);
            ci::Rectf drawRect(start_x, start_y, end_x, end_y);
            ci::gl::draw(tiles[row][col].GetStillMapImage(), drawRect);
            //not all tiles are dynamic
            //tiles[row][col].GetDynamicImage()->draw(start_x, start_y, end_x, end_y);
        }
    }
    }

    vector<vector<Tile>> PlayingField::GetTileMap() {
        return tiles;
    }

    size_t PlayingField::GetMaxXTiles() {
        return max_x_tiles;
    }

    size_t PlayingField::GetMaxYTiles(){
        return max_y_tiles;
    }
    size_t PlayingField::GetMaxXPixels(){
        return max_x_pixels;
    }
    size_t PlayingField::GetMaxYPixels(){
        return max_y_pixels;
    }
    size_t PlayingField::GetXStartPixel(size_t current_x_tile){
        return (current_x_tile - 1) * tile_size;
    }
    size_t PlayingField::GetYStartPixel(size_t current_y_tile){
        return (current_y_tile - 1) * tile_size;
    }

    size_t PlayingField::GetXEndPixel(size_t current_x_tile) {
        return current_x_tile * tile_size;
    }
    size_t PlayingField::GetYEndPixel(size_t current_y_tile) {
        return current_y_tile * tile_size;
    }

}  // namespace mylibrary
