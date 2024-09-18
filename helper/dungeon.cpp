/*!
@file dungeon.cpp
@brief Implementation of the Dungeon class.
@details This file contains the implementation of the Dungeon class, which manages the creation and traversal of a dungeon made up of interconnected rooms. The class includes methods for generating rooms, linking them, displaying maps, and traversing the dungeon.
*/

#include "../lib/dungeon.h"
#include <queue>
#include <set>
#include <memory> // For std::shared_ptr

/*!
@brief Constructor for the Dungeon class.
@details Initializes the random number generator with the current time to ensure different dungeon layouts each time.
*/
Dungeon::Dungeon() : rng(static_cast<unsigned int>(std::time(0))) {}

/*!
@brief Destructor for the Dungeon class.
@details Cleans up dynamically allocated Room objects when the Dungeon object is destroyed.
*/
Dungeon::~Dungeon()
{
    for (Room *room : rooms)
    {
        delete room;
    }
}

/*!
@brief Private method to generate a new room at specific coordinates.
@param x The x-coordinate of the new room.
@param y The y-coordinate of the new room.
@return A pointer to the newly created Room object.
*/
Room *Dungeon::generateRoom(int x, int y)
{
    Room *newRoom = new Room();
    newRoom->roomContent.addCoordinates(x, y);
    rooms.push_back(newRoom);
    return newRoom;
}

/*!
@brief Private method to link two rooms together in a specified direction.
@param room1 The first room to link.
@param room2 The second room to link.
@param direction The direction from room1 to room2 (0: North, 1: South, 2: West, 3: East).
*/
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

/*!
@brief Private method to check and link a new room with existing adjacent rooms.
@param newRoom The new room to link.
@param x The x-coordinate of the new room.
@param y The y-coordinate of the new room.
@param roomMap A map of existing rooms by their coordinates.
*/
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

/*!
@brief Get a string representation of the dungeon map centered on a specific room.
@param room The room to center the map on.
@return A string representing the map of the dungeon.
@details The map displays a 5x5 grid centered on the given room, with visited rooms marked with '*', unvisited rooms with 'X', and the current room in blue.
*/
std::string Dungeon::getMap(Room *room)
{
    room->roomContent.setVisited(true);
    std::queue<Room *> roomQueue;
    std::set<std::pair<int, int>> visitedRooms;
    roomQueue.push(room);

    int originX = room->roomContent.getCoordinates().first;
    int originY = room->roomContent.getCoordinates().second;

    std::map<std::pair<int, int>, bool> roomsForMap;
    std::map<std::pair<int, int>, bool> roomsVisited;

    for (int i = 0; i < (int)rooms.size(); i++)
    {
        roomsVisited[rooms[i]->roomContent.getCoordinates()] = rooms[i]->roomContent.getVisited();
    }

    while (!roomQueue.empty())
    {
        Room *currentRoom = roomQueue.front();
        roomQueue.pop();

        int currX = currentRoom->roomContent.getCoordinates().first;
        int currY = currentRoom->roomContent.getCoordinates().second;

        if (currX > originX + 2 || currX < originX - 2 || currY > originY + 2 || currY < originY - 2)
        {
            continue;
        }

        if (visitedRooms.find({currX, currY}) != visitedRooms.end())
        {
            continue;
        }

        roomsForMap[currentRoom->roomContent.getCoordinates()] = true;
        visitedRooms.insert(currentRoom->roomContent.getCoordinates());
        roomsVisited[currentRoom->roomContent.getCoordinates()] = currentRoom->roomContent.getVisited();

        if (currentRoom->north)
        {
            roomQueue.push(currentRoom->north);
        }
        if (currentRoom->east)
        {
            roomQueue.push(currentRoom->east);
        }
        if (currentRoom->south)
        {
            roomQueue.push(currentRoom->south);
        }
        if (currentRoom->west)
        {
            roomQueue.push(currentRoom->west);
        }
    }

    std::string map = "+ - - - - - +\n";
    for (int y = originY + 2; y >= originY - 2; y--)
    {
        map.append("| ");
        for (int x = originX - 2; x <= originX + 2; x++)
        {
            auto it = roomsForMap.find(std::make_pair(x, y));
            auto it2 = roomsVisited.find(std::make_pair(x, y));
            if (it != roomsForMap.end())
            {
                std::string roomToken = "X ";
                if (it2->second)
                {
                    roomToken = "* ";
                }
                if (x == originX && y == originY)
                {
                    map.append("\033[34m" + roomToken + "\033[37m");
                }
                else
                {
                    map.append(roomToken);
                }
            }
            else
            {
                map.append("  ");
            }
        }
        map.append("|\n");
    }
    map.append("+ - - - - - +\n");
    return map;
}

/*!
@brief Public method to generate a floor with a specified number of rooms.
@param numRooms The number of rooms to generate.
@return A pointer to a randomly selected Room object from the generated floor.
@details This method generates a floor by creating a starting room and linking additional rooms to it until the specified number of rooms is reached.
*/
Room *Dungeon::generateFloor(int numRooms)
{
    if (numRooms <= 0)
    {
        return nullptr;
    }

    Room *startRoom = generateRoom(0, 0);
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

        Room *newRoom = generateRoom(newX, newY);
        roomMap[{newX, newY}] = newRoom;
        linkRooms(existingRoom, newRoom, direction);

        checkAndLink(newRoom, newX, newY, roomMap);
    }

    return rooms[std::uniform_int_distribution<>(0, (int)rooms.size() - 1)(rng)];
}

/*!
@brief Public method to count the number of rooms in the dungeon.
@param startRoom A pointer to the room where the count begins.
@return The number of rooms in the dungeon.
@details Counts the total number of rooms in the dungeon starting from the given room and traversing all connected rooms.
*/
int Dungeon::numRooms(Room *startRoom)
{
    if (startRoom == nullptr)
        return 0;

    std::queue<std::pair<Room *, std::pair<int, int>>> q;
    std::map<std::pair<int, int>, Room *> visited;

    q.push({startRoom, {0, 0}});
    visited[{0, 0}] = startRoom;

    int roomCount = 0;

    while (!q.empty())
    {
        auto [currentRoom, coords] = q.front();
        q.pop();

        int x = coords.first;
        int y = coords.second;

        roomCount++;

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
    return roomCount;
}
