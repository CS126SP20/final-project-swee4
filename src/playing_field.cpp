// Copyright (c) 2020 [Sue Wee]. All rights reserved.

#include <iostream>
#include <mylibrary/playing_field.h>

namespace mylibrary {

using ci::app::getAssetPath;
using std::ifstream;

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
            if (current_dynamic_type == "END") {
                boss_tiles.push_back(tiles[row][col]);
            }
            tiles[row][col].setDynamicType(current_dynamic_type);
            col++;
        }
    }
}

void PlayingField::draw() {
    for (size_t current_y_tile = 1; current_y_tile <= GetMaxYTiles(); current_y_tile++) {
        for (size_t current_x_tile = 1; current_x_tile <= GetMaxXTiles(); current_x_tile++) {
            mylibrary::Tile current_tile = tiles[current_y_tile - 1][current_x_tile - 1];
            size_t start_x = GetXStartPixel(current_x_tile);
            size_t end_x = GetXEndPixel(current_x_tile);
            size_t start_y = GetYStartPixel(current_y_tile);
            size_t end_y = GetYEndPixel(current_y_tile);
            ci::Rectf drawRect(start_x, start_y, end_x, end_y);
            ci::gl::draw(current_tile.GetStillMapImage(), drawRect);
            if (current_tile.IsDynamic()) {
                current_tile.GetDynamicImage()->draw(start_x, start_y, end_x, end_y);
            }
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

Tile PlayingField::GetTile(size_t x_index, size_t y_index) {
    return tiles[y_index - 1][x_index - 1];
}

bool PlayingField::operator==(const PlayingField& rhs) {
    PlayingField other = rhs;
    vector<vector<Tile>> other_tile_map = other.GetTileMap();
    if (tiles.size() != other_tile_map.size()) {
        return false;
    }
    for (size_t row = 0; row < tiles.size(); row++) {
        if (tiles[row].size() != other_tile_map[row].size()) {
            return false;
        }
        for (size_t col = 0; col < tiles[row].size(); col++) {
            if (tiles[row][col].GetMapType() != other_tile_map[row][col].GetMapType()) {
                return false;
            }
        }

    }
    return true;
}

void PlayingField::Reveal(size_t x_index, size_t y_index) {
    tiles[y_index - 1][x_index - 1].Reveal();
}

void PlayingField::Remove(size_t x_index, size_t y_index) {
    tiles[y_index - 1][x_index - 1].Remove();
}

void PlayingField::SetupTiles() {
    tile_size = 64;
    max_x_tiles = 12;
    max_y_tiles = 8;

    for (size_t row = 0; row < GetMaxYTiles(); row++) {
        vector<Tile> current_row;
        for (size_t col = 0; col < GetMaxXTiles(); col++) {
            Tile tile("   ", " . ");
            current_row.push_back(tile);
        }
        tiles.push_back(current_row);
    }
}

}  // namespace mylibrary
