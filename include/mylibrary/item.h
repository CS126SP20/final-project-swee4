// Copyright (c) 2020 [Sue Wee]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_ITEM_H_
#define FINALPROJECT_MYLIBRARY_ITEM_H_

#include "mylibrary/ciAnimatedGif.h"
#include <string>

namespace mylibrary {

using std::string;

/**
 * Class to represent items that the character is able to pick up and update their stats with, or add to
 * their inventory.
 */
class Item {

public:

    /**
     * Default constructor for an Item, which sets most values to be empty except for the image, which it sets to a
     * bee by default, which was arbitrarily chosen. This constructor is necessary for the program to run.
     */
    Item();

    /**
     * Creates an item based on the dynamic type that is passed down from the Tile class during Tile dynamic type
     * assignment.
     * @param dynamic_type The string representation of the dynamic type that is represented by the item.
     */
    Item(const string& dynamic_type);

    /**
     * Gets the gif of the item.
     * @return Visual of the item.
     */
    cinder::ciAnimatedGifRef& GetImage();

    /**
     * Gets the acronym for the buff category that the item corresponds to, which is based on the first two letters
     * of the dynamic type string that is loaded in from the maps.
     * @return Acronym for the buff category of the item.
     */
    string GetBuffAcronym();

    /**
     * Gets the value of how much the item will increase the character's current stats that aligns with the category
     * of the buff, if the character were to pick up the item.
     * @return Value of how much the character's stats will increase in the corresponding buff's category.
     */
    size_t GetValue();

    /**
     * Gets the description of the item, which contains the name, its buff's category, and the value of the buff,
     * excluding bees. Bees will use the description that is assigned in the Tile class.
     * @return Description of the item.
     */
    string GetDescription();

    /**
     * Instructions on how to interact with the item.
     * @return Instruction of how to pick up the item.
     */
    string GetInteractionInstructions();

private:
    /** Gif representation of the item. **/
    cinder::ciAnimatedGifRef image;

    /** Acronym of the buff that corresponds to the item. **/
    string buff_acronym;

    /** Buff category that corresponds to the item. **/
    string buff;

    /** Value of how much the character's corresponding stat will increase if they were to pick up the item.**/
    size_t value;

    /** Description of the item. **/
    string description;

    /** Name of the item. **/
    string name;

    /** Instructions on how to interact with the item. **/
    string interaction_instructions;

    /**
     * Assign the name, image, and value of the item based on the dynamic type that it is.
     * @param dynamic_type Dynamic type derived from the text file of the scene loaded in.
     */
    void AssignNameImageAndValue(const string& dynamic_type);
};

}  // namespace mylibrary

#endif // FINALPROJECT_MYLIBRARY_ITEM_H_
