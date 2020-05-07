// Copyright (c) 2020 [Sue Wee]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_BOSS_H_
#define FINALPROJECT_MYLIBRARY_BOSS_H_

#include "mylibrary/ciAnimatedGif.h"
#include <mylibrary/tile.h>
#include <string>
#include <vector>

namespace mylibrary {

using std::vector;

using std::string;

/**
 * Class to represent the final boss of the game. Unique aspects to the final boss include that they can occupy
 * a space that is greater than the typical 1 Tile x 1 Tile, and they can engage in attacks with the character.
 * Note: As the code currently goes, there should only be one final boss that is loaded in on a scene, with all
 * boss dynamic types adjacent to one another, in a square layout.
 */
class FinalBoss {

public:

    /**
     * Default constructor of the final boss, which sets nearly all values to nullptr or 0, and assigns the default
     * boss gif to the image. It is necessary to have the default constructor for the program to run, but it is not
     * used to actually load the final boss.
     */
    FinalBoss();

    /**
     * Constructor that will create a final boss based on a list of the Tiles that it occupies, which will
     * help determine where the final boss is drawn in terms of bounds.
     * Note: If the final boss is to occupy 128 pixels x 128 pixels, gif looks good if it is 64 pixels x 64 pixels.
     * @param boss_tiles List of Tiles that the boss will occupy, loaded in from the text files that are used to
 *                       represent the scene layout.
     */
    FinalBoss(const vector<Tile>& boss_tiles);

    /**
     * Returns the description of the final boss that will be printed when the character is in front of the boss,
     * facing it. This will include the boss's current Health and total health.
     * @return Description of the final boss that the user will see.
     */
    string GetDescription();

    /**
     * Returns the interaction instructions of the final boss, which include the specific buttons that will lead
     * to a certain action with the final boss. By default, buttons to fight the boss will be Space and Q.
     * Interaction instructions will start with a new line because it is always printed after the description.
     * @return Instructions for how to interact with the final boss.
     */
    string GetInteractionInstructions();

    /**
     * Gets the reference to the current gif that will represent the final boss.
     * @return Animated gif of the final boss.
     */
    cinder::ciAnimatedGifRef& GetImage();

    /**
     * Calculates the minimum and maximum x and y tiles that the final boss will spawn on/occupy, based on
     * the container of x and y tiles that the class stored when it was created using a pre-loaded map that
     * was parsed through a text file.
     */
    void SetMinMaxTiles();

    /**
     * Get the leftmost Tile index of all the tiles that the final boss occupies.
     * @return Tile index of the leftmost tile.
     */
    size_t GetMinXTile();

    /**
     * Get the rightmost Tile index of all the tiles that the final boss occupies.
     * @return Tile index of the rightmost tile.
     */
    size_t GetMaxXTile();

    /**
     * Get the topmost Tile index of all the tiles that the final boss occupies.
     * @return Tile index of the topmost tile.
     */
    size_t GetMinYTile();

    /**
     * Get the bottommost Tile index of all the tiles that the final boss occupies.
     * @return Tile index of the bottommost tile.
     */
    size_t GetMaxYTile();

    /**
     * Decrease the final boss's current health by the damage value. If the damage value is greater than the
     * current health, the current health will be set to 0.
     * @param value Value of the damage that the final boss will be taking.
     */
    void TakeDamage(size_t value);

    /**
     * Get the damage value that the final boss is able to inflict in a round.
     * @return Damage value of the final boss's attacks.
     */
    size_t GetDamage();

    /**
     * Sets the current gif of the final boss to the final boss's attack gif.
     */
    void AttackMode();

    /**
     * Sets the current gif of the final boss to the final boss's default gif.
     */
    void DefaultMode();

    /**
     * Gets the current health of the final boss.
     * @return Current health value of the final boss.
     */
    size_t GetCurrentHealth();

    /**
     * Gets a list of all the Tiles that the final boss occupies, which is used for finding minimum and maximum
     * coordinates as well as for clearing out said Tiles after the boss is defeated, to allow for movement
     * on and past the Tiles.
     * @return
     */
    vector<Tile> GetOccupiedTiles();

private:

    /** List of the Tiles that the boss is loaded on. **/
    vector<Tile> occupied_tiles;

    /** Current image representation of the final boss. **/
    cinder::ciAnimatedGifRef image;

    /** Current health of the final boss. **/
    size_t current_health;

    /** Total health of the final boss. **/
    size_t total_health;

    /** Description of the final boss, updates every time it takes damage. **/
    string description;

    /** Instructions on how to interact with the final boss. **/
    string interaction_instructions;

    /** Leftmost tile index that the final boss is occupying. **/
    size_t min_x_tile;

    /** Rightmost tile index that the final boss is occupying. **/
    size_t max_x_tile;

    /** Topmost tile index that the final boss is occupying. **/
    size_t min_y_tile;

    /** Bottommost tile index that the final boss is occupying. **/
    size_t max_y_tile;

    /** Attack damage value of the final boss. **/
    size_t damage;

    /**
     * Updates the description to include any changes to the final boss's current health.
     */
    void UpdateDescription();
};

}  // namespace mylibrary

#endif // FINALPROJECT_MYLIBRARY_BOSS_H_
