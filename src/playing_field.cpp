// Copyright (c) 2020 [Sue Wee]. All rights reserved.

#include <iostream>
#include <mylibrary/playing_field.h>

namespace mylibrary {

using ci::app::getAssetPath;

using std::ifstream;

const size_t kTileIndexOffset = 1;

PlayingField::PlayingField() :
    tile_size(64),
    max_x_tiles(12),
    max_y_tiles(8),
    is_final_boss_present(false),
    ammo_count(0)
    { SetupBlankTiles(); }

PlayingField::PlayingField(const string& file_name, size_t tile_pixels, size_t tiles_row, size_t tiles_col) :
    tile_size(tile_pixels),
    max_x_tiles(tiles_row),
    max_y_tiles(tiles_col),
    is_final_boss_present(false),
    ammo_count(0)
    {
    SetupBlankTiles();
    vector<string> map_types;
    vector<string> dynamic_types;
    StoreMapAndDynamicTypes(file_name, map_types, dynamic_types);
    AssignTileTypes(map_types, dynamic_types);
    if (is_final_boss_present) {
        final_boss = FinalBoss(boss_tiles);
    } else {
        final_boss = FinalBoss();
    }

}

void PlayingField::draw() {
    DrawScene();
    DrawFinalBossIfApplicable();
}

FinalBoss& PlayingField::GetFinalBoss() {
    return final_boss;
}

void PlayingField::DealBossDamage(size_t damage_value) {
    final_boss.TakeDamage(damage_value);
}

void PlayingField::SetBossAttackMode() {
    final_boss.AttackMode();
}

void PlayingField::SetBossDefaultMode() {
    final_boss.DefaultMode();
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
    return (current_x_tile - kTileIndexOffset) * tile_size;
}
size_t PlayingField::GetYStartPixel(size_t current_y_tile){
    return (current_y_tile - kTileIndexOffset) * tile_size;
}

size_t PlayingField::GetXEndPixel(size_t current_x_tile) {
    return current_x_tile * tile_size;
}
size_t PlayingField::GetYEndPixel(size_t current_y_tile) {
    return current_y_tile * tile_size;
}

Tile& PlayingField::GetTile(size_t x_index, size_t y_index) {
    return tiles[y_index - kTileIndexOffset][x_index - kTileIndexOffset];
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
    tiles[y_index - kTileIndexOffset][x_index - kTileIndexOffset].Reveal();
}

void PlayingField::Remove(size_t x_index, size_t y_index) {
    tiles[y_index - kTileIndexOffset][x_index - kTileIndexOffset].Remove();
}

void PlayingField::SetupBlankTiles() {
    for (size_t row = 0; row < GetMaxYTiles(); row++) {
        vector<Tile> current_row;
        for (size_t col = 0; col < GetMaxXTiles(); col++) {
            Tile tile("   ", " . ", 0, 0);
            current_row.push_back(tile);
        }
        tiles.push_back(current_row);
    }
}

size_t PlayingField::GetAmmoCount() {
    return ammo_count;
}


void PlayingField::AssignTileTypes(const vector<string>& map_types, const vector<string>& dynamic_types) {
    for (size_t row = 0; row < GetMaxYTiles(); row++) {
        vector<Tile> current_row;
        size_t col = 0;
        for (size_t index = 0; index < map_types[0].size(); index += 3) {
            string current_map_type = map_types[row].substr(index,3);
            Tile& current = tiles[row][col];
            current.SetMapType(current_map_type);
            string current_dynamic_type = dynamic_types[row].substr(index,3);
            current.SetDynamicType(current_dynamic_type);
            current.SetXTile(col + kTileIndexOffset);
            current.SetYTile(row + kTileIndexOffset);
            if (current_dynamic_type == "BOS") {
                boss_tiles.push_back(tiles[row][col]);
                if (!is_final_boss_present) {
                    is_final_boss_present = true;
                }
            } else if (current_dynamic_type == "BEE") {
                ammo_count++;
            }
            col++;
        }
    }
}

void PlayingField::StoreMapAndDynamicTypes(const string& file_name, vector<string>& map_types, vector<string>& dynamic_types) {
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
}

void PlayingField::DrawScene() {
    for (size_t current_y_tile = kTileIndexOffset; current_y_tile <= GetMaxYTiles(); current_y_tile++) {
        for (size_t current_x_tile = kTileIndexOffset; current_x_tile <= GetMaxXTiles(); current_x_tile++) {
            mylibrary::Tile& current_tile = tiles[current_y_tile - kTileIndexOffset][current_x_tile - kTileIndexOffset];
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

void PlayingField::DrawFinalBossIfApplicable() {
    if (is_final_boss_present && final_boss.GetCurrentHealth() > 0) {
        size_t min_x_pixel = GetXStartPixel(final_boss.GetMinXTile());
        size_t min_y_pixel = GetYStartPixel(final_boss.GetMinYTile());
        size_t max_x_pixel = GetXEndPixel(final_boss.GetMaxXTile());
        size_t max_y_pixel = GetYEndPixel(final_boss.GetMaxYTile());
        final_boss.GetImage()->draw(min_x_pixel,min_y_pixel,max_x_pixel,max_y_pixel);
    } else if (is_final_boss_present && final_boss.GetCurrentHealth() == 0) {
        for (Tile current : final_boss.GetOccupiedTiles()) {
            Remove(current.GetXTile(), current.GetYTile());
        }
    }
}

}  // namespace mylibrary
