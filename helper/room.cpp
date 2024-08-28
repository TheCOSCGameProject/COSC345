#include "../lib/room.h"
#include <iostream>
#include "../lib/toolkit.h"

/**
 * @brief Constructor for the Room class.
 * @details Initializes room directions to nullptr and content to "Empty room".
 */
RoomContent::RoomContent()
{
    this->roomType = generateRandomNumber(0, 1);
    // Call the appropriate method based on roomType
    switch (roomType)
    {
    case 0:
        emptyRoom();
        roomDesc = "Empty Room";
        break;
    case 1:
        gamblingRoom();
        roomDesc = "Gambling Room";
        break;
    default:
        emptyRoom(); // Fallback, although unnecessary with current range
        roomDesc = "Empty Room";
        break;
    }
}

std::string RoomContent::getRoomDesc()
{
    return roomDesc;
}

void RoomContent::gamblingRoom()
{
    int gamblingGameType = generateRandomNumber(0, 1);
    int gameType = generateRandomNumber(0, 1);
    NPC newNPC;
    if (gamblingGameType == 0)
    {
        newNPC.gamblingGame = std::make_unique<TicTacToe>();
    }
    else
    {
        newNPC.gamblingGame = std::make_unique<BlackJack>();
    }
    newNPC.name = "Charlie";
    newNPC.skillLevel = 0;
    this->npc = std::move(newNPC);
}

void RoomContent::emptyRoom()
{
    std::vector<std::string> listOfEnemies = split(getFileContent("../reasources/enemies.txt"), '\n');
    std::vector<std::string> listOfItems = split(getFileContent("../reasources/room_items.txt"), '\n');
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
        int index = generateRandomNumber(0, listOfRoomEnemies.size() - 1);
        addEnemy(listOfRoomEnemies.at(index));
    }

    // Add a random number of items between 1 and 5
    int numItemsToAdd = generateRandomNumber(1, 3);
    for (int i = 0; i < numItemsToAdd && !listRoomItems.empty(); i++)
    {
        int index = generateRandomNumber(0, listRoomItems.size() - 1);
        addItem(listRoomItems.at(index));
    }
}

void RoomContent::addItem(const std::string &item)
{
    items.push_back(item);
}

void RoomContent::addEnemy(const EnemyStruct &enemy)
{
    enemies.push_back(enemy);
}

int RoomContent::getRoomType()
{
    return this->roomType;
}

NPC &RoomContent::getNPC()
{
    return npc;
}

void RoomContent::displayContent() const
{
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
        std::cout << "Gambling Game: " << std::endl;
        std::cout << "Skill Level: " << npc.skillLevel << std::endl;
    }
}

// Room methods
Room::Room() : north(nullptr), south(nullptr), west(nullptr), east(nullptr), roomContent() {}

void Room::displayAvailableDirections()
{
    std::cout << "You can move: ";
    if (north)
        std::cout << "North ";
    if (south)
        std::cout << "South ";
    if (west)
        std::cout << "West ";
    if (east)
        std::cout << "East ";
    std::cout << std::endl;
}