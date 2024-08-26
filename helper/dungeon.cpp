#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <queue>
#include <set>
#include <map>
#include "../lib/room.h"
#include "../lib/enemies.h"

class Dungeon
{
private:
    std::vector<Room *> rooms;
    std::mt19937 rng;

    Room *generateRoom()
    {
        Room *newRoom = new Room();
        
        // Generate content for the room
        int roomType = std::uniform_int_distribution<>(0, 2)(rng);

        switch(roomType)
        {
            case 0:
                newRoom->roomContent.emptyRoom();
                break;
            case 1:
                newRoom->roomContent.gamblingRoom();
                break;
            case 2:
                // Use EnemySpawner to add enemies to the room
                EnemySpawner spawner;
                newRoom->roomContent.addEnemy(spawner.spawnEnemy());
                newRoom->roomContent.addItem("Sword");
                break;
        }
        
        rooms.push_back(newRoom);
        return newRoom;
    }

    void linkRooms(Room *room1, Room *room2, int direction)
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

    void checkAndLink(Room *newRoom, int x, int y, std::map<std::pair<int, int>, Room *> &roomMap)
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

public:
    Dungeon() : rng(std::time(0)) {}

    ~Dungeon()
    {
        for (Room *room : rooms)
        {
            delete room;
        }
    }

    Room *generateFloor(int numRooms)
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
                std::advance(it, std::uniform_int_distribution<>(0, roomMap.size() - 1)(rng));
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

        return rooms[std::uniform_int_distribution<>(0, rooms.size() - 1)(rng)];
    }

    void traverseAndPrint(Room *startRoom)
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
            std::cout << "Room at (" << x << ", " << y << "): " << std::endl;
            currentRoom->roomContent.displayContent();

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
};
