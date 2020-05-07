// Copyright (c) 2020 [Sue Wee]. All rights reserved.

#include <mylibrary/item.h>

namespace mylibrary {

    const string kAbilityPowerAcronym = "AP";

    const string kHealthAcronym = "HP";

    const string kAmmunitionAcronym = "BE";

Item::Item() :
    buff_acronym (""),
    buff(""),
    value(0)
    {image = cinder::ciAnimatedGif::create( ci::app::loadAsset("dynamic_types/bee.gif"));}

Item::Item(const string& dynamic_type) {
    size_t acronym_length = 2;
    buff_acronym = dynamic_type.substr(0,acronym_length);
    if (buff_acronym == kAbilityPowerAcronym) {
        buff = "ABILITY POWER";
    } else if (buff_acronym == kHealthAcronym) {
        buff = "HEALTH";
    } else if (buff_acronym == kAmmunitionAcronym) {
        buff = "AMMO";
    }
    AssignNameImageAndValue(dynamic_type);
    description = "It's a " + name + "! If you add this to your inventory, it will increase your " + buff + " by " +
                  std::to_string(value) + "!";
    interaction_instructions = "\nAdd it to your inventory by pressing [SPACE] or [E].";
}

cinder::ciAnimatedGifRef& Item::GetImage() {
    return image;
}

string Item::GetBuffAcronym() {
    return buff_acronym;
}

size_t Item::GetValue() {
    return value;
}

string Item::GetDescription() {
    return description;
}

string Item::GetInteractionInstructions() {
    return interaction_instructions;
}

void Item::AssignNameImageAndValue(const string& dynamic_type) {
    const char sparkle_indicator = '1';
    const char minion_indicator = '2';
    // All items aside from the bee are sourced from: https://leagueoflegends.fandom.com/wiki/League_of_Legends_Wiki
    if (dynamic_type == kAmmunitionAcronym + "E") {
        name = "BEE";
        image = cinder::ciAnimatedGif::create( ci::app::loadAsset("dynamic_types/bee.gif"));
        value = 1;
    } else if (dynamic_type == kAbilityPowerAcronym + sparkle_indicator) {
        name = "BLASTING WAND";
        image = cinder::ciAnimatedGif::create( ci::app::loadAsset("items/blasting wand.gif"));
        value = 10;
    } else if (dynamic_type == kAbilityPowerAcronym + minion_indicator) {
        name = "RABADON'S DEATHCAP";
        image = cinder::ciAnimatedGif::create( ci::app::loadAsset("items/rabadon's deathcap.gif"));
        value = 30;
    } else if (dynamic_type == kHealthAcronym + sparkle_indicator) {
        name = "RUBY CRYSTAL";
        image = cinder::ciAnimatedGif::create( ci::app::loadAsset("items/ruby crystal.gif"));
        value = 10;
    } else if (dynamic_type == kHealthAcronym + minion_indicator) {
        name = "WARMOG'S ARMOR";
        image = cinder::ciAnimatedGif::create( ci::app::loadAsset("items/warmog's armor.gif"));
        value = 30;
    }
}

}  // namespace mylibrary
