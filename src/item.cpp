// Copyright (c) 2020 [Sue Wee]. All rights reserved.

#include <mylibrary/item.h>

namespace mylibrary {
Item::Item() {
    buff_acronym = "NA";
    buff = "none";
    image = cinder::ciAnimatedGif::create( ci::app::loadAsset("temp revealed.gif"));
    value = 0;
}

Item::Item(const string& dynamic_type) {
    buff_acronym = dynamic_type.substr(0,2);
    if (buff_acronym == "AP") {
        buff = "ABILITY POWER";
    } else if (buff_acronym == "HP") {
        buff = "HEALTH";
    } else if (buff_acronym == "BE") {
        buff = "AMMO";
    }

    // these will all be assigned their respective images and values later
    if (dynamic_type == "BEE") {
        name = "BEE";
        image = cinder::ciAnimatedGif::create( ci::app::loadAsset("bee.gif"));
        value = 1;
    } else if (dynamic_type == "AP1") {
        name = "BLASTING WAND";
        image = cinder::ciAnimatedGif::create( ci::app::loadAsset("temp revealed.gif"));
        value = 10;
    } else if (dynamic_type == "AP2") {
        name = "RABADON'S DEATHCAP";
        image = cinder::ciAnimatedGif::create( ci::app::loadAsset("temp revealed 2.gif"));
        value = 30;
    } else if (dynamic_type == "HP1") {
        name = "RUBY CRYSTAL";
        image = cinder::ciAnimatedGif::create( ci::app::loadAsset("temp revealed.gif"));
        value = 10;
    } else if (dynamic_type == "HP2") {
        name = "WARMOG'S ARMOR";
        image = cinder::ciAnimatedGif::create( ci::app::loadAsset("temp revealed 2.gif"));
        value = 30;
    }
}

cinder::ciAnimatedGifRef Item::GetImage() {
    return image;
}

string Item::GetBuff() {
    return buff;
}

string Item::GetBuffAcronym() {
    return buff_acronym;
}

size_t Item::GetValue() {
    return value;
}

string Item::GetDescription() {
    return "It's a " + name + "! If you add this to your inventory, it will increase your " + buff + " by " +
           std::to_string(value) + "!";
}

string Item::GetInteractionInstructions() {
    return "\nAdd it to your inventory by pressing [SPACE] or [E].";
}

}  // namespace mylibrary
