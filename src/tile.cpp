// Copyright (c) 2020 [Sue Wee]. All rights reserved.

#include <mylibrary/tile.h>


namespace mylibrary {

    Tile::Tile() {
        still_map_image = cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("grass.png")));
        dynamic_image = cinder::ciAnimatedGif::create( ci::app::loadAsset("beemo default.gif"));
    }

Tile::Tile(const string& map_type_input, string& dynamic_type_input) {
    map_type = map_type_input;
    dynamic_type = dynamic_type_input;
    is_solid = true;
    //individually creating images in case future use is to be replaced with gifs, using moving_map_image;
    if (map_type == " G ") {
        still_map_image = cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("grass.png")));
        is_solid = false;
    } else if (map_type == " L ") {
        still_map_image = cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("lane.png")));
        is_solid = false;
    } else if (map_type == " H ") {
        still_map_image = cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("horizontal wall.png")));
    } else if (map_type == " V ") {
        still_map_image = cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("vertical wall.png")));
    } else if (map_type == " R ") {
        still_map_image = cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("river.png")));
    }

    if (dynamic_type_input == " . ") {
        is_undiscovered = false;
        is_undefeated = false;
        is_dynamic = false;
        // MAKE SURE THIS ISN'T DRAWN
        dynamic_image = nullptr;
        is_solid = false;
    } else if (dynamic_type_input == "BEE") {
        is_undiscovered = false;
        is_undefeated = false;
        is_dynamic = true;
        //should be bee gif
        dynamic_image = cinder::ciAnimatedGif::create( ci::app::loadAsset("beemo default.gif"));
    } else {
        is_dynamic = true;
        if (dynamic_type_input[2] == '1') {
            //should be twinkle gif
            dynamic_image = cinder::ciAnimatedGif::create( ci::app::loadAsset("beemo default.gif"));
            is_undiscovered = true;
            is_undefeated = false;
        } else if (dynamic_type_input[2] == '2') {
            //should be minion gif
            dynamic_image = cinder::ciAnimatedGif::create( ci::app::loadAsset("beemo default.gif"));
            is_undiscovered = false;
            is_undefeated = true;
        }
    }
}

cinder::gl::Texture2dRef Tile::GetStillMapImage() {
    return still_map_image;
}

cinder::ciAnimatedGifRef Tile::GetDynamicImage() {
    return dynamic_image;
    //TODO: setters to update dynamic image after interaction
}

bool Tile::IsSolid() {
    return is_solid;
}

bool Tile::IsDynamic() {
    return is_dynamic;
}

    bool Tile::IsUndiscovered(){
    return is_undiscovered;
}
    bool Tile::IsUndefeated(){
    return is_undefeated;

}
    string Tile::GetMapType(){
    return map_type;

}
    string Tile::GetDynamicType(){
    return dynamic_type;

}
}  // namespace mylibrary
