/*!
@file room.cpp
@brief Implementation of Room and RoomContent classes for dungeon system.
@details This file contains the implementation of the Room and RoomContent classes,
which manage the creation and interaction with different types of rooms in a dungeon system.
The RoomContent class handles the generation of room types, items, enemies, and NPCs,
while the Room class manages room connections and navigation.
*/

#include "../lib/room.h"
#include <iostream>
#include "../lib/toolkit.h"

/*!
@brief Constructor for RoomContent class.
@details Initializes a RoomContent object by randomly generating a room type (either empty or gambling room).
Depending on the room type, it populates the room with appropriate items, enemies, or NPCs.
*/

RoomContent::RoomContent()
    : roomType(generateRandomNumber(0, 3)),
      passcode(false),
      visited(false)
{
    switch (roomType)
    {
    case 0:
        enemyRoom();
        roomDesc = "You have entered a Room";
        if (!enemies.empty())
        {
            roomDesc.append(" containing ");
            for (size_t i = 0; i < enemies.size(); ++i)
            {
                if (i > 0)
                {
                    roomDesc.append(", ");
                }
                roomDesc.append(enemies[i].name);
            }
        }
        break;
    case 1:
        gamblingRoom();

        if (this->npc.gamblingGame)
        {
            roomDesc = "You have entered a Gambling Room containing a " + this->npc.name + " who wants to play " + npc.gamblingGame->getGameName();
        }
        else
        {
            roomDesc = "You have entered a Gambling Room containing an NPC with an unknown game";
        }
        break;
    case 2:
        lockedRoom();
        roomDesc = "You have entered a room with a locked safe type /PLAY to try crack the passcode!";
        roomType = 2;
        break;
    case 3:
        enemyRoom();
        roomDesc = "You have entered a Room";
        if (!enemies.empty())
        {
            roomDesc.append(" containing ");
            for (size_t i = 0; i < enemies.size(); ++i)
            {
                if (i > 0)
                {
                    roomDesc.append(", ");
                }
                roomDesc.append(enemies[i].name);
            }
        }
        roomType = 0;
        break;
    default:
        break;
    }
}

/*!
@brief Get the description of the room.
@return A string describing the room and its contents.
*/
std::string RoomContent::getRoomDesc()
{
    return roomDesc;
}

int selectIndex(const std::vector<int> &probabilities)
{
    // Random device to seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a discrete distribution based on the probabilities vector
    std::discrete_distribution<> dist(probabilities.begin(), probabilities.end());

    // Generate and return the index
    return dist(gen);
}

void RoomContent::lockedRoom()
{
    nonGambilingGame = std::make_unique<CodeGuesser>();
    std::vector<std::string> health_items = split(getFileContent("../reasources/health_items.txt"), '\n');
    std::vector<std::string> weapon_items = split(getFileContent("../reasources/weapon_items.txt"), '\n');
    std::vector<std::string> armour_items = split(getFileContent("../reasources/armour_items.txt"), '\n');

    // for (int i = 0; i < armour_items.size(); i++)
    // {
    //     std::cout << armour_items[i] << std::endl;
    // }
    coins = generateRandomNumber(10, 20);

    std::vector<int>
        health_items_dist = getDist(health_items);

    std::vector<int> weapon_items_dist = getDist(weapon_items);

    std::vector<int> armour_items_dist = getDist(armour_items);

    int random = generateRandomNumber(0, 4);
    for (int i = 0; i < random; i++)
    {
        addItem(health_items[selectIndex(health_items_dist)]);
    }

    for (int i = 0; i < 1; i++)
    {
        addItem(weapon_items[selectIndex(weapon_items_dist)]);
    }

    random = generateRandomNumber(0, 1);
    for (int i = 0; i < random; i++)
    {
        addItem(armour_items[selectIndex(armour_items_dist)]);
    }
}

/*!
@brief Generate a gambling room with a random NPC and game.
@details This method creates an NPC with a random gambling game (either TicTacToe or BlackJack).
It reads NPC names from a file and assigns one to the NPC.
*/
void RoomContent::gamblingRoom()
{
    int gamblingGameType = generateRandomNumber(0, 1);
    NPC newNPC;

    if (gamblingGameType == 0)
    {
        newNPC.gamblingGame = std::make_unique<TicTacToe>();
    }
    else
    {
        newNPC.gamblingGame = std::make_unique<BlackJack>();
    }

    std::vector<std::string> npcNames = split(getFileContent("../reasources/npc.txt"), '\n');
    if (npcNames.empty())
    {
        std::cerr << "Error: NPC names list is empty.\n";
        return; // Exit the function if there are no NPC names
    }

    int index = generateRandomNumber(0, (int)npcNames.size() - 1);
    newNPC.name = npcNames[index];
    newNPC.skillLevel = 0;
    this->npc = std::move(newNPC);
}

/*!
@brief Generate an empty room with random enemies and items.
@details This method reads enemy and item details from files, then randomly adds them to the room based on predefined probabilities.
*/
void RoomContent::enemyRoom()
{
    std::vector<std::string> listOfEnemies = split(getFileContent("../reasources/enemies.txt"), '\n');
    std::vector<std::string> listOfItems = split(getFileContent("../reasources/weapon_items.txt"), '\n');
    std::vector<std::string> listRoomItems;
    std::vector<EnemyStruct> listOfRoomEnemies;

    for (int i = 0; i < listOfEnemies.size(); i++)
    {
        std::vector<std::string> enemyDetails = split(listOfEnemies.at(i), ':');
        int rand = generateRandomNumber(0, 10);
        if (stringToInt(enemyDetails.at(1)) > rand)
        {
            EnemyStruct enemy;
            enemy.name = enemyDetails[0];
            enemy.health = stringToInt(enemyDetails[2]);
            enemy.attack = stringToInt(enemyDetails[3]);
            listOfRoomEnemies.push_back(enemy);
        }
    }

    for (int i = 0; i < listOfItems.size(); i++)
    {
        std::vector<std::string> itemDetails = split(listOfItems.at(i), ':');
        int rand = generateRandomNumber(0, 10);
        if (stringToInt(itemDetails[1]) > rand)
        {
            listRoomItems.push_back(itemDetails[0]);
        }
    }

    int numEnemiesToAdd = generateRandomNumber(1, 4);
    for (int i = 0; i < numEnemiesToAdd && !listOfRoomEnemies.empty(); i++)
    {
        int index = generateRandomNumber(0, (int)listOfRoomEnemies.size() - 1);
        addEnemy(listOfRoomEnemies.at(index));
    }

    int numItemsToAdd = generateRandomNumber(1, 3);
    for (int i = 0; i < numItemsToAdd && !listRoomItems.empty(); i++)
    {
        int index = generateRandomNumber(0, (int)listRoomItems.size() - 1);
        addItem(listRoomItems.at(index));
    }
}

/*!
@brief Add an item to the room.
@param item The name of the item to add.
*/
void RoomContent::addItem(const std::string &item)
{
    items.push_back(item);
}

/*!
@brief Add an enemy to the room.
@param enemy The enemy to add to the room.
*/
void RoomContent::addEnemy(const EnemyStruct &enemy)
{
    enemies.push_back(enemy);
}

/*!
@brief Get the type of the room.
@return An integer representing the room type (0 for empty room, 1 for gambling room).
*/
int RoomContent::getRoomType()
{
    return this->roomType;
}

/*!
@brief Get the NPC in the room.
@return A reference to the NPC in the room.
*/
NPC &RoomContent::getNPC()
{
    return npc;
}

/*!
@brief Get the list of enemies in the room.
@return A vector of EnemyStructs representing the enemies in the room.
*/
std::vector<EnemyStruct> RoomContent::getEnemies()
{
    return enemies;
}

void RoomContent::clearEnemies()
{
    enemies.clear();
}

std::vector<std::string> RoomContent::getItems()
{
    return items;
}

/*!
@brief Display the content of the room.
@details Prints the coordinates, visited status, items, enemies, and NPC details of the room to the console.
*/
// LCOV_EXCL_START
void RoomContent::displayContent() const
{
    std::cout << "cords: " << "(" << cords.first << ", " << cords.second << ")" << std::endl;

    std::cout << visited << std::endl;

    if (roomType == 0)
    {
        // Display items
        std::cout << "Items: ";
        for (size_t i = 0; i < items.size(); ++i)
        {
            std::cout << items[i];
            if (i < items.size() - 1) // Check if it's not the last item
            {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;

        // Display enemies
        std::cout << "Enemies: ";
        for (size_t i = 0; i < enemies.size(); ++i)
        {
            std::cout << enemies[i].name;
            if (i < enemies.size() - 1) // Check if it's not the last enemy
            {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
    else if (roomType == 1)
    {
        std::cout << "NPC Details:" << std::endl;
        std::cout << "Name: " << npc.name << std::endl;
        std::cout << "Gambling Game: " << npc.gamblingGame->getGameName() << std::endl;
        std::cout << "Skill Level: " << npc.skillLevel << std::endl;
    }
}
// LCOV_EXCL_STOP

/*!
@brief Constructor for the Room class.
@details Initializes a Room object with null pointers for all directions and an empty RoomContent.
*/
Room::Room() : north(nullptr), south(nullptr), west(nullptr), east(nullptr), roomContent() {}

/*!
@brief Display the available directions the player can move to.
@details Checks the neighboring rooms and lists the possible directions the player can move in.
*/
void Room::displayAvailableDirections()
{
    std::vector<std::string> directions;

    if (north)
        directions.push_back("North");
    if (south)
        directions.push_back("South");
    if (west)
        directions.push_back("West");
    if (east)
        directions.push_back("East");

    std::cout << "You can move: ";
    for (size_t i = 0; i < directions.size(); ++i)
    {
        std::cout << directions[i];
        if (i < directions.size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

void RoomContent::displayRoomItems()
{
    if (items.size() == 0)
    {
        std::cout << "There are currently no items available in this room" << std::endl;
        return;
    }

    std::cout << "Available Items\n"
              << std::endl;
    for (size_t i = 0; i < items.size(); i++)
    {
        std::cout << i + 1 << ". " << split(items[i], ':')[0] << std::endl;
    }
    if (coins > 0)
    {
        std::cout << "Coins" << ": " << coins << std::endl;
    }
    std::cout << std::endl;
}

int RoomContent::getCoins()
{
    int c = coins;
    coins = 0;
    return c;
}

bool RoomContent::collect(Player *player)
{
    bool done = !items.empty();

    while (!items.empty())
    {
        std::string newS = items.back();
        player->addToInventory(newS);
        items.pop_back();
    }
    return done;
}

/*!
@brief Add coordinates to the room.
@param x The x-coordinate of the room.
@param y The y-coordinate of the room.
*/
void RoomContent::addCoordinates(int x, int y)
{
    cords = std::make_pair(x, y);
}

/*!
@brief Get the coordinates of the room.
@return A pair of integers representing the x and y coordinates of the room.
*/
std::pair<int, int> RoomContent::getCoordinates()
{
    return cords;
}

/*!
@brief Check if the room has been visited.
@return True if the room has been visited, false otherwise.
*/
bool RoomContent::getVisited()
{
    return visited;
}

/*!
@brief Set the visited status of the room.
@param hasVisited Boolean value to set the visited status.
*/
void RoomContent::setVisited(bool hasVisited)
{
    visited = hasVisited;
}

Game *RoomContent::getNonGamblingGame()
{
    return nonGambilingGame.get();
}

bool RoomContent::emptyItems()
{
    items.clear();
    return items.empty();
}
