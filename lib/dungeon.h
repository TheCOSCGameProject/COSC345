/*!
 * @file dungeon.h
 * @brief Defines the Dungeon class for the Valeris game.
 * @details This file contains the declaration of the Dungeon class, which is responsible for generating and managing
 * the dungeon floors in the game. It includes methods for generating rooms, linking them, and traversing the dungeon.
 */

#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <random>
#include <map>
#include <queue>
#include "../lib/room.h"

/*!
 * @class Dungeon
 * @brief Manages the generation and traversal of dungeon floors.
 * @details The Dungeon class handles the creation of a dungeon floor with a specified number of rooms, linking rooms
 * together, and providing methods to traverse and print the contents of the dungeon.
 */
class Dungeon
{
public:
    /*!
     * @brief Constructor for the Dungeon class.
     * @details Initializes the Dungeon object, including the random number generator.
     */
    Dungeon();

    /*!
     * @brief Destructor for the Dungeon class.
     * @details Cleans up any dynamically allocated memory.
     */
    ~Dungeon();

    /*!
     * @brief Generates a dungeon floor with a specified number of rooms.
     * @param numRooms The number of rooms to generate in the floor.
     * @return A pointer to the starting room of the generated floor.
     */
    Room *generateFloor(int numRooms);

    /*!
     * @brief Counts the number of rooms in the dungeon starting from a given room.
     * @param startRoom A pointer to the room from which to start counting.
     * @return The total number of rooms in the dungeon.
     */
    int numRooms(Room *startRoom);

    /*!
     * @brief Links two rooms together in a specified direction.
     * @param room1 A pointer to the first room.
     * @param room2 A pointer to the second room.
     * @param direction The direction in which to link the rooms (0 = north, 1 = south, 2 = west, 3 = east).
     */
    void linkRooms(Room *room1, Room *room2, int direction); // Making it public for testing

    std::string getMap(Room *room);

private:
    std::vector<Room *> rooms; //!< A vector containing pointers to all the rooms in the dungeon.
    std::mt19937 rng;          //!< Random number generator for generating random dungeon elements.

    /*!
     * @brief Generates a new room.
     * @return A pointer to the newly generated room.
     */
    Room *generateRoom(int x, int y);

    /*!
     * @brief Links a new room with existing adjacent rooms.
     * @param newRoom A pointer to the new room to link.
     * @param x The x-coordinate of the new room.
     * @param y The y-coordinate of the new room.
     * @param roomMap A map of existing rooms with their coordinates.
     */
    void checkAndLink(Room *newRoom, int x, int y, std::map<std::pair<int, int>, Room *> &roomMap);
};

#endif // DUNGEON_H
