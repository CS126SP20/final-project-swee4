// Copyright (c) 2020 [Sue Wee]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_ITEM_H_
#define FINALPROJECT_MYLIBRARY_ITEM_H_

#include "mylibrary/ciAnimatedGif.h"
#include <string>

namespace mylibrary {
    using std::string;
    class Item {
public:
    Item();
    Item(const string& dynamic_type);
    cinder::ciAnimatedGifRef GetImage();
    string GetBuff();
    string GetBuffAcronym();
    size_t GetValue();
    string GetDescription();
    string GetInteractionInstructions();
private:
    cinder::ciAnimatedGifRef image;
    string buff_acronym;
    string buff;
    size_t value;
    string description;
    string name;
    string interaction_instructions;

};
}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_ITEM_H_
