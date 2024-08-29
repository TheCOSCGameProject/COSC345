/*!
 * @file valerisgame.h
 * @brief This file contains the declaration of the ValerisGame class.
 * @details The ValerisGame class manages the main game loop, player state, and dungeon exploration.
 */

#include "toolkit.h"
#include "player.h"
#include "dungeon.h"
#include "dependencies.h"

/*!
 * @class ValerisGame
 * @brief Manages the core gameplay of Valeris.
 * @details The ValerisGame class is responsible for initializing the game, managing the player and dungeon,
 * and handling the game's main loop.
 */
class ValerisGame
{
private:
    Player player; //!< The player object representing the player in the game.
    Dungeon dungeon; //!< The dungeon object representing the dungeon environment.
    Room *currentRoom; //!< Pointer to the current room in the dungeon.
    int numRooms; //!< The number of rooms in the dungeon.

public:
    /*!
     * @brief Constructor for the ValerisGame class.
     * @details Initializes the player, dungeon, and other game-related entities.
     */
    ValerisGame();

    /*!
     * @brief Starts the game.
     * @details This method begins the game loop, allowing the player to explore the dungeon and interact with the environment.
     */
    void start();
};
