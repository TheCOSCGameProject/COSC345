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
    numRooms = 20;                                 //!< Sets the number of rooms in the dungeon.
    currentRoom = dungeon.generateFloor(numRooms); //!< Generates the dungeon floor and sets the starting room.
}

/*!
 * @brief Starts the game and manages the main exploration loop.
 * @details The start method enters a loop where the player explores the dungeon, moves between rooms, and interacts with the game world. The player can move in cardinal directions, engage in combat, play games, or view help information.
 */
// LCOV_EXCL_START
void ValerisGame::start(const std::string &color)
{
    bool exploring = true; //!< Flag to control the exploration loop.
    bool codeGuessed = false;
    while (exploring)
    {
        // dungeon.traverseAndPrint(currentRoom);
        std::cout << dungeon.getMap(currentRoom) << std::endl;
        std::cout << color + currentRoom->roomContent.getRoomDesc() << ".\n\n";
        currentRoom->displayAvailableDirections();

        std::string fightString = "";
        std::string playString = "";
        std::string searchString = "";
        std::string bidString = "";

        if (currentRoom->roomContent.getRoomType() == 0)
        {
            fightString = ", /fight";
        }
        if (currentRoom->roomContent.getRoomType() == 1)
        {
            playString = ", /play";
        }
        if (currentRoom->roomContent.getRoomType() == 2 && !codeGuessed)
        {
            playString = ", /play";
        }
        else if (currentRoom->roomContent.getRoomType() == 2 && codeGuessed)
        {
            searchString = ", /search";
        }
        if (currentRoom->roomContent.getRoomType() == 1 && player.getCoins() >= 10)
        {
            bidString = ", /gamble";
        }

        std::cout << "Other Avalible Actions: Q, /help, /heal, /stats, /inventory" + fightString + playString + searchString + bidString + "\nEnter Action : ";
        std::string direction = getUserInputToken(); //!< Gets the player's input for movement or action.
        std::cout << "\n";

        // Convert direction to uppercase for consistent comparisons
        std::string upperDirection = toUpperCase(direction);

        if (upperDirection == "N")
        {
            bool empty = true;
            if (currentRoom->roomContent.getRoomType() == 0)
            {
                std::vector<EnemyStruct> enemies = currentRoom->roomContent.getEnemies();
                if (!enemies.empty())
                {
                    std::cout << "There are enemies in the room!" << std::endl;
                    delay(2000);
                    clear(1);
                    empty = false;
                }
            }
            if (empty)
            {
                if (currentRoom->north)
                {
                    currentRoom = currentRoom->north; //!< Move the player to the room to the north.
                    codeGuessed = false;
                }
                else
                {
                    std::cout << "You can't move North." << std::endl;
                    delay(3000);
                    clear(1);
                }
                clear(14);
            }
        }
        else if (upperDirection == "S")
        {
            bool empty = true;
            if (currentRoom->roomContent.getRoomType() == 0)
            {
                std::vector<EnemyStruct> enemies = currentRoom->roomContent.getEnemies();
                if (!enemies.empty())
                {
                    std::cout << "There are enemies in the room!" << std::endl;
                    delay(2000);
                    clear(1);
                    empty = false;
                }
            }
            if (empty)
            {
                if (currentRoom->south)
                {
                    currentRoom = currentRoom->south; //!< Move the player to the room to the south.
                    codeGuessed = false;
                }
                else
                {
                    std::cout << "You can't move South." << std::endl;
                    delay(3000);
                    clear(1);
                }
                clear(14);
            }
        }
        else if (upperDirection == "E")
        {
            bool empty = true;
            if (currentRoom->roomContent.getRoomType() == 0)
            {
                std::vector<EnemyStruct> enemies = currentRoom->roomContent.getEnemies();
                if (!enemies.empty())
                {
                    std::cout << "There are enemies in the room!" << std::endl;
                    delay(2000);
                    clear(1);
                    empty = false;
                }
            }
            if (empty)
            {
                if (currentRoom->east)
                {
                    currentRoom = currentRoom->east; //!< Move the player to the room to the east.
                    codeGuessed = false;
                }
                else
                {
                    std::cout << "You can't move East." << std::endl;
                    delay(3000);
                    clear(1);
                }
            }

            clear(14);
        }
        else if (upperDirection == "W")
        {
            bool empty = true;
            if (currentRoom->roomContent.getRoomType() == 0)
            {
                std::vector<EnemyStruct> enemies = currentRoom->roomContent.getEnemies();
                if (!enemies.empty())
                {
                    std::cout << "There are enemies in the room!" << std::endl;
                    delay(2000);
                    clear(1);
                    empty = false;
                }
            }
            if (empty)
            {
                if (currentRoom->west)
                {
                    currentRoom = currentRoom->west; //!< Move the player to the room to the west.
                    codeGuessed = false;
                }
                else
                {
                    std::cout << "You can't move West." << std::endl;
                    delay(3000);
                    clear(1);
                }
                clear(14);
            }
        }
        else if (upperDirection == "/PLAY" && currentRoom->roomContent.getRoomType() == 1)
        {
            std::cout << "\033[37m";
            while (!currentRoom->roomContent.getNPC().gamblingGame.get()->start())
            {
                //!< Starts the NPC's gambling game if the current room is a gambling room.
            }
            clear(14);
            std::cout << color;
        }
        else if (upperDirection == "/PLAY" && currentRoom->roomContent.getRoomType() == 2)
        {
            std::cout << "\033[37m";
            if (!codeGuessed)
            {
                codeGuessed = currentRoom->roomContent.getNonGamblingGame()->start();
            }
            std::cout << color;
            clear(14);
        }
        else if (upperDirection == "/GAMBLE" && currentRoom->roomContent.getRoomType() == 1 && player.getCoins() >= 10)
        {
            std::cout << "\033[37m";
            bool result = currentRoom->roomContent.getNPC().gamblingGame.get()->start();

            if (result)
            {
                player.setCoinsPlus(10);
            }
            else
            {
                player.setCoinsMinus(10);
            }
            clear(14);
            std::cout << color;
        }
        else if (upperDirection == "/SEARCH")
        {
            currentRoom->roomContent.displayRoomItems();
            std::vector<std::string> itemsToAdd = currentRoom->roomContent.getItems();
            for (size_t i = 0; i < itemsToAdd.size(); i++)
            {
                player.addToInventory(itemsToAdd[i]);
            }
            currentRoom->roomContent.emptyItems();
            player.setCoinsPlus(currentRoom->roomContent.getCoins());
        }
        else if (upperDirection == "/HEAL")
        {
            player.heal();
            clear(14);
        }
        else if (upperDirection == "/FIGHT" && currentRoom->roomContent.getRoomType() == 0)
        {
            std::cout << "\033[37m";
            std::vector<EnemyStruct> enemies = currentRoom->roomContent.getEnemies();
            while (!enemies.empty())
            {
                EnemyStruct enemy = enemies.front();
                int enemyHealth = enemy.health;
                int difficulty = 2000;
                bool state = combatV1(player.getCurrHealth(), enemyHealth, 3000, enemy.name, player.getDamage(), enemy.attack, player.getResistance()); //!< Initiates combat with the enemy.
                if (!state)
                {
                    exploring = false;
                    break;
                }
                else
                {
                    enemies.erase(enemies.begin());
                }
                std::cout << "Healing..." << std::endl;
                player.heal();
                delay(500);
                clear(6);
                difficulty -= 100;
            }
            currentRoom->roomContent.clearEnemies();
            currentRoom->roomContent.clearText();
            clear(14);
            std::cout << color;
        }
        else if (upperDirection == "/STATS")
        {
            player.displayStats();
        }
        else if (upperDirection == "Q")
        {
            exploring = false; //!< Exits the exploration loop and ends the game.
            std::cout << "Exiting dungeon exploration." << std::endl;
        }
        else if (upperDirection == "/HELP")
        {
            std::cout << getFileContent("../reasources/help.txt") << std::endl; //!< Displays help information from a file.
        }
        else if (upperDirection == "/INVENTORY")
        {
            player.printInventory();
        }
        else
        {
            std::cout << "Invalid direction. Please enter N, S, E, W, or Q." << std::endl;
        }
    }
    // LCOV_EXCL_STOP
}