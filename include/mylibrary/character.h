// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_CHARACTER_H_
#define FINALPROJECT_MYLIBRARY_CHARACTER_H_

#include <string>
#include "mylibrary/ciAnimatedGif.h"

namespace mylibrary {
    using std::string;
    class Character {
    public:
        Character();
        Character(size_t start_x_tile, size_t start_y_tile, size_t tile_size, string image_file_name);
        size_t GetXTile();
        size_t GetYTile();
        void SetXTile(size_t tile_index);
        void SetYTile(size_t tile_index);
        size_t GetXStartPixel();
        size_t GetYStartPixel();
        size_t GetXEndPixel();
        size_t GetYEndPixel();
        cinder::ciAnimatedGifRef GetImage();
        void SetImage(string orientation);
    private:
        size_t current_x_tile;
        size_t current_y_tile;
        size_t tile_length;
        cinder::ciAnimatedGifRef current_image;
    };

}  // namespace mylibrary


#endif // FINALPROJECT_CHARACTER_EXAMPLE_H_
