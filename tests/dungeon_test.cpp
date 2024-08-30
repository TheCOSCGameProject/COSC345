/**
 * @file dungeon_test.cpp
 * @brief Unit tests for the Dungeon class.
 *
 * This file contains test cases for verifying the correct behavior of the Dungeon class,
 * including room generation, room linking, and memory management through the destructor.
 */

// #include "../helper/minigames.cpp"
#include "../lib/toolkit.h"
#include "../lib/room.h"
#include "../lib/dungeon.h"
#include "custom_test_framework.h"

// cd tests
// g++ -std=c++17 -o run_tests.exe dungeon_test.cpp ../helper/room.cpp ../helper/dungeon.cpp ../helper/minigames.cpp ../helper/toolkit.cpp
// ./run_tests.exe

/**
 * @brief Test if the dungeon generates the correct number of rooms.
 *
 * This test verifies that the generateFloor method in the Dungeon class correctly creates
 * the specified number of rooms and that the starting room is not a null pointer.
 */
void testDungeonRoomGeneration()
{
    Dungeon dungeon;
    Room *startRoom = dungeon.generateFloor(10);

    ASSERT(startRoom != nullptr);
    int numRoom = dungeon.numRooms(startRoom);
    ASSERT_EQUAL(10, numRoom); // Assuming you add a getRoomCount method in the Dungeon class
}

/**
 * @brief Test if the dungeon destructor correctly deletes rooms to avoid memory leaks.
 *
 * This test checks whether the Dungeon class destructor properly deletes the dynamically
 * allocated rooms, ensuring that the number of rooms is zero after deletion.
 */
void testDungeonDestructor()
{
    Dungeon dungeon;
    Room *startRoom = dungeon.generateFloor(10);

    int numRoom = dungeon.numRooms(startRoom);
    ASSERT_EQUAL(10, numRoom);

    delete startRoom;

    int numRoom2 = dungeon.numRooms(startRoom);
    ASSERT_EQUAL(0, numRoom2);
}

/**
 * @brief Test the linking of rooms in the dungeon.
 *
 * This test ensures that rooms are correctly linked in all four directions (north, south, west, east)
 * using the linkRooms method in the Dungeon class.
 */
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

/**
 * @brief Main function that runs the test cases for the Dungeon class.
 *
 * The main function creates a TestFramework object, adds the test cases for the Dungeon class,
 * and then runs the tests, outputting the results to an XML file.
 *
 * @return int Returns 0 upon successful execution of the tests.
 */
int main()
{
    TestFramework framework("dungeon_test_results.xml");

    framework.addTest("Dungeon Room Generation", testDungeonRoomGeneration);

    framework.addTest("Dungeon Link Room", testLinkRooms);

    framework.run();

    return 0;
}
