/*!
 * @file valeris.cpp
 * @brief Main entry point for the game.
 * @details This file contains the main function, which serves as the entry point for the game.
 * It initializes the game, provides menu options, and handles user input to control the game flow.
 */

#include "../lib/combat.h"
// #include "../helper/minigames.cpp"
#include "../lib/player.h"
#include "../lib/toolkit.h"
#include "../lib/room.h"
#include "../lib/dungeon.h"
#include "../lib/menu.h"

/*!
 * @brief Main function of the game.
 * @details The main function initializes the game, sets up the console or terminal,
 * and displays the main menu. It also handles user input and navigates to different game functionalities.
 *
 * @return Returns 0 upon successful execution.
 */
int main()
{
  int j;               //!< Stores the user's menu selection.
  bool running = true; //!< Controls the main loop for the game.

  int delayTime = 0;              //!< Delay time for displaying text.
  std::string color = "\033[36m"; //!< Color code for text display.

#ifdef _WIN32
  SetConsoleSize(1200, 600);
#else
  SetTerminalSize(50, 137);
#endif

  /*!
   * @brief Main game loop.
   * @details This loop keeps the game running until the user chooses to exit.
   * Depending on the user's input, it can start a new game, load a saved game,
   * display instructions, or modify accessibility settings.
   */
  while (running)
  {
    Displayj();    //!< Display the main menu.
    j = readInt(); //!< Read user's menu selection.

    switch (j)
    {
    case 1:
      clear(10);
      displayIntro(delayTime, color); //!< Display the game introduction.
      StartGame();                    //!< Start a new game.
      break;
    case 2:
      clear(10);
      LoadSavedGame(); //!< Load a previously saved game.
      break;
    case 3:
      clear(11);
      DisplayInstructionsText(); //!< Display the instructions for the game.
      break;
    case 4:
      clear(10);
      Accessiblity(delayTime, color); //!< Access and modify accessibility options.
      break;
    case 5:
      std::cout << "Exiting Game. We hope you enjoyed the Game Play." << std::endl;
      running = false; //!< Exit the game loop.
      break;
    default:
      std::cout << "Error: An invalid choice has been entered. Please try again." << std::endl;
      delay(2000);
      clear(12);
      break;
    }

    std::cout << std::endl;
  }

  return 0;
}
