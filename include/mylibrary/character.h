// Copyright (c) 2020 [Sue Wee]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_CHARACTER_H_
#define FINALPROJECT_MYLIBRARY_CHARACTER_H_

#include "mylibrary/ciAnimatedGif.h"
#include <mylibrary/item.h>
#include <string>
#include <vector>

namespace mylibrary {

using std::string;

using std::vector;

/**
 * This class represents the character that the player is able to control on screen. The character's stats are stored
 * within this class and are updated as buffs are picked up. This class also stores the player's inventory and will
 * also update the character's sprite models based on the direction that the player moves.
 */
class Character {

public:

    /**
     * Default constructor for the class, which will create a character that spawns on the top left of the screen,
     * with a pixel size of 64x64, and will be facing the right. Other stats are arbitrarily assigned.
     */
    Character();

    /**
     * Constructor that will create a character based on the tile that the character is supposed to spawn on, the size
     * of the tile (in terms of pixels) and the sprite gif of the character.
     * @param start_x_tile The X-Coordinate of the Tile that the character spawns on.
     * @param start_y_tile The Y-Coordinate of the Tile that the character spawns on.
     * @param tile_size The size that the sprite image will be resized to, in pixels.
     * @param image_file_name The file path of the image of the default starting sprite.
     */
    Character(size_t start_x_tile, size_t start_y_tile, size_t tile_size, const string& image_file_name);

    /**
     * Returns the current X-Coordinate of the character.
     * @return X-Coordinate of the character.
     */
    size_t GetXTile();

    /**
     * Returns the current Y-Coordinate of the character.
     * @return Y-Coordinate of the character.
     */
    size_t GetYTile();

    /**
     * Updates the current X-Coordinate of the character's tile to a new X-Coordinate. This method is more open
     * ended than simply MoveLeft(), MoveRight() and the like because the teleportation factor of the screen changes
     * requires the character to be set to the corresponding tile and side of map that the scene continues on, which
     * is not always adjacent to the last in terms of coordinates.
     * @param tile_index The new X-Coordinate that the character is moving to.
     */
    void SetXTile(size_t tile_index);

    /**
     * Updates the current Y-Coordinate of the character's tile to a new Y-Coordinate. This method is more open
     * ended than simply MoveUp(), MoveDown() and the like because the teleportation factor of the screen changes
     * requires the character to be set to the corresponding tile and side of map that the scene continues on, which
     * is not always adjacent to the last in terms of coordinates.
     * @param tile_index The new Y-Coordinate that the character is moving to.
     */
    void SetYTile(size_t tile_index);

    /**
     * Calculates the leftmost X-Coordinate (in pixels, not Tiles) of the character based on its current location.
     * @return Leftmost X-Coordinate of the Tile that the character is on, in pixels.
     */
    size_t GetXStartPixel();

    /**
     * Calculates the topmost Y-Coordinate (in pixels, not Tiles) of the character based on its current location.
     * @return Topmost Y-Coordinate of the Tile that the character is on, in pixels.
     */
    size_t GetYStartPixel();

    /**
     * Calculates the rightmost X-Coordinate (in pixels, not Tiles) of the character based on its current location.
     * @return Rightmost X-Coordinate of the Tile that the character is on, in pixels.
     */
    size_t GetXEndPixel();

    /**
     * Calculates the bottommost Y-Coordinate (in pixels, not Tiles) of the character based on its current location.
     * @return Bottommost Y-Coordinate of the Tile that the character is on, in pixels.
     */
    size_t GetYEndPixel();

    /**
     * Returns the gif sprite of the character, in the form of a ciAnimatedGif, from the external library.
     * @return Gif of the character sprite as a ciAnimatedGif.
     */
    cinder::ciAnimatedGifRef& GetImage();

    /**
     * Selects the corresponding ciAnimatedGif to represent the sprite based on the direction that the player has
     * moved.
     * Note: This is heavily dependent on the idea that there are multiple default sprites, attack sprites, and grabbing
     * sprites, each of which faces a different direction, and is labeled as such in the files in the assets directory.
     * @param orientation The direction that the sprite should be facing, based on a corresponding string input that is
     *                    stored upon keypress of a directional button.
     */
    void SetImage(const string& orientation);

    /**
     * Returns the string representation of the direction that the character is currently facing. The orientation
     * is facing the "right" by default, but otherwise it will be set to the most recent direction change.
     * @return Direction that the character is currently facing.
     */
    string GetOrientation();

    /**
     * Sets the current sprite of the character to the uncover action (used to reveal minions and sparkles specifically)
     * based on the character's current orientation.
     */
    void Uncover();

    /**
     * Sets the current sprite of the character to the grab action (used to collect items/buffs) based on the
     * character's current orientation. It will also update the character's current stats by adding the corresponding
     * buffs and values of the item that is being grabbed, and adds the item to the inventory.
     * @param item_to_grab Item that the character is collecting.
     */
    void Grab(mylibrary::Item item_to_grab);

    /**
     * Depletes one quantity of the collected ammunition that the character has been storing, to represent using
     * an attack.
     * Note: This method should only be called when it is ensured that the current quantity of collected ammunition is
     * greater than 0.
     */
    void UseAmmo();

    /**
     * Gets the current inventory of items that the character has collected.
     * @return The character's current inventory of items.
     */
    vector<Item> GetInventory();

    /**
     * Checks if the inventory has reached the maximum capacity, which is by default at 6 items. This should be checked
     * with the DrawInventory() method in beemos_rescue.cc to ensure that the inventory slots align with the
     * visual inventory row * columns.
     * @return True if the inventory has reached its size capacity.
     */
    bool IsInventoryFull();

    /**
     * Returns the total Ability Power of the character, which also happens to be the damage that they do to enemies.
     * @return Current Ability Power of the character.
     */
    size_t GetTotalAP();

    /**
     * Returns the total Health of the character, which also happens to be the damage that they do to enemies.
     * @return Total Health of the character.
     */
    size_t GetTotalHP();

    /**
     * Returns the current Health of the character, which also happens to be the damage that they do to enemies.
     * @return Current Health of the character.
     */
    size_t GetCurrentHP();

    /**
     * Returns the total number of collected ammo that the character has available at the moment.
     * @return Quantity of ammunition that the character has stored thus far.
     */
    size_t GetCurrentAmmoCount();

    /**
     * Decreases character's health by a designated value. If the value were to push the current health to be
     * negative (checked by whether the value is greater than the current health) then the current health becomes
     * set to 0.
     * @param damage_value Damage that the character is taking to their Health.
     */
    void TakeDamage(size_t damage_value);

    private:

    /** Current X-Index of the Tile, with a minimum of 1. **/
    size_t current_x_tile;

    /** Current Y-Index of the Tile, with a minimum of 1. **/
    size_t current_y_tile;

    /** Length of tiles in terms of pixels. **/
    size_t tile_length;

    /** Current image representation of the sprite, based on orientation and action movement. **/
    cinder::ciAnimatedGifRef current_image;

    /** Current direction that the sprite is facing. **/
    string orientation;

    /** Current Ability Power of the character, updated when picking up AP buffs. **/
    size_t ap;

    /** Total possible Health of the character, updated when picking up HP buffs. **/
    size_t total_hp;

    /** Current Health of the character, updated when picking up HP buffs and upon taking damage. **/
    size_t current_hp;

    /** Current count of the ammunition that the character has collected. **/
    size_t ammo;

    /** Container that stores the items (with buffs, exclusive of ammunition) that the character picks up. **/
    vector<Item> inventory;

};

}  // namespace mylibrary

#endif // FINALPROJECT_MYLIBRARY_CHARACTER_H_
