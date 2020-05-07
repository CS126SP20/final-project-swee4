// Copyright (c) 2020 [Sue Wee]. All rights reserved.

#include <mylibrary/tile.h>

namespace mylibrary {

Tile::Tile() :
    still_map_image(cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("map_types/blank.png")))),
    dynamic_image(cinder::ciAnimatedGif::create( ci::app::loadAsset("beemo/beemo right.gif"))),
    item(Item()),
    is_solid(false),
    is_dynamic(false),
    is_undiscovered(false),
    is_undefeated(false),
    is_teleport(false),
    description(""),
    interaction_instructions(""),
    x_tile(0),
    y_tile(0)
    {}

Tile::Tile(const string& map_type_input, const string& dynamic_type_input, size_t col, size_t row) :
    item(Item(dynamic_type_input)),
    x_tile(col),
    y_tile(row)
    {
    SetMapType(map_type_input);
    SetDynamicType(dynamic_type_input);
    }

void Tile::SetMapType(const string& map_type_input) {
    map_type = map_type_input;
    description = "";
    interaction_instructions = "";
    if (map_type == " . ") {
        still_map_image = cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("map_types/grass.png")));
        is_solid = false;
    } else if (map_type == " L ") {
        still_map_image = cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("map_types/lane.png")));
        is_solid = false;
    } else if (map_type == " H ") {
        still_map_image = cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("map_types/horizontal wall.png")));
        is_solid = true;
    } else if (map_type == " V ") {
        still_map_image = cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("map_types/vertical wall.png")));
        is_solid = true;
    } else if (map_type == " R ") {
        still_map_image = cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("map_types/river.png")));
        is_solid = true;
    } else if (map_type == "   ") {
        still_map_image = cinder::gl::Texture2d::create(loadImage(ci::app::loadAsset("map_types/blank.png")));
        is_solid = false;
    }
}

void Tile::SetDynamicType(const string& dynamic_type_input) {
    dynamic_type = dynamic_type_input;
    is_undiscovered = false;
    is_undefeated = false;
    is_dynamic = false;
    is_teleport = false;
    if (dynamic_type_input == " . ") {
        dynamic_image = nullptr;
    } else if (dynamic_type_input == "BOS") {
        dynamic_image = nullptr;
        is_solid = true;
    } else if (dynamic_type_input == "TEL") {
        is_teleport = true;
        dynamic_image = nullptr;
    } else if (dynamic_type_input == "END") {
        is_dynamic = true;
        is_solid = true;
        dynamic_image = cinder::ciAnimatedGif::create( ci::app::loadAsset("poro crying.gif"));
        description = "Your friend, the PORO!";
        interaction_instructions = "\nPress [SPACE] or [E] to continue.";
    } else if (dynamic_type_input == "BEE") {
            is_dynamic = true;
            //should be bee gif
            item = Item(dynamic_type);
            dynamic_image = item.GetImage();
            is_solid = true;
            description = "A BEE! This will help you fight enemies. But use it wisely! You cannot attack without them. ";
            interaction_instructions = "\nPick it up by pressing [SPACE] or [E].";
    } else {
        is_dynamic = true;
        is_solid = true;
        item = Item(dynamic_type);
        if (dynamic_type_input[2] == '1') {
            dynamic_image = cinder::ciAnimatedGif::create( ci::app::loadAsset("dynamic_types/sparkle.gif"));
            is_undiscovered = true;
            description = "What's this? It seems like something is hidden here. ";
            interaction_instructions = "\nReveal it by pressing [SPACE] or [E].";
        } else if (dynamic_type_input[2] == '2') {
            dynamic_image = cinder::ciAnimatedGif::create( ci::app::loadAsset("dynamic_types/minion attack.gif"));
            is_undefeated = true;
            description = "A MINION! You will need to use your BEES to fight them. "
                          "\nBut if you win, you will be lavishly rewarded! ";
            interaction_instructions = "\nFight by pressing [SPACE] or [Q].";
        }
    }
}

size_t Tile::GetXTile() {
    return x_tile;
}

size_t Tile::GetYTile() {
    return y_tile;
}

void Tile::SetXTile(size_t col) {
    x_tile = col;
}

void Tile::SetYTile(size_t row) {
    y_tile = row;
}

cinder::gl::Texture2dRef& Tile::GetStillMapImage() {
    return still_map_image;
}

cinder::ciAnimatedGifRef& Tile::GetDynamicImage() {
    return dynamic_image;
}

bool Tile::IsSolid() {
    return is_solid;
}

bool Tile::IsDynamic() {
    return is_dynamic;
}

bool Tile::IsTeleport() {
    return is_teleport;
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

Item Tile::GetItem() {
    return item;
}

void Tile::Reveal() {
    dynamic_image = item.GetImage();
    is_undefeated = false;
    is_undiscovered = false;
}

void Tile::Remove() {
    is_dynamic = false;
    is_solid = false;
    dynamic_type = " . ";
    description = "";
    interaction_instructions = "";
}

string Tile::GetDescription() {
    if (is_undefeated || is_undiscovered || dynamic_type == "BEE" || dynamic_type == "END") {
        return description;
    } else if (is_dynamic) {
        return item.GetDescription();
    }
    return description;
}

string Tile::GetInteractionInstructions() {
    if (is_undefeated || is_undiscovered || dynamic_type == "BEE" || dynamic_type == "END") {
        return interaction_instructions;
    } else if (is_dynamic) {
        return item.GetInteractionInstructions();
    }
    return interaction_instructions;
}

}  // namespace mylibrary
