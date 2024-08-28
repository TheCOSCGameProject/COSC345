#include "../lib/minigames.h"
#include "../lib/combat.h"
#include "../lib/dungeon.h"
#include "../lib/player.h"
#include "../lib/room.h"
#include "../lib/toolkit.h"
#include "../lib/weapon.h"

#include "custom_test_framework.h"
#include "cassert"
#include <sstream>

void testTicTacToeInitialization()
{
    TicTacToe game;
    // Test that the board is initially empty
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ASSERT_EQUAL(' ', game.getSquare(i, j));
        }
    }
}

void testTicTacToePlayerMove()
{
    TicTacToe game;
    game.playerMove(0, 0);
    ASSERT_EQUAL('X', game.getSquare(0, 0));
}
void testTicTacToeComputerTurn()
{
    TicTacToe game;
    game.computerTurn();
    // Check that the computer has made a move (one square should be 'O')
    bool computerMoved = false;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (game.getSquare(i, j) == 'O')
            {
                computerMoved = true;
                break;
            }
        }
        if (computerMoved)
            break;
    }
    ASSERT(computerMoved);
}

void testTicTacToeCheckForWin()
{
    TicTacToe game;
    // Test horizontal win
    game.playerMove(0, 0);
    game.playerMove(0, 1);
    game.playerMove(0, 2);
    ASSERT(game.checkForWin());

    // Reset and test vertical win
    game = TicTacToe();
    game.playerMove(0, 0);
    game.playerMove(1, 0);
    game.playerMove(2, 0);
    ASSERT(game.checkForWin());

    // Reset and test diagonal win
    game = TicTacToe();
    game.playerMove(0, 0);
    game.playerMove(1, 1);
    game.playerMove(2, 2);
    ASSERT(game.checkForWin());
}

/* These two are currently set up for input, can easily change the player.h and cpp to have a default case but for now is fine as is.
void testPlayerInitialization()
{
    Player player;
    ASSERT(player.getName() != "");
    ASSERT(player.getClassType() != "");
    ASSERT_EQUAL(100, player.getMaxHealth());
    ASSERT_EQUAL(100, player.getCurrHealth());
}

void testPlayerInventory()
{
    Player player;
    player.addToInventory("Sword");
    ASSERT_EQUAL(1, player.getInventory().size());
    ASSERT_EQUAL("Sword", player.getInventory()[0]);

    player.removeFromInventory("Sword");
    ASSERT_EQUAL(0, player.getInventory().size());
}
*/
// New Room tests
void testRoomInitialization()
{
    Room room;
    ASSERT(room.north == nullptr);
    ASSERT(room.south == nullptr);
    ASSERT(room.east == nullptr);
    ASSERT(room.west == nullptr);
}

// New Weapon tests
void testWeaponInitialization()
{
    Weapon weaponSystem;
    int weaponId = weaponSystem.giveRandWeapon();
    ASSERT(weaponId >= 1 && weaponId <= 27);
    ASSERT(weaponSystem.getName(weaponId) != "");
    ASSERT(weaponSystem.getDamage(weaponId) > 0);
}

// New Toolkit tests
void testGenerateRandomNumber()
{
    int low = 1, high = 10;
    int result = generateRandomNumber(low, high);
    ASSERT(result >= low && result <= high);
}

void testStringToInt()
{
    ASSERT_EQUAL(123, stringToInt("123"));
    ASSERT_EQUAL(0, stringToInt("abc")); // Invalid input should return 0
}

// New Combat tests
void testCombatV1()
{
    // Redirect cout to capture output
    std::stringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int playerHealth = 100;
    int enemyHealth = 50;
    int difficulty = 1000; // 1 second

    // Mock user input
    std::istringstream input("w\n");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    combatV1(playerHealth, enemyHealth, difficulty, "Enemy");

    // Restore cout and cin
    std::cout.rdbuf(oldCout);
    std::cin.rdbuf(oldCin);

    std::string output = buffer.str();
    ASSERT(output.find("Player Health: 100") != std::string::npos);
    ASSERT(output.find("Enemy Health: 45") != std::string::npos);
}

// New Dungeon tests
// void testDungeonGeneration()
// {
//     Dungeon dungeon;
//     Room *startRoom = dungeon.generateFloor(5);
//     ASSERT(startRoom != nullptr);

//     // Count rooms
//     std::set<Room *> visitedRooms;
//     std::queue<Room *> roomQueue;
//     roomQueue.push(startRoom);

//     while (!roomQueue.empty())
//     {
//         Room *currentRoom = roomQueue.front();
//         roomQueue.pop();

//         if (visitedRooms.find(currentRoom) == visitedRooms.end())
//         {
//             visitedRooms.insert(currentRoom);

//             if (currentRoom->north)
//                 roomQueue.push(currentRoom->north);
//             if (currentRoom->south)
//                 roomQueue.push(currentRoom->south);
//             if (currentRoom->east)
//                 roomQueue.push(currentRoom->east);
//             if (currentRoom->west)
//                 roomQueue.push(currentRoom->west);
//         }
//     }

//     ASSERT_EQUAL(5, visitedRooms.size());
// }

int main()
{
    TestFramework framework("minigames_test_results.xml");

    // Existing TicTacToe tests
    framework.addTest("TicTacToe Initialization", testTicTacToeInitialization);
    framework.addTest("TicTacToe Player Move", testTicTacToePlayerMove);
    framework.addTest("TicTacToe Computer Turn", testTicTacToeComputerTurn);
    framework.addTest("TicTacToe Check For Win", testTicTacToeCheckForWin);
    /*
    // New Player tests
    framework.addTest("Player Initialization", testPlayerInitialization);
    framework.addTest("Player Inventory", testPlayerInventory);
`   */
    // New Room tests
    // framework.addTest("Room Initialization", testRoomInitialization);

    // // New Weapon tests
    // framework.addTest("Weapon Initialization", testWeaponInitialization);

    // // New Toolkit tests
    // framework.addTest("Generate Random Number", testGenerateRandomNumber);
    // framework.addTest("String to Int Conversion", testStringToInt);

    // // New Combat tests
    // framework.addTest("Combat V1", testCombatV1);

    // // New Dungeon tests
    // // framework.addTest("Dungeon Generation", testDungeonGeneration);
    framework.run();

    return 0;
}

// g++ -std=c++11 -o run_tests.exe tests/minigames_test.cpp

//./run_tests.exe

// g++ -std=c++17 -o run_tests.exe tests/minigames_test.cpp

// g++ -std=c++17 -o run_tests.exe tests/minigames_test.cpp
// g++ -std=c++17 -o run_tests.exe tests/minigames_test.cpp helper/minigames.cpp
/*
g++ -std=c++17 -o run_tests.exe \
    tests/minigames_test.cpp \
    helper/minigames.cpp \
    helper/combat.cpp \
    helper/dungeon.cpp \
    helper/player.cpp \
    helper/room.cpp \
    helper/toolkit.cpp \
    helper/weapon.cpp \
    helper/enemies.cpp
*/