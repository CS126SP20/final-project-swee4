// Copyright (c) 2020 [Sue Wee]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_TILE_H_
#define FINALPROJECT_MYLIBRARY_TILE_H_

#include "mylibrary/ciAnimatedGif.h"
#include <mylibrary/item.h>

namespace mylibrary {
using std::string;

class Tile {
public:
    Tile();
    Tile(const string& map_type, const string& dynamic_type);
    void setMapType(const string& map_type_input);
    void setDynamicType(const string& dynamic_type_input);
    cinder::gl::Texture2dRef GetStillMapImage();
    bool IsSolid();
    bool IsDynamic();
    cinder::ciAnimatedGifRef GetDynamicImage();
    bool IsUndiscovered();
    bool IsUndefeated();
    bool IsTeleport();
    string GetMapType();
    string GetDynamicType();
    Item GetItem();
    void Reveal();
    void Remove();
    string GetDescription();
    string GetInteractionInstructions();

private:
    string map_type;
    string dynamic_type;
    bool is_solid;
    cinder::gl::Texture2dRef still_map_image;
    bool is_dynamic;
    bool is_undiscovered;
    bool is_undefeated;
    bool is_teleport;
    cinder::ciAnimatedGifRef dynamic_image;
    Item item;
    string description;
    string interaction_instructions;
};
}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_TILE_H_
