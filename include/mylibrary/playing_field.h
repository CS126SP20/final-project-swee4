// Copyright (c) 2020 [Sue Wee]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_SCENE_H_
#define FINALPROJECT_MYLIBRARY_SCENE_H_

#include <mylibrary/final_boss.h>
#include <mylibrary/tile.h>
#include <string>
#include <vector>

namespace mylibrary {

using std::string;

using std::vector;

/**
 * Class to manage all that is related to creating the playable scenes on the app window, which includes loading in
 * the map and all dynamic types on top of the map Tiles that can be interacted with. Everything except the character
 * is handled in this class.
 */
class PlayingField {

public:

    /**
     * Default constructor for the class will create an empty map of 64 pixel x 64 pixel Tiles that shows only white.
     */
    PlayingField();

    /**
     * Constructor for the class that takes in a file and parses through it to load in pre-determined conditions and
     * locations of certain objects and map types. Playing fields consist of two main layers: a base map layer that
     * is a static image, which every tile must contain, and a dynamic layer which will contain an animated gif
     * image and sometimes an associated Item, if the tile is a minion or a sparkle. Tiles do not always display a
     * dynamic type. Then there is a final boss that is also created and managed within the class.
     * @param file_name File name of the scene that the map and dynamic types will be loaded from. The first block of
     *                  text represents the map types, and the second represents the dynamic types.
     * @param tile_pixels Length of each tile in pixels.
     * @param tiles_row Number of tiles in a row.
     * @param tiles_col Number of tiles in a column.
     */
    explicit PlayingField(const string& file_name, size_t tile_pixels, size_t tiles_row, size_t tiles_col);

    /**
     * Get the number of Tiles in a column.
     * @return Number of Tiles in a column.
     */
    size_t GetMaxXTiles();

    /**
     * Get the number of Tiles in a row.
     * @return Number of Tiles in a row.
     */
    size_t GetMaxYTiles();

    /**
     * Get the X-Coordinate of the leftmost pixel, given the coordinates of a Tile.
     * @param current_x_tile X-Coordinate of a Tile.
     * @return Leftmost X-Coordinate of the Tile, in pixels.
     */
    size_t GetXStartPixel(size_t current_x_tile);

    /**
     * Get the Y-Coordinate of the topmost pixel, given the coordinates of a Tile.
     * @param current_y_tile Y-Coordinate of a Tile.
     * @return Topmost Y-Coordinate of the Tile, in pixels.
     */
    size_t GetYStartPixel(size_t current_y_tile);

    /**
     * Get the X-Coordinate of the bottommost pixel, given the coordinates of a Tile.
     * @param current_x_tile Y-Coordinate of a Tile.
     * @return Bottommost X-Coordinate of the Tile, in pixels.
     */
    size_t GetXEndPixel(size_t current_x_tile);

    /**
     * Get the Y-Coordinate of the bottommost pixel, given the coordinates of a Tile.
     * @param current_y_tile Y-Coordinate of a Tile.
     * @return Bottommost Y-Coordinate of the Tile, in pixels.
     */
    size_t GetYEndPixel(size_t current_y_tile);

    /**
     * Gets the 2D representation of all the Tiles in the scene.
     * @return 2D representation of all Tiles in the scene.
     */
    vector<vector<Tile>> GetTileMap();

    /**
     * Gets a reference to a Tile based on its XY coordinates.
     * @param x_index X-Coordinate of the Tile.
     * @param y_index Y-Coordinate of the Tile.
     * @return Reference to the Tile at the XY coordinate.
     */
    Tile& GetTile(size_t x_index, size_t y_index);

    /**
     * Equality operator to check if the current scene is the same as another scene, based on the map types of
     * the scene, not on dynamic types.
     * @param rhs Reference to the other scene that this current scene is being compared to.
     * @return True if the map types of each corresponding tile is the same.
     */
    bool operator==(const PlayingField& rhs);

    /**
     * Draws the playing field with the Tiles loaded in and the final boss, if the scene has one.
     */
    void draw();

    /**
     * For the dynamic types that have "hidden states" such as minions and sparkles, which must be interacted with
     * before they can be picked up, this method will uncover the "hidden states".
     * @param x_index X-Coordinate of the Tile to be revealed.
     * @param y_index Y-Coordinate of the Tile to be revealed.
     */
    void Reveal(size_t x_index, size_t y_index);

    /**
     * For the dynamic types that can be picked up and removed from the map, this method will remove them and allow
     * the character to pass above the Tiles where it used to be occupied by the item.
     * @param x_index X-Coordinate of the Tile to be removed.
     * @param y_index Y-Coordinate of the Tile to be removed.
     */
    void Remove(size_t x_index, size_t y_index);

    /**
     * Returns the final boss object that is loaded in on the map.
     * @return Final boss of the scene.
     */
    FinalBoss& GetFinalBoss();

    /**
     * Deals a certain amount of damage to the final boss.
     * @param damage_value Damage that is inflicted upon the final boss.
     */
    void DealBossDamage(size_t damage_value);

    /**
     * Sets the boss to Attack Mode, which means that its graphic will now display an attack animation.
     */
    void SetBossAttackMode();

    /**
     * Sets the boss to Default Mode, which means that its graphic will now display its default animation.
     */
    void SetBossDefaultMode();

    /**
     * Gets the total count of all Tiles that store the dynamic type of the ammunition used in the game, which is used
     * later to calculate when the character has ran out of all available ammunition.
     * @return
     */
    size_t GetAmmoCount();

private:

    /** 2D representation of the Tiles in the scene. **/
    vector<vector<Tile>> tiles;

    /** Length of the Tiles in pixels. **/
    size_t tile_size;

    /** Number of Tiles in a column. **/
    size_t max_x_tiles;

    /** Number of Tiles in a row. **/
    size_t max_y_tiles;

    /** Container for the Tiles that the final boss is occupying.
     * Note: They should all be adjacent, ideally as a square.
     */
    vector<Tile> boss_tiles;

    /** Final boss of the scene. **/
    FinalBoss final_boss;

    /** True if there is a final boss that is meant to be loaded onto the scene, based on whether there are final boss
     * dynamic types stored in the text file where the scenes are loaded in.
     */
    bool is_final_boss_present;

    /** The total number of ammunition available on the scene in its initial state before any interactions. **/
    size_t ammo_count;

    /**
     * Sets up an empty 2D representation of the Tiles based on the designated size of the scene. All Tiles will only
     * show a white image.
     */
    void SetupBlankTiles();

    /**
     * Assigns the correct map and dynamic type to the initial 2D representation of the Tiles, which starts out only
     * as a white image. This also initializes all corresponding items and images associated with the map and/or
     * dynamic type.
     * @param file_name File name that the scene will be based on.
     * @param map_types Assigns the map types to this reference, row by row, excluding the last character each time
     *                  (due to CLion's automatic text formatting, the last character is there to maintain the
     *                  trailing space.)
     * @param dynamic_types Assigns the dynamic types to this reference, row by row, excluding the last character
     *                      each time (due to CLion's automatic text formatting, the last character is there to
     *                      maintain the trailing space.)
     */
    void StoreMapAndDynamicTypes(const string& file_name, vector<string>& map_types, vector<string>& dynamic_types);

    /**
     * Assigns the Tiles qualities based on the corresponding map and dynamic types that were loaded in.
     * @param map_types Container of the map types by row, read in from the file.
     * @param dynamic_types Container of the dynamic types by row, read in from the file.
     */
    void AssignTileTypes(const vector<string>& map_types, const vector<string>& dynamic_types);

    /**
     * Draws the scene of the playing field, but only the map and dynamic states.
     */
    void DrawScene();

    /**
     * Draws the final boss in its corresponding location, if there is a designated spot on the map for the final boss.
     */
    void DrawFinalBossIfApplicable();

};

}  // namespace mylibrary

#endif // FINALPROJECT_MYLIBRARY_SCENE_H_
