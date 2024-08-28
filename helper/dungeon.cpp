#include "../lib/dungeon.h"

// Constructor
Dungeon::Dungeon() : rng(static_cast<unsigned int>(std::time(0))) {}

// Destructor
Dungeon::~Dungeon()
{
    for (Room *room : rooms)
    {
        delete room;
    }
}

// Private method to generate a new room
Room *Dungeon::generateRoom()
{
    Room *newRoom = new Room();
    rooms.push_back(newRoom);
    return newRoom;
}

// Private method to link two rooms together in a specified direction
void Dungeon::linkRooms(Room *room1, Room *room2, int direction)
{
    switch (direction)
    {
    case 0: // North
        room1->north = room2;
        room2->south = room1;
        break;
    case 1: // South
        room1->south = room2;
        room2->north = room1;
        break;
    case 2: // West
        room1->west = room2;
        room2->east = room1;
        break;
    case 3: // East
        room1->east = room2;
        room2->west = room1;
        break;
    }
}

// Private method to check and link a new room with existing adjacent rooms
void Dungeon::checkAndLink(Room *newRoom, int x, int y, std::map<std::pair<int, int>, Room *> &roomMap)
{
    // Check north
    if (roomMap.find({x, y + 1}) != roomMap.end())
    {
        linkRooms(newRoom, roomMap[{x, y + 1}], 0);
    }
    // Check south
    if (roomMap.find({x, y - 1}) != roomMap.end())
    {
        linkRooms(newRoom, roomMap[{x, y - 1}], 1);
    }
    // Check west
    if (roomMap.find({x - 1, y}) != roomMap.end())
    {
        linkRooms(newRoom, roomMap[{x - 1, y}], 2);
    }
    // Check east
    if (roomMap.find({x + 1, y}) != roomMap.end())
    {
        linkRooms(newRoom, roomMap[{x + 1, y}], 3);
    }
}

// Public method to generate a floor with a specified number of rooms
Room *Dungeon::generateFloor(int numRooms)
{
    if (numRooms <= 0)
    {
        return nullptr;
    }

    Room *startRoom = generateRoom();
    std::map<std::pair<int, int>, Room *> roomMap;
    roomMap[{0, 0}] = startRoom;

    for (int i = 1; i < numRooms; ++i)
    {
        Room *existingRoom;
        int direction, x = 0, y = 0;

        do
        {
            auto it = roomMap.begin();
            std::advance(it, std::uniform_int_distribution<>(0, (int)roomMap.size() - 1)(rng));
            existingRoom = it->second;
            x = it->first.first;
            y = it->first.second;

            direction = std::uniform_int_distribution<>(0, 3)(rng);
        } while (
            (direction == 0 && existingRoom->north != nullptr) ||
            (direction == 1 && existingRoom->south != nullptr) ||
            (direction == 2 && existingRoom->west != nullptr) ||
            (direction == 3 && existingRoom->east != nullptr));

        int newX = x, newY = y;

        switch (direction)
        {
        case 0:
            newY += 1;
            break; // North
        case 1:
            newY -= 1;
            break; // South
        case 2:
            newX -= 1;
            break; // West
        case 3:
            newX += 1;
            break; // East
        }

        Room *newRoom = generateRoom();
        roomMap[{newX, newY}] = newRoom;
        linkRooms(existingRoom, newRoom, direction);

        // Check and link to adjacent rooms
        checkAndLink(newRoom, newX, newY, roomMap);
    }

    return rooms[std::uniform_int_distribution<>(0, (int)rooms.size() - 1)(rng)];
}

// Public method to traverse the dungeon and print room contents
void Dungeon::traverseAndPrint(Room *startRoom)
{
    if (startRoom == nullptr)
        return;

    std::queue<std::pair<Room *, std::pair<int, int>>> q;
    std::map<std::pair<int, int>, Room *> visited;

    q.push({startRoom, {0, 0}});
    visited[{0, 0}] = startRoom;

    while (!q.empty())
    {
        auto [currentRoom, coords] = q.front();
        q.pop();

        int x = coords.first;
        int y = coords.second;
        std::cout << "\nRoom at (" << x << ", " << y << "): \n\nRoom content:" << std::endl;
        currentRoom->roomContent.displayContent();
        std::cout << "--------------------" << std::endl;

        if (currentRoom->north && visited.find({x, y + 1}) == visited.end())
        {
            q.push({currentRoom->north, {x, y + 1}});
            visited[{x, y + 1}] = currentRoom->north;
        }
        if (currentRoom->south && visited.find({x, y - 1}) == visited.end())
        {
            q.push({currentRoom->south, {x, y - 1}});
            visited[{x, y - 1}] = currentRoom->south;
        }
        if (currentRoom->east && visited.find({x + 1, y}) == visited.end())
        {
            q.push({currentRoom->east, {x + 1, y}});
            visited[{x + 1, y}] = currentRoom->east;
        }
        if (currentRoom->west && visited.find({x - 1, y}) == visited.end())
        {
            q.push({currentRoom->west, {x - 1, y}});
            visited[{x - 1, y}] = currentRoom->west;
        }
    }
}
