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
    switch (roomType)
    {
    case 0:
        emptyRoom();
        roomDesc = "Empty Room";
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
            roomDesc = "Gambling Room containing a " + this->npc.name + " who wants to play " + npc.gamblingGame->getGameName();
        }
        else
        {
            roomDesc = "Gambling Room containing a with an unknown game";
        }
        break;
    default:
        emptyRoom(); // Fallback
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
    NPC newNPC;

    if (gamblingGameType == 0)
    {
        newNPC.gamblingGame = std::make_unique<TicTacToe>();
    }
    else
    {
        newNPC.gamblingGame = std::make_unique<BlackJack>();
    }

    // std::cout << "Hello2";

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
        int index = generateRandomNumber(0, (int)listOfRoomEnemies.size() - 1);
        addEnemy(listOfRoomEnemies.at(index));
    }

    // Add a random number of items between 1 and 5
    int numItemsToAdd = generateRandomNumber(1, 3);
    for (int i = 0; i < numItemsToAdd && !listRoomItems.empty(); i++)
    {
        int index = generateRandomNumber(0, (int)listRoomItems.size() - 1);
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

std::vector<EnemyStruct> RoomContent::getEnemies()
{
    return enemies;
}

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
        std::cout << "Gambling Game: " << std::endl;
        std::cout << "Skill Level: " << npc.skillLevel << std::endl;
    }
}

// Room methods
Room::Room() : north(nullptr), south(nullptr), west(nullptr), east(nullptr), roomContent() {}

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

void RoomContent::addCoordinates(int x, int y)
{
    cords = std::make_pair(x, y);
}

std::pair<int, int> RoomContent::getCoordinates()
{
    return cords;
}

bool RoomContent::getVisited()
{
    return visited;
}

void RoomContent::setVisited(bool hasVisited)
{
    visited = hasVisited;
}
