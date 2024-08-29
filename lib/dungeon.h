#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <random>
#include <map>
#include <queue>
#include "../lib/room.h"

class Dungeon
{
public:
    // Constructor
    Dungeon();

    // Destructor
    ~Dungeon();

    // Generate a floor with a specified number of rooms
    Room *generateFloor(int numRooms);

    // Traverse the dungeon and print room contents
    void traverseAndPrint(Room *startRoom);

    int numRooms(Room *startRoom);

    void linkRooms(Room *room1, Room *room2, int direction); // making it public for testing

    std::string getMap(Room *room);

private:
    std::vector<Room *> rooms;
    std::mt19937 rng;

    // Generate a new room
    Room *generateRoom(int x, int y);

    // Link two rooms together in a specified direction
    // void linkRooms(Room *room1, Room *room2, int direction);

    // Check and link a new room with existing adjacent rooms
    void checkAndLink(Room *newRoom, int x, int y, std::map<std::pair<int, int>, Room *> &roomMap);
};

#endif // DUNGEON_H
