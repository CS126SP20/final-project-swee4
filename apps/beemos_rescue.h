// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include "cinder/app/RendererGl.h"
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <mylibrary/character.h>
#include <mylibrary/playing_field.h>
#include <string>
#include <cinder/Color.h>

namespace myapp {

using std::string;

/**
 * Creates enums to keep track of the state of the game as it progresses, limiting certain controls at designated times.
 */
enum class GameState {
    kTitle,
    kInstructions,
    kPlaying,
    kDealDamage,
    kTakeDamage,
    kOutOfAmmo,
    kOutOfHealth,
    kGameWon
};

/**
 * Creates a class that will handle the overall game logic of the application, as well as setting up the introduction
 * screens and the ending screens.
 */
class GameEngine : public cinder::app::App {

public:

    /**
     * Default constructor to create a GameEngine.
     */
    GameEngine();

    /**
     * Sets up all necessary components to the Game Engine, including loading in the Playing Field and initializing
     * each aspect of the game.
     */
    void setup() override;

    /**
     * Will deal damage to the boss or receive damage from the boss in the corresponding game states, but otherwise
     * will check for game loss states.
     */
    void update() override;

    /**
     * Draws the current state of the game.
     */
    void draw() override;

    /**
     * Listens for keypress and will execute corresponding actions if certain conditions are met.
     */
    void keyDown(cinder::app::KeyEvent) override;

private:

    /** Stores the current state of the scene that the player is on. **/
    mylibrary::PlayingField current_scene;

    /** Stores the state of the first scene. **/
    mylibrary::PlayingField scene_one;

    /** Stores the state of the second scene. **/
    mylibrary::PlayingField scene_two;

    /** Stores the state of character. **/
    mylibrary::Character beemo;

    /**
     * Checks if the character can move in a certain direction, based on whether it is within bounds of the window and
     * if the tile in that direction is solid or not.
     * @param direction Direction that the character is attempting to move in.
     * @return True if the character can move to that Tile.
     */
    bool CanMove(const std::string& direction);

    /**
     * Checks if the the tile that is one towards the designated direction is still within frame of the playing field.
     * @param direction Direction that the character is attempting to move in.
     * @return True if there is a Tile between the character and the bounds of the window.
     */
    bool IsWithinSceneBounds(const std::string& direction);

    /**
     * Gets the Tile that is in front of the character, based on its current orientation. If it is facing the bound
     * of a window, the front tile will be set to a blank Tile.
     * @return Tile in front of the character, or a blank Tile if it is facing the window bounds.
     */
    mylibrary::Tile GetFrontTile();

    /** The X-Coordinate of the Tile in front of the character. **/
    size_t GetFrontTileX();

    /** The Y-Coordinate of the Tile in front of the character. **/
    size_t GetFrontTileY();

    /**
     * Draws the description of the item in front of the character, within the allotted Description area on the bottom
     * left of the screen.
     */
    void DrawDescription();

    /**
     * Draws the Inventory of the character, based on Items (aside from Bees) that it picks up.
     */
    void DrawInventory();

    /**
     * Displays the character stats on the bottom right of the screen.
     */
    void DrawStats();

    /** Current state of the game, based on predetermined enums. **/
    GameState game_state;

    /**
     * Draws the Introduction screen of the game, which will state the objective and game controls.
     */
    void DrawIntroduction();

    /**
     * Draws the appropriate end screen of the game based on the game state, which will have text on the top
     * half and an image on the bottom half.
     */
    void DrawEndScreen();

    /**
     * Draws the appropriate end image on the bottom half of the screen when the end screen is drawn. Image
     * will be scaled based on the amount that the height of the image is being scaled.
     */
    void DrawEndImage();

    /**
     * Checks whether the Tile in front of the character is an Item that contains a buff.
     * @return True if the Tile in front of the character contains a buff.
     */
    bool IsFrontTileBuff();

    /**
     * Checks whether the Tile in front of the character is occupied by the final boss.
     * @return True if the final boss is in front of the character.
     */
    bool IsFrontTileBoss();

    /**
     * Gets the appropriate text to print based on the game state and what tile is in front of the character.
     * @return Text to print in the description box.
     */
    string GetDescriptionText();

    /**
     * Highly versatile method that allows for Text boxes to be drawn with the input of certain parameters.
     * @param font_height Size of the font.
     * @param size Size of the box in terms of both x and y.
     * @param color Color of the text to print.
     * @param text_to_print Designated text to be printed.
     * @param top_left_point The coordinate, in pixels, of where the top left of the text box should be printed.
     */
    void DrawTextBox(size_t font_height, const cinder::ivec2& size, const cinder::Color& color,
                     const string& text_to_print, const cinder::vec2& top_left_point);

    /**
     * Draws the visual representation of the character's current Inventory on the bottom of the screen, between
     * descriptions and stats.
     * Note: The product of the column_count and row_count should be equal to the character's maximum inventory
     * storage space.
     * @param column_count Number of columns of Inventory display.
     * @param row_count Number of rows of Inventory display.
     * @param x_start_pixel Leftmost pixel of the display.
     * @param y_start_pixel Topmost pixel of the display.
     */
    void DrawInventoryItems(size_t column_count, size_t row_count, size_t x_start_pixel, size_t y_start_pixel);

    /**
     * Get the appropriate attack response of the game engine, depending on game state, whether the character has
     * the ammunition to attack, and more. By default, the [Q] key will check for Attack Responses while the engine
     * is in its default playing state.
     */
    void GetAttackResponse();

    /**
     * Gets the appropriate interaction response from the game engine, depending on the game state, what the Tile
     * in front of the character is, whether the character has the inventory space to interact with it, and more.
     * By default, the [E] key will check for Interaction Responses while the engine is in its default playing state.
     */
    void GetInteractResponse();

    /**
     * Gets the appropriate response to when a directional key is pressed to indicate the attempt to move in a
     * designated direction.
     * @param direction Direction that the character is attempting to move in.
     */
    void GetDirectionResponse(const string& direction);

    /**
     * While the Game is in its Playing Game State, this method will be called to check for whether actions need
     * to be executed upon certain key presses.
     * @param event KeyEvent that will be used to check if there is an appropriate action to be executed in response
     *              to it.
     */
    void GetPlayingStateResponse(const cinder::app::KeyEvent& event);

    /**
     * Draws the current scene, which includes the playing field, the description, inventory, and the stats on the
     * bottom of the screen, as well as the character itself.
     */
    void DrawCurrentScene();

    /**
     * Draws the Title screen that welcomes the player to the game.
     */
    void DrawTitleScreen();
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
