// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_SCENE_H_
#define FINALPROJECT_MYLIBRARY_SCENE_H_

#include <string>
#include <vector>
#include <mylibrary/tile.h>

namespace mylibrary {
    using std::string;
    using std::vector;
    class PlayingField {
    public:
        PlayingField();
        PlayingField(const string& file_name);
        size_t GetMaxXTiles();
        size_t GetMaxYTiles();
        size_t GetMaxXPixels();
        size_t GetMaxYPixels();
        size_t GetXStartPixel(size_t current_x_tile);
        size_t GetYStartPixel(size_t current_y_tile);
        size_t GetXEndPixel(size_t current_x_tile);
        size_t GetYEndPixel(size_t current_y_tile);
        void draw();
        vector<vector<Tile>> GetTileMap();
        Tile GetTile(size_t x_index, size_t y_index);
    private:
        vector<vector<Tile>> tiles;
        size_t tile_size{};
        size_t max_x_tiles{};
        size_t max_y_tiles{};
        size_t max_x_pixels{};
        size_t max_y_pixels{};
        void SetupTiles();
};
}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_SCENE_H_
