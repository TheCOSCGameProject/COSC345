/*!
 * @file valerisgame.cpp
 * @brief Implements the ValerisGame class for the Valeris game.
 * @details This file defines the methods of the ValerisGame class, which manages the game's main loop, dungeon exploration, and player interactions.
 */

#include "../lib/valerisgame.h"
#include "../lib/combat.h"

/*!
 * @brief Constructor for the ValerisGame class.
 * @details Initializes the game by generating a dungeon floor with a specified number of rooms and setting the current room to the starting point.
 */
ValerisGame::ValerisGame()
{
    numRooms = 10;                                 //!< Sets the number of rooms in the dungeon.
    currentRoom = dungeon.generateFloor(numRooms); //!< Generates the dungeon floor and sets the starting room.
}

/*!
 * @brief Starts the game and manages the main exploration loop.
 * @details The start method enters a loop where the player explores the dungeon, moves between rooms, and interacts with the game world. The player can move in cardinal directions, engage in combat, play games, or view help information.
 */
// LCOV_EXCL_START
void ValerisGame::start()
{
    bool exploring = true; //!< Flag to control the exploration loop.
    while (exploring)
    {
        // dungeon.traverseAndPrint(currentRoom);
        std::cout << dungeon.getMap(currentRoom) << std::endl;
        std::cout << "You have entered a " << currentRoom->roomContent.getRoomDesc() << ".\n\n";
        currentRoom->displayAvailableDirections();

        std::cout << "Enter Action: ";
        std::string direction = getUserInputToken(); //!< Gets the player's input for movement or action.
        std::cout << "\n";

        // Convert direction to uppercase for consistent comparisons
        std::string upperDirection = toUpperCase(direction);

        if (upperDirection == "N")
        {
            if (currentRoom->north)
            {
                currentRoom = currentRoom->north; //!< Move the player to the room to the north.
            }
            else
            {
                std::cout << "You can't move North." << std::endl;
                delay(3000);
                clear(1);
            }
            clear(13);
        }
        else if (upperDirection == "S")
        {
            if (currentRoom->south)
            {
                currentRoom = currentRoom->south; //!< Move the player to the room to the south.
            }
            else
            {
                std::cout << "You can't move South." << std::endl;
                delay(3000);
                clear(1);
            }
            clear(13);
        }
        else if (upperDirection == "E")
        {
            if (currentRoom->east)
            {
                currentRoom = currentRoom->east; //!< Move the player to the room to the east.
            }
            else
            {
                std::cout << "You can't move East." << std::endl;
                delay(3000);
                clear(1);
            }
            clear(13);
        }
        else if (upperDirection == "W")
        {
            if (currentRoom->west)
            {
                currentRoom = currentRoom->west; //!< Move the player to the room to the west.
            }
            else
            {
                std::cout << "You can't move West." << std::endl;
                delay(3000);
                clear(1);
            }
            clear(13);
        }
        else if (upperDirection == "/PLAY" && currentRoom->roomContent.getRoomType() == 1)
        {
            while (!currentRoom->roomContent.getNPC().gamblingGame.get()->start())
            {
                //!< Starts the NPC's gambling game if the current room is a gambling room.
            }
            clear(13);
        }
        else if (upperDirection == "/SCAN")
        {
            std::cout << dungeon.getMap(currentRoom) << std::endl;
        }
        else if (upperDirection == "/FIGHT" && currentRoom->roomContent.getRoomType() == 0)
        {
            std::vector<EnemyStruct> enemies = currentRoom->roomContent.getEnemies();
            for (int i = 0; i < (int)enemies.size(); i++)
            {
                EnemyStruct enemy = enemies[i];
                int enemyHealth = enemy.health;
                combatV1(player.getCurrHealth(), enemyHealth, 3000, enemy.name); //!< Initiates combat with the enemy.
                delay(5000);
                clear(5);
            }
            clear(13);
        }
        else if (upperDirection == "Q")
        {
            exploring = false; //!< Exits the exploration loop and ends the game.
            std::cout << "Exiting dungeon exploration." << std::endl;
        }
        else if (upperDirection == "/HELP")
        {
            std::cout << getFileContent("../resources/help.txt") << std::endl; //!< Displays help information from a file.
        }
        else
        {
            std::cout << "Invalid direction. Please enter N, S, E, W, or Q." << std::endl;
        }
    }
    // LCOV_EXCL_STOP
}