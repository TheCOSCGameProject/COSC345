/*!
 * @file room.h
 * @brief Defines the Room and RoomContent classes for the Valeris game.
 * @details This file contains the definitions of the Room and RoomContent classes,
 * which represent the various rooms in the game's dungeon and their contents, such as items, enemies, and NPCs.
 */

#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>
#include <iostream>
#include "../lib/minigames.h"

// Assuming these functions are declared in the toolkit.h
// std::vector<std::string> split(const std::string &str, char delimiter);
// int generateRandomNumber(int low, int high);
// int stringToInt(const std::string &str);
// std::string getFileContent(const std::string &filePath);

/*!
 * @struct EnemyStruct
 * @brief Represents an enemy in a room.
 * @details Contains the name, health, and attack attributes of an enemy.
 */
struct EnemyStruct
{
    std::string name; //!< Name of the enemy.
    int health;       //!< Health points of the enemy.
    int attack;       //!< Attack power of the enemy.
};

/*!
 * @struct NPC
 * @brief Represents a non-player character (NPC) in a room.
 * @details Contains the name, skill level, and an optional gambling game associated with the NPC.
 */
struct NPC
{
    std::string name;                   //!< Name of the NPC.
    std::unique_ptr<Game> gamblingGame; //!< Pointer to a gambling game associated with the NPC.
    int skillLevel;                     //!< Skill level of the NPC in the gambling game.
};

/*!
 * @class RoomContent
 * @brief Manages the content within a room, including items, enemies, and NPCs.
 * @details The RoomContent class is responsible for handling the contents of a room,
 * such as items that can be collected, enemies that can be fought, and NPCs that can be interacted with.
 */
class RoomContent
{
public:
    /*!
     * @brief Constructor for RoomContent.
     * @details Initializes an empty room content.
     */
    RoomContent();

    /*!
     * @brief Clears the room content, making it empty.
     */
    void emptyRoom();

    /*!
     * @brief Sets up a gambling room with an NPC.
     */
    void gamblingRoom();

    /*!
     * @brief Adds an item to the room.
     * @param item The name of the item to add.
     */
    void addItem(const std::string &item);

    /*!
     * @brief Adds an enemy to the room.
     * @param enemy The enemy to add.
     */
    void addEnemy(const EnemyStruct &enemy);

    /*!
     * @brief Displays the contents of the room.
     */
    void displayContent() const;

    /*!
     * @brief Gets the type of the room.
     * @return An integer representing the room type.
     */
    int getRoomType();

    /*!
     * @brief Gets the description of the room.
     * @return A string containing the room description.
     */
    std::string getRoomDesc();

    /*!
     * @brief Gets the NPC in the room.
     * @return A reference to the NPC in the room.
     */
    NPC &getNPC();

    /*!
     * @brief Gets the enemies in the room.
     * @return A vector of enemies present in the room.
     */
    std::vector<EnemyStruct> getEnemies();

    /*!
     * @brief Sets the coordinates for this room.
     * @param x The x coordinate.
     * @param y The y coordinate.
     */
    void addCoordinates(int x, int y);

    /*!
     * @brief Gets the coordinates for this room.
     * @return The coordinates for this room
     */
    std::pair<int, int> getCoordinates();

    /*!
     * @brief Gets whether or not the room has been visited
     * @return Whether or not the room has been visited
     */
    bool getVisited();

    /*!
     * @brief Sets whether or not the room has been visited
     * @param hasVisited Whether or not the room has been visited
     */
    void setVisited(bool hasVisited);

private:
    std::vector<std::string> items;   //!< Items available in the room.
    std::vector<EnemyStruct> enemies; //!< Enemies present in the room.
    NPC npc;                          //!< NPC present in the room.
    bool passcode;                    //!< Indicates if the room has a passcode.
    int roomType;                     //!< The type of the room.
    std::string roomDesc;             //!< Description of the room.
    std::pair<int, int> cords;        //!< (x,y) Coordinates of room
    bool visited;                     //!< Whether or not the room has been visited
};

/*!
 * @class Room
 * @brief Represents a room in the dungeon.
 * @details The Room class links rooms together and manages their contents, allowing the player to navigate between them.
 */
class Room
{
public:
    /*!
     * @brief Constructor for the Room class.
     * @details Initializes the room with default values and no connections to other rooms.
     */
    Room();

    Room *north;             //!< Pointer to the room to the north.
    Room *south;             //!< Pointer to the room to the south.
    Room *west;              //!< Pointer to the room to the west.
    Room *east;              //!< Pointer to the room to the east.
    RoomContent roomContent; //!< The content of the room.

    /*!
     * @brief Displays the available directions the player can move in.
     */
    void displayAvailableDirections();
};

#endif // ROOM_H