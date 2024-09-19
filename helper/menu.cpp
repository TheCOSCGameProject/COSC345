/*!
@file menu.cpp
@brief Implementation of the Valeris game menu system.
@details This file contains functions for displaying the game menu, handling user input, and configuring accessibility options.
*/

#include "../lib/toolkit.h"
#include "../lib/dependencies.h"
#include "../lib/dungeon.h"
#include "../lib/menu.h"
#include "../lib/valerisgame.h"
#include <iomanip>

/*!
@brief Display the game introduction.
@param delayTime The delay time between printing each character.
@param color The color code for the text.
@details The introduction is read from a file and printed with a delay and color for dramatic effect.
*/
void displayIntro(int delayTime, const std::string &color)
{
    std::vector<std::string> intro = split(getFileContent("../reasources/intro.txt"), '@');

    for (int i = 0; i < 3; i++)
    {
        typePrint(intro[i], delayTime, color);
        std::cout << std::endl;
    }
    typePrint(intro[intro.size() - 1], 0, color);
    std::cout << std::endl;
}

/*!
@brief Display the Valeris game main menu.
@details This function displays the main menu with options for starting a new game, loading a saved game, viewing instructions, adjusting accessibility settings, or exiting the game.
*/
void Displayj()
{
    std::cout << "\033[37m" << "==========================================================" << std::endl;
    std::cout << std::setw(15) << " " << "VALERIS GAME MENU" << std::endl;
    std::cout << "==========================================================" << std::endl;
    std::cout << "1. Start New Game" << std::endl;
    std::cout << "2. Load Saved Game" << std::endl;
    std::cout << "3. Instructions" << std::endl;
    std::cout << "4. Accessibility" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "==========================================================" << std::endl;
}

// LCOV_EXCL_START
/*!
@brief Start a new game of Valeris.
@details This function creates an instance of the ValerisGame class and begins the game.
*/
void StartGame()
{
    ValerisGame valerisGame;
    valerisGame.start();
}

/*!
 * @brief Load a saved game.
 * @details This function simulates loading a saved game. The actual loading functionality is not implemented.
 */
void LoadSavedGame()
{
    std::cout << "\033[37m" << "Loading game..." << std::endl;
}
// LCOV_EXCL_STOP

/*!
 * @brief Display the game instructions.
 * @details This function prints the instructions for playing the Valeris game and waits for the user to press Enter before clearing the screen.
 */
void DisplayInstructionsText()
{
    std::string instructions = R"(
Instructions:
1. Use the N, S, W, E keys to move your character.
2. Fight enemies with ___
3. Collect items to improve your chances of survival.
4. Play minigames with ___
5. Defeat bosses to progress to the next level.
)";
    std::cout << "\033[37m" << instructions << std::endl;

    waitForEnter();
    clear(8);
}

/*!
 * @brief Get color from user for menu.
 * @param colorChoice the color choice the user chose.
 * @param color Reference to the old color code for the text.
 * @details This function allows the player to select and change the color of the text
 */
std::string getColor(int colorChoice, const std::string& color)
{
    std::string newColor = color;
    switch (colorChoice)
    {
    case 1:
        newColor = "\033[32m";
        break;
    case 2:
        newColor = "\033[34m";
        break;
    case 3:
        newColor = "\033[31m";
        break;
    case 4:
        newColor = "\033[33m";
        break;
    case 5:
        newColor = "\033[36m";
        break;
    default:
        std::cout << "\033[91m" << "Invalid choice. Keeping current color." << "\033[37m" << std::endl;
        delay(2000);
        clear(1);
        break;
    }
    return newColor;
}

/*!
 * @brief Configure accessibility options.
 * @param delayTime Reference to the delay time between printing each character.
 * @param color Reference to the color code for the text.
 * @details This function allows the player to adjust text speed and color for better accessibility. Changes are applied immediately, and the player can return to the main menu at any time.
 */
void Accessiblity(int &delayTime, std::string &color)
{
    std::cout << "\033[37m" << "Accessibility Options:" << std::endl;
    std::cout << "1. Text Speed (current: " << delayTime << " ms)" << std::endl;
    std::cout << "2. Text Color (current: " << color << "color" << "\033[37m" << ")" << std::endl;
    std::cout << "3. Return to Main Menu" << std::endl;

    int j = readInt();
    int colorChoice;

    switch (j)
    {
    case 1:
        std::cout << "Enter new text speed in milliseconds: ";
        delayTime = readInt();
        clear(6);
        Accessiblity(delayTime, color); // Recursive call
        break;

    case 2:
        std::cout << "Select text color:" << std::endl;
        std::cout << "1. Green" << std::endl;
        std::cout << "2. Blue" << std::endl;
        std::cout << "3. Red" << std::endl;
        std::cout << "4. Yellow" << std::endl;
        std::cout << "5. Default Cyan" << std::endl;
        colorChoice = readInt();
        color = getColor(colorChoice, color);
        clear(12);
        Accessiblity(delayTime, color); // Recursive call
        break;

    case 3:
        clear(6);
        return;

    default:
        std::cout << "\033[91m" << "Invalid choice. Returning to Accessibility Options." << "\033[37m" << std::endl;
        delay(2000);
        clear(6);
        Accessiblity(delayTime, color); // Recursive call
        break;
    }
}
