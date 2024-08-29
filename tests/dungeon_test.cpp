// #include "../helper/minigames.cpp"
#include "../lib/toolkit.h"
#include "../lib/room.h"
#include "../lib/dungeon.h"
#include "custom_test_framework.h"

// cd tests
// g++ -std=c++17 -o run_tests.exe dungeon_test.cpp ../helper/room.cpp ../helper/dungeon.cpp ../helper/minigames.cpp ../helper/toolkit.cpp
// ./run_tests.exe

// Test if the dungeon generates the correct number of rooms
void testDungeonRoomGeneration()
{
    Dungeon dungeon;
    Room *startRoom = dungeon.generateFloor(10);

    ASSERT(startRoom != nullptr);
    int numRoom = dungeon.numRooms(startRoom);
    ASSERT_EQUAL(10, numRoom); // Assuming you add a getRoomCount method in the Dungeon class
}

// Test if the dungeon destructor correctly deletes rooms to avoid memory leaks
void testDungeonDestructor()
{
    Dungeon dungeon;
    Room *startRoom = dungeon.generateFloor(10);

    int numRoom = dungeon.numRooms(startRoom);
    // Assuming getRoomCount returns the number of rooms before deletion
    ASSERT_EQUAL(10, numRoom);

    delete startRoom;

    int numRoom2 = dungeon.numRooms(startRoom);
    ASSERT_EQUAL(0, numRoom2);
}

void testLinkRooms()
{
    Dungeon dungeon;
    Room *newRoom1 = new Room();
    Room *newRoom2 = new Room();

    dungeon.linkRooms(newRoom1, newRoom2, 0);
    ASSERT_EQUAL(newRoom1->north, newRoom2);

    dungeon.linkRooms(newRoom1, newRoom2, 1);
    ASSERT_EQUAL(newRoom1->south, newRoom2);

    dungeon.linkRooms(newRoom1, newRoom2, 2);
    ASSERT_EQUAL(newRoom1->west, newRoom2);

    dungeon.linkRooms(newRoom1, newRoom2, 3);
    ASSERT_EQUAL(newRoom1->east, newRoom2);
}

int main()
{
    TestFramework framework("dungeon_test_results.xml");

    framework.addTest("Dungeon Room Generation", testDungeonRoomGeneration);

    framework.addTest("Dungeon Link Room", testLinkRooms);

    framework.run();

    return 0;
}
