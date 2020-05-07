// Copyright (c) 2020 [Sue Wee]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_TILE_H_
#define FINALPROJECT_MYLIBRARY_TILE_H_

#include "mylibrary/ciAnimatedGif.h"
#include <mylibrary/item.h>

namespace mylibrary {

using std::string;

/**
 * Class to represent a single Tile on the Playing Field. This stores all information regarding the base layer of
 * the Tile, which is the map, represented by a static image, as well as any possible dynamic layers above it,
 * which could be interactive as is or store hidden states, such as other Items that can be collected.
 */
class Tile {

public:

    /**
     * Default constructor for a Tile, which should not be used to create a Tile object, but is necessary for the
     * program to run. Mostly instantiated with arbitrary values.
     */
    Tile();

    /**
     * Constructor for the Tile, which is made by taking in the designated map type, dynamic type, and its current
     * Tile index in terms of column and row.
     * @param map_type Representation of the map type that should be assigned to this Tile.
     * @param dynamic_type Representation of the dynamic type that should be assigned to this Tile.
     * @param col Column that this Tile lies in.
     * @param row Row that this Tile lies in.
     */
    Tile(const string& map_type, const string& dynamic_type, size_t col, size_t row);

    /**
     * Sets the Tile's map type to a new type specified in the parameters.
     * @param map_type_input New map type that the Tile will be set to.
     */
    void SetMapType(const string& map_type_input);

    /**
     * Sets the Tile's dynamic type to a new type specified in the parameters.
     * @param dynamic_type_input New dynamic type that the Tile will be set to.
     */
    void SetDynamicType(const string& dynamic_type_input);

    /**
     * Returns a reference to the still image of the map on the Tile.
     * @return Still image of the map on the Tile.
     */
    cinder::gl::Texture2dRef& GetStillMapImage();

    /**
     * Indicates if the Tile is solid, which means that the character cannot pass through it.
     * @return True if the Tile is solid.
     */
    bool IsSolid();

    /**
     * Indicates if the Tile is dynamic, which means that there are some special qualities to it and it can be
     * interacted with on top of its initial map image.
     * @return True if the Tile is dynamic.
     */
    bool IsDynamic();

    /**
     * Gets the dynamic image that is assigned to the Tile.
     * Note: This should not be called without first checking if IsDynamic() is true.
     * @return Animated gif image of the dynamic type.
     */
    cinder::ciAnimatedGifRef& GetDynamicImage();

    /**
     * Indicates that the dynamic type of this Tile contains an Item that is hidden by a Sparkle.
     * @return True if the Tile has not yet been interacted with to reveal the Item.
     */
    bool IsUndiscovered();

    /**
     * Indicates that the dynamic type of this Tile contains an Item that is hidden by a Minion.
     * @return True if the Tile has not yet been interacted with to reveal the Item.
     */
    bool IsUndefeated();

    /**
     * Indicates if the Tile will load another scene by walking "off" the scene of sorts.
     * @return True if the character can load another scene by walking a certain direction while standing on the Tile.
     */
    bool IsTeleport();

    /**
     * Returns the map type of the current Tile.
     * @return Map type of current Tile.
     */
    string GetMapType();

    /**
     * Returns the dynamic type of the current Tile.
     * @return Dynamic type of current Tile.
     */
    string GetDynamicType();

    /**
     * Returns Item that is associated with the current Tile.
     * Note: This should only be called on dynamic types that can be grabbed and added to stats/inventory.
     * @return Item that is associated with the current Tile.
     */
    Item GetItem();

    /**
     * Sets the dynamic image of the Tile to be the hidden Item's image instead, and adjusts the global booleans
     * to indicate that the Tile is no longer undiscovered or undefeated.
     */
    void Reveal();

    /**
     * Empties the Tile's information and makes it so that the character can now pass through, if it used to be solid.
     * Clears all information that used to be associated with it and resets it as a blank tile, only displaying
     * the initial map type that was assigned to it.
     */
    void Remove();

    /**
     * Gets the appropriate description that is associated with the Tile.
     * @return Description of the Tile in its current state.
     */
    string GetDescription();

    /**
     * Gets the appropriate interaction instructions associated with the Tile.
     * @return Instructions on how to interact with the Tile in its current state.
     */
    string GetInteractionInstructions();

    /**
     * Gets the X-Coordinate of the current Tile.
     * @return X-Coorinate of the Tile.
     */
    size_t GetXTile();

    /**
     * Gets the Y-Coordinate of the current Tile.
     * @return Y-Coordinate of the Tile.
     */
    size_t GetYTile();

    /**
     * Sets the X-Coordinate of the Tile, which is assigned in the Playing Field Class.
     * @param col Column index of the Tile (starting from 1).
     */
    void SetXTile(size_t col);

    /**
     * Sets the Y-Coordinate of the Tile, which is assigned in the Playing Field Class.
     * @param row Row index of the Tile (starting from 1).
     */
    void SetYTile(size_t row);

private:

    /** X-Coordinate of Tile. **/
    size_t x_tile;

    /** Y-Coordinate of Tile. **/
    size_t y_tile;

    /** Map type of Tile. **/
    string map_type;

    /** Dynamic type of Tile. **/
    string dynamic_type;

    /** Whether or not the Tile is solid/not able to be passed through. **/
    bool is_solid;

    /** Image of the map that corresponds to the Tile. **/
    cinder::gl::Texture2dRef still_map_image;

    /** Whether of not the Tile is dynamic and can be interacted with. **/
    bool is_dynamic;

    /** Whether or not the Tile is a Sparkle hiding the Item beneath. **/
    bool is_undiscovered;

    /** Whether or not the Tile is a Minion hiding the Item beneath. **/
    bool is_undefeated;

    /** Whether or not the Tile is a teleportation spot, which can load another scene. **/
    bool is_teleport;

    /** Dynamic image that is associated with the Tile, to be displayed above the map type if the Tile is dynamic. **/
    cinder::ciAnimatedGifRef dynamic_image;

    /** Item associated with the Tile. **/
    Item item;

    /** Description of the Tile. **/
    string description;

    /** Instructions of how to interact with the Tile. **/
    string interaction_instructions;

};

}  // namespace mylibrary

#endif // FINALPROJECT_MYLIBRARY_TILE_H_
