// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/character.h>

namespace mylibrary {

    Character::Character() {
        current_x_tile = 1;
        current_y_tile = 1;
        tile_length = 64;
        current_image = cinder::ciAnimatedGif::create( ci::app::loadAsset("beemo default.gif"));
    }

    Character::Character(size_t start_x_tile, size_t start_y_tile, size_t tile_size, string image_file_name) {
        current_x_tile = start_x_tile;
        current_y_tile = start_y_tile;
        tile_length = tile_size;
        current_image = cinder::ciAnimatedGif::create( ci::app::loadAsset(image_file_name));
    }

    size_t Character::GetXTile() {
        return current_x_tile;
    }

    size_t Character::GetYTile() {
        return current_y_tile;
    }

    void Character::SetXTile(size_t tile_index) {
        current_x_tile = tile_index;
    }

    void Character::SetYTile(size_t tile_index) {
        current_y_tile = tile_index;
    }

    size_t Character::GetXStartPixel(){
        return (current_x_tile - 1) * tile_length;
    }
    size_t Character::GetYStartPixel(){
        return (current_y_tile - 1) * tile_length;
    }

    size_t Character::GetXEndPixel() {
        return current_x_tile * tile_length;
    }
    size_t Character::GetYEndPixel() {
        return current_y_tile * tile_length;
    }

    cinder::ciAnimatedGifRef Character::GetImage() {
        return current_image;
    }

    void Character::SetImage(string orientation) {
        if (orientation == "up") {
            current_image = cinder::ciAnimatedGif::create( ci::app::loadAsset("beemo up.gif"));
        } else if (orientation == "down") {
            current_image = cinder::ciAnimatedGif::create( ci::app::loadAsset("beemo down.gif"));
        } else if (orientation == "right") {
            current_image = cinder::ciAnimatedGif::create( ci::app::loadAsset("beemo default.gif"));
        } else if (orientation == "left") {
            current_image = cinder::ciAnimatedGif::create( ci::app::loadAsset("beemo left.gif"));
        }
    }

}  // namespace mylibrary
