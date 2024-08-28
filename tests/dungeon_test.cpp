// #include "../lib/dungeon.h"
// #include "custom_test_framework.h"

// // Test if the dungeon generates the correct number of rooms
// void testDungeonRoomGeneration()
// {
//     Dungeon dungeon;
//     Room *startRoom = dungeon.generateFloor(10);

//     ASSERT(startRoom != nullptr);
//     int numRoom = dungeon.numRooms(startRoom);
//     ASSERT_EQUAL(10, numRoom); // Assuming you add a getRoomCount method in the Dungeon class
// }

// // // Test if the dungeon links rooms correctly
// // void testDungeonRoomLinking()
// // {
// //     Dungeon dungeon;
// //     Room *startRoom = dungeon.generateFloor(10);

// //     ASSERT(startRoom != nullptr);
// //     int linkedRooms = 0;

// //     for (Room *room : dungeon.getRooms())
// //     {
// //         if (room->north || room->south || room->east || room->west)
// //         {
// //             linkedRooms++;
// //         }
// //     }

// //     ASSERT(linkedRooms > 0); // Ensure at least some rooms are linked
// // }

// // // Test if the dungeon is properly traversed and printed
// // void testDungeonTraversal()
// // {
// //     Dungeon dungeon;
// //     Room *startRoom = dungeon.generateFloor(5);

// //     ASSERT(startRoom != nullptr);

// //     // Mocking traverseAndPrint to check if all rooms are visited
// //     std::map<Room *, bool> visited;
// //     dungeon.traverseAndPrint(startRoom, [&](Room *room)
// //                              { visited[room] = true; });

// //     ASSERT_EQUAL(5, visited.size()); // Ensure all rooms were visited
// // }

// // Test if the dungeon destructor correctly deletes rooms to avoid memory leaks
// void testDungeonDestructor()
// {
//     Dungeon dungeon;
//     Room *startRoom = dungeon.generateFloor(10);

//     int numRoom = dungeon.numRooms(startRoom);
//     // Assuming getRoomCount returns the number of rooms before deletion
//     ASSERT_EQUAL(10, numRoom);

//     delete startRoom;

//     int numRoom2 = dungeon.numRooms(startRoom);
//     ASSERT_EQUAL(0, numRoom2);

//     // To verify memory cleanup, we'd ideally use a tool like Valgrind. For the test, we can only assume
//     // memory was freed correctly since we don't have a getRoomCount method after deletion.
// }

// int main()
// {
//     TestFramework framework("dungeon_test_results.xml");

//     framework.addTest("Dungeon Room Generation", testDungeonRoomGeneration);
//     // framework.addTest("Dungeon Room Linking", testDungeonRoomLinking);
//     // framework.addTest("Dungeon Traversal", testDungeonTraversal);
//     framework.addTest("Dungeon Destructor", testDungeonDestructor);

//     framework.run();

//     return 0;
// }
