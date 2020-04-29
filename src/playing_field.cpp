// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/playing_field.h>
#include <iostream>
#include <fstream>

namespace mylibrary {
    using std::ifstream;
    using ci::app::getAssetPath;

    PlayingField::PlayingField() {
        SetupTiles();
    }

PlayingField::PlayingField(const string& file_name) {
        SetupTiles();

    vector<string> map_types;
    vector<string> dynamic_types;
    ifstream file_reader;
    file_reader.open(getAssetPath(file_name));
    bool is_map_section = true;
    std::string line_to_read;
    while (getline(file_reader, line_to_read)) {
        if (line_to_read.empty()) {
            is_map_section = false;
        } else if (is_map_section) {
            map_types.push_back(line_to_read.substr(0, line_to_read.size() - 1));
        } else {
            dynamic_types.push_back(line_to_read.substr(0, line_to_read.size() - 1));
        }
    }

    for (size_t row = 0; row < GetMaxYTiles(); row++) {
        vector<Tile> current_row;
        size_t col = 0;
        for (size_t index = 0; index < map_types[0].size(); index += 3) {
            string current_map_type = map_types[row].substr(index,3);
            tiles[row][col].setMapType(current_map_type);
            col++;
        }
    }

    for (size_t row = 0; row < GetMaxYTiles(); row++) {
        vector<Tile> current_row;
        size_t col = 0;
        for (size_t index = 0; index < dynamic_types[0].size(); index += 3) {
            string current_dynamic_type = dynamic_types[row].substr(index,3);
            tiles[row][col].setDynamicType(current_dynamic_type);
            col++;
        }
    }
}

//TODO: move to bottom of page bc it's private
void PlayingField::SetupTiles() {
        tile_size = 64;
        max_x_tiles = 12;
        max_y_tiles = 8;
        max_x_pixels = max_x_tiles * tile_size;
        max_y_pixels = max_y_tiles * tile_size;

        for (size_t row = 0; row < GetMaxYTiles(); row++) {
            vector<Tile> current_row;
            for (size_t col = 0; col < GetMaxXTiles(); col++) {
                Tile tile("   ", " . ");
                current_row.push_back(tile);
            }
            tiles.push_back(current_row);
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
