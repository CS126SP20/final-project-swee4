// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_TILE_H_
#define FINALPROJECT_MYLIBRARY_TILE_H_

#include "mylibrary/ciAnimatedGif.h"

namespace mylibrary {

    using std::string;

    class Tile {
    public:
        Tile();
        Tile(const string& map_type, const string& dynamic_type);
        void setMapType(const string& map_type_input);
        void setDynamicType(const string& dynamic_type_input);
        cinder::gl::Texture2dRef GetStillMapImage();
        cinder::ciAnimatedGifRef GetDynamicImage();
        bool IsSolid();
        bool IsDynamic();
        bool IsUndiscovered();
        bool IsUndefeated();
        string GetMapType();
        string GetDynamicType();

    private:
        string map_type;
        string dynamic_type;
        bool is_solid;
        cinder::gl::Texture2dRef still_map_image;
        bool is_dynamic;
        bool is_undiscovered;
        bool is_undefeated;
        cinder::ciAnimatedGifRef dynamic_image;
    };
}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_TILE_H_
