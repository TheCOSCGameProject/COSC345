/*!
 * @file menu.h
 * @brief Provides functions for managing the game menu and related actions.
 * @details This file contains declarations for functions that handle the display of the game's introductory text,
 * the main menu, game instructions, and accessibility options. It also includes functions for starting a new game
 * and loading a saved game.
 */

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

/*!
 * @brief Displays the introductory text for the game.
 * @param delayTime The time delay between each printed character in milliseconds.
 * @param color The color code for the text.
 */
void displayIntro(int delayTime, const std::string &color);

/*!
 * @brief Displays the game menu.
 * @details This function shows the main menu of the game, allowing the player to choose between starting a new game,
 * loading a saved game, viewing instructions, or accessing the accessibility options.
 */
void Displayj();

/*!
 * @brief Starts a new game.
 * @details This function initializes a new game session, setting up the necessary game state.
 */
void StartGame();

/*!
 * @brief Loads a saved game.
 * @details This function retrieves and resumes a previously saved game session.
 */
void LoadSavedGame();

/*!
 * @brief Displays the game instructions.
 * @details This function shows the instructions on how to play the game, including controls and objectives.
 */
void DisplayInstructionsText();

/*!
 * @brief Manages accessibility options.
 * @param delayTime Reference to the time delay between each printed character in milliseconds.
 * @param color Reference to the color code for the text.
 * @details This function allows the player to adjust accessibility settings, such as text color and delay time for text display.
 */
void Accessiblity(int &delayTime, std::string &color);

/*!
 * @brief Get color from user for menu.
 * @param colorChoice the color choice the user chose.
 * @param color Reference to the old color code for the text.
 * @details This function allows the player to select and change the color of the text
 */
std::string getColor(int colorChoice, const std::string& color);

void DisplayOption();

#endif // MENU_H
