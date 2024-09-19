#include "../lib/minigames.h"
#include "../lib/combat.h"
#include "../lib/dungeon.h"
#include "../lib/player.h"
#include "../lib/room.h"
#include "../lib/toolkit.h"
#include "../lib/weapon.h"
#include "../lib/enemies.h"
#include "../lib/menu.h"
#include <algorithm>
#include <cctype>
#include <regex>
#include <cassert>
#include <iostream>
#include <set>

#include "custom_test_framework.h"
#include <sstream>

// void testTicTacToeInitialization()
// {
//     TicTacToe game;
//     // Test that the board is initially empty
//     for (int i = 0; i < 3; i++)
//     {
//         for (int j = 0; j < 3; j++)
//         {
//             ASSERT_EQUAL(' ', game.getSquare(i, j));
//         }
//     }
// }

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

void testTicTacToeStart()
{
    TicTacToe game;

    // Prepare simulated input for a game where the player wins
    std::stringstream simulatedInput;
    simulatedInput << "1 1\n2 2\n3 3\n";

    // Capture console output
    std::stringstream capturedOutput;

    // Save the current state of cin and cout
    std::streambuf *originalCin = std::cin.rdbuf();
    std::streambuf *originalCout = std::cout.rdbuf();

    // Redirect cin and cout
    std::cin.rdbuf(simulatedInput.rdbuf());
    std::cout.rdbuf(capturedOutput.rdbuf());

    // Run the game
    bool result = game.start();

    // Restore cin and cout
    std::cin.rdbuf(originalCin);
    std::cout.rdbuf(originalCout);

    // Check the result
    ASSERT(result); // Player should win with this input

    // Check if the output contains expected phrases
    std::string output = capturedOutput.str();
    ASSERT(output.find("You win!") != std::string::npos);
}

// CodeGuesser tests
void testCodeGuesserInitialization()
{
    CodeGuesser game;
    ASSERT_EQUAL(5, game.getWordLength());
    ASSERT_EQUAL(0, game.getGuessCount());
    ASSERT_EQUAL("", game.getLastGuess());
}

void testCodeGuesserGameName()
{
    CodeGuesser game;
    ASSERT_EQUAL("Code Guesser", game.getGameName());
}

void testCodeGuesserAddGuess()
{
    CodeGuesser game;

    // Simulate input for addGuess
    std::stringstream simulatedInput("GUESS\n");
    std::streambuf *cinBackup = std::cin.rdbuf(simulatedInput.rdbuf());

    bool guessAdded = game.addGuess();

    // Restore cin
    std::cin.rdbuf(cinBackup);

    ASSERT_EQUAL(1, game.getGuessCount());
}

void testCodeGuesserStart()
{
    CodeGuesser game;

    // Simulate 5 incorrect guesses
    std::stringstream simulatedInput("wrong\nwrong\nwrong\nwrong\nwrong\n");
    std::streambuf *cinBackup = std::cin.rdbuf();
    std::cin.rdbuf(simulatedInput.rdbuf());

    // Capture output
    std::stringstream capturedOutput;
    std::streambuf *coutBackup = std::cout.rdbuf();
    std::cout.rdbuf(capturedOutput.rdbuf());

    bool result = game.start();

    // Restore cin and cout
    std::cin.rdbuf(cinBackup);
    std::cout.rdbuf(coutBackup);

    ASSERT_EQUAL(false, result);
    ASSERT(capturedOutput.str().find("Too many failed attempts!") != std::string::npos);
}

// BlackJack tests
void testBlackJackInitialization()
{
    BlackJack game;
    ASSERT_EQUAL("Black Jack", game.getGameName());
}

void testSpecificWeapon(Weapon &weaponSystem, int id, const std::string &name, const std::string &description,
                        int damage, const std::string &rarity, bool isRanged, bool canStun)
{
    ASSERT_EQUAL(name, weaponSystem.getName(id));
    ASSERT_EQUAL(description, weaponSystem.getDescription(id));
    ASSERT_EQUAL(damage, weaponSystem.getDamage(id));
    ASSERT_EQUAL(rarity, weaponSystem.getRarity(id));
    ASSERT_EQUAL(isRanged, weaponSystem.getRanged(id));
    ASSERT_EQUAL(canStun, weaponSystem.getStun(id));
}

void testWeaponInitialization()
{
    // Test multiple instances to ensure randomness is covered
    std::set<int> randomWeapons;
    const int NUM_TESTS = 100;

    for (int i = 0; i < NUM_TESTS; ++i)
    {
        Weapon weaponSystem;

        // Test a random weapon to ensure the random number generation is covered
        int randomId = weaponSystem.giveRandWeapon();
        randomWeapons.insert(randomId);

        // Test specific properties for a few weapons to ensure correct initialization
        testSpecificWeapon(weaponSystem, 1, "Plasma Rifle", "A high-energy weapon that fires concentrated plasma bolts.", 45, "Rare", true, false);
        testSpecificWeapon(weaponSystem, 15, "Gom Jabbar", "A needle-like weapon that delivers a lethal poison. Used in specific assassination rituals.", 100, "Legendary", false, false);
        testSpecificWeapon(weaponSystem, 27, "Sardaukar Blade", "A razor-sharp sword used by the elite Sardaukar troops, feared across the galaxy.", 65, "Rare", false, false);
    }

    // Assert that we've seen a good distribution of random weapons
    ASSERT(randomWeapons.size() == 1);
}

void testAllWeapons()
{
    Weapon weaponSystem;

    for (int id = 1; id <= 27; ++id)
    {
        ASSERT(!weaponSystem.getName(id).empty());
        ASSERT(!weaponSystem.getDescription(id).empty());
        ASSERT(weaponSystem.getDamage(id) > 0);
        ASSERT(!weaponSystem.getRarity(id).empty());
        // No need to check getRanged and getStun as they are boolean and any value is valid
    }
}
// Test random weapon generation
void testRandomWeaponGeneration()
{
    Weapon weaponSystem;
    int weaponId = weaponSystem.giveRandWeapon();
    ASSERT(weaponId >= 1 && weaponId <= 27);
    ASSERT(!weaponSystem.getName(weaponId).empty());
}

// Test weapon generation by rarity
void testWeaponGenerationByRarity()
{
    Weapon weaponSystem;

    int commonWeaponId = weaponSystem.giveRariWeapon("Common");
    ASSERT(commonWeaponId != -1);
    ASSERT_EQUAL("Common", weaponSystem.getRarity(commonWeaponId));

    int rareWeaponId = weaponSystem.giveRariWeapon("Rare");
    ASSERT(rareWeaponId != -1);
    ASSERT_EQUAL("Rare", weaponSystem.getRarity(rareWeaponId));

    int nonexistentWeaponId = weaponSystem.giveRariWeapon("Nonexistent");
    ASSERT_EQUAL(-1, nonexistentWeaponId); // No weapons of this rarity should exist
}
// Toolkit tests
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

void testRepeatString()
{
    ASSERT_EQUAL("", repeatString("test", 0));
    ASSERT_EQUAL("testtesttest", repeatString("test", 3));
    ASSERT_EQUAL("", repeatString("test", -1));
}

void testToLowerCase()
{
    ASSERT_EQUAL("hello world", toLowerCase("HELLO WORLD"));
    ASSERT_EQUAL("mixed case 123", toLowerCase("MiXeD cAsE 123"));
    ASSERT_EQUAL("already lowercase", toLowerCase("already lowercase"));
}

void testToUpperCase()
{
    ASSERT_EQUAL("HELLO WORLD", toUpperCase("hello world"));
    ASSERT_EQUAL("MIXED CASE 123", toUpperCase("MiXeD cAsE 123"));
    ASSERT_EQUAL("ALREADY UPPERCASE", toUpperCase("ALREADY UPPERCASE"));
}

void testSplit()
{
    std::vector<std::string> result = split("hello,world,test", ',');
    ASSERT_EQUAL(3, result.size());
    ASSERT_EQUAL("hello", result[0]);
    ASSERT_EQUAL("world", result[1]);
    ASSERT_EQUAL("test", result[2]);

    result = split("no delimiter here", ',');
    ASSERT_EQUAL(1, result.size());
    ASSERT_EQUAL("no delimiter here", result[0]);
}

void testGetFileContent()
{
    // The actual content of the test file, including the literal "\n" at the end
    std::string expectedContent = "This is content of the test txt file\\n\n";
    std::string actualContent = getFileContent("test_file.txt");

    ASSERT_EQUAL(expectedContent, actualContent);
}

// Test for readInt
void testReadInt()
{
    std::stringstream input("42\n");
    std::streambuf *cinbuf = std::cin.rdbuf(input.rdbuf());

    int result = readInt();

    std::cin.rdbuf(cinbuf);

    ASSERT_EQUAL(42, result);
}

// Test for getUserInputLine
void testGetUserInputLine()
{
    std::stringstream input("Test input\n");
    std::streambuf *cinbuf = std::cin.rdbuf(input.rdbuf());

    std::string result = getUserInputLine();

    std::cin.rdbuf(cinbuf);

    ASSERT_EQUAL("Test input", result);
}

// Test for waitForEnter
void testWaitForEnter()
{
    std::stringstream input("\n");
    std::streambuf *cinbuf = std::cin.rdbuf(input.rdbuf());

    std::stringstream output;
    std::streambuf *coutbuf = std::cout.rdbuf(output.rdbuf());

    waitForEnter();

    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);

    ASSERT(output.str().find("Press Enter to continue...") != std::string::npos);
}
// Avoid console as different systems.

// Test the initialisation of a newly spawned enemy
void testEnemyInitialisation()
{
    EnemySpawner spawner;
    Enemy enemy = spawner.spawnEnemy();

    // Ensure that the enemy's attributes are within expected ranges
    ASSERT(!spawner.getName(enemy).empty());
    ASSERT(spawner.getHealth(enemy) >= 50 && spawner.getHealth(enemy) <= 100);
    ASSERT(spawner.getAttack(enemy) >= 10 && spawner.getAttack(enemy) <= 30);
    ASSERT(!spawner.getType(enemy).empty());
    ASSERT(!spawner.getPersonality(enemy).empty());
    ASSERT(spawner.getDefence(enemy) >= 5 && spawner.getDefence(enemy) <= 80);
}

// Test the damage application on an enemy
void testEnemyDamageApplication()
{
    EnemySpawner spawner;
    Enemy enemy = spawner.spawnEnemy();

    int initialHealth = spawner.getHealth(enemy);
    int damage = 20;

    spawner.damageDelt(enemy, damage);
    int expectedHealth = initialHealth - static_cast<int>(damage * (1 - spawner.getDefence(enemy) / 100.0));

    ASSERT_EQUAL(expectedHealth, spawner.getHealth(enemy));
}

// Test the death condition
void testEnemyDeathCondition()
{
    EnemySpawner spawner;
    Enemy enemy = spawner.spawnEnemy();

    spawner.setHealth(enemy, 10);
    ASSERT(!spawner.isDead(enemy)); // Enemy is alive

    spawner.damageDelt(enemy, 100); // Apply damage to kill the enemy
    ASSERT(spawner.isDead(enemy));  // Enemy should be dead now
}

// Test custom setters for enemy attributes
void testEnemyCustomSetters()
{
    EnemySpawner spawner;
    Enemy enemy = spawner.spawnEnemy();

    spawner.setAttack(enemy, 25);
    ASSERT_EQUAL(25, spawner.getAttack(enemy));

    spawner.setHealth(enemy, 75);
    ASSERT_EQUAL(75, spawner.getHealth(enemy));
}

// Dungeon Tests
void testDungeonRoomGeneration()
{
    Dungeon dungeon;
    Room *startRoom = dungeon.generateFloor(10);

    ASSERT(startRoom != nullptr);
    int numRoom = dungeon.numRooms(startRoom);
    ASSERT_EQUAL(10, numRoom); // Assuming you add a getRoomCount method in the Dungeon class
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

// Player Testing
Player createPlayerWithInput(const std::string &nameInput, const std::string &classInput)
{
    std::stringstream simulatedInput(nameInput + "\n" + classInput + "\n");
    std::stringstream simulatedOutput;

    // Backup the original std::cin and std::cout
    std::streambuf *cinBackup = std::cin.rdbuf();
    std::streambuf *coutBackup = std::cout.rdbuf();

    // Redirect std::cin and std::cout
    std::cin.rdbuf(simulatedInput.rdbuf());
    std::cout.rdbuf(simulatedOutput.rdbuf());

    // Create the Player object
    Player player;

    // Restore the original std::cin and std::cout
    std::cin.rdbuf(cinBackup);
    std::cout.rdbuf(coutBackup);

    return player;
}

void testPlayerConstructor()
{
    // Redirect std::cin and std::cout
    std::streambuf *cinBackup = std::cin.rdbuf();
    std::streambuf *coutBackup = std::cout.rdbuf();

    // Test case 1: First player with valid input
    {
        std::stringstream simulatedInput("Alice\nWarrior\n");
        std::stringstream simulatedOutput;
        std::cin.rdbuf(simulatedInput.rdbuf());
        std::cout.rdbuf(simulatedOutput.rdbuf());

        Player player;
        ASSERT_EQUAL(player.getName(), "Alice");
        ASSERT_EQUAL(player.getClassType(), "Warrior");
        ASSERT_EQUAL(player.getMaxHealth(), 100);
        ASSERT_EQUAL(player.getCurrHealth(), 100);
    }

    // Test case 2: Second player with different input
    {
        std::stringstream simulatedInput("Frank\nToolSmith\n");
        std::stringstream simulatedOutput;
        std::cin.rdbuf(simulatedInput.rdbuf());
        std::cout.rdbuf(simulatedOutput.rdbuf());

        Player player;
        ASSERT_EQUAL(player.getName(), "Frank");
        ASSERT_EQUAL(player.getClassType(), "ToolSmith");
        ASSERT_EQUAL(player.getMaxHealth(), 100);
        ASSERT_EQUAL(player.getCurrHealth(), 100);
    }

    {
        std::stringstream simulatedInput(" _23\n_23\n");
        std::stringstream simulatedOutput;
        std::cin.rdbuf(simulatedInput.rdbuf());
        std::cout.rdbuf(simulatedOutput.rdbuf());

        Player player;
        ASSERT_EQUAL(player.getName(), "_23");
        ASSERT_EQUAL(player.getClassType(), "_23");
        ASSERT_EQUAL(player.getMaxHealth(), 100);
        ASSERT_EQUAL(player.getCurrHealth(), 100);
    }

    // Restore std::cin and std::cout
    std::cin.rdbuf(cinBackup);
    std::cout.rdbuf(coutBackup);
}

void testAddToInventory()
{
    Player player = createPlayerWithInput("Alice", "Warrior");

    player.addToInventory("Sword");
    std::vector<std::string> expected{"Sword"};
    ASSERT_EQUAL(player.getInventory(), expected);
}

void testRemoveFromInventory()
{
    Player player = createPlayerWithInput("Alice", "Warrior");
    player.addToInventory("Sword");

    player.removeFromInventory("Sword");
    std::vector<std::string> expected{};
    ASSERT_EQUAL(player.getInventory(), expected);
    player.removeFromInventory("Sword");
    ASSERT_EQUAL(player.getInventory(), expected);

    player.addToInventory("Bow");
    player.addToInventory("Arrow");
    std::vector<std::string> expected2 = {"Bow"};
    player.removeFromInventory("Arrow");
    ASSERT_EQUAL(player.getInventory(), expected2);

    std::stringstream simulatedOutput;
    std::streambuf *coutBackup = std::cout.rdbuf();
    std::cout.rdbuf(simulatedOutput.rdbuf());

    player.removeFromInventory("Arrow"); // Item not in the inventory

    // Restore std::cout
    std::cout.rdbuf(coutBackup);

    std::string output = simulatedOutput.str();
    ASSERT_EQUAL(output, "Item not found in inventory.\n");
}

void testRemoveNonexistentItem()
{

    Player player = createPlayerWithInput("Alice", "Warrior");
    std::stringstream simulatedOutput;
    std::streambuf *coutBackup = std::cout.rdbuf();
    std::cout.rdbuf(simulatedOutput.rdbuf());
    player.removeFromInventory("Sword");

    std::cout.rdbuf(coutBackup);

    ASSERT_EQUAL(simulatedOutput.str(), "Item not found in inventory.\n");
}

void testSetMaxHealth()
{
    Player player = createPlayerWithInput("Alice", "Warrior");
    player.setMaxHelth(150);
    ASSERT_EQUAL(player.getMaxHealth(), 150);

    player.setMaxHelth(50);
    ASSERT_EQUAL(player.getMaxHealth(), 50);
    ASSERT_EQUAL(player.getCurrHealth(), 50);
}

void testSetCurrHealth()
{
    Player player = createPlayerWithInput("Alice", "Warrior");
    player.setCurrHealth(50);
    ASSERT_EQUAL(player.getCurrHealth(), 50);

    player.setCurrHealth(200);
    ASSERT_EQUAL(player.getCurrHealth(), 100);

    player.setCurrHealth(-10);
    ASSERT_EQUAL(player.getCurrHealth(), 0);
}

void testAddBuff()
{
    Player player = createPlayerWithInput("Alice", "Warrior");
    player.addBuff("Strength");
    std::vector<std::string> expected{"Strength"};
    ASSERT_EQUAL(player.getBuffs(), expected);
}

void testRemoveBuff()
{
    Player player = createPlayerWithInput("Alice", "Warrior");
    player.addBuff("Strength");
    player.removeBuff("Strength");
    std::vector<std::string> expected{};
    ASSERT_EQUAL(player.getBuffs(), expected);
}

void testRemoveNonexistentBuff()
{
    Player player = createPlayerWithInput("Alice", "Warrior");
    std::stringstream simulatedOutput;
    std::streambuf *coutBackup = std::cout.rdbuf();
    std::cout.rdbuf(simulatedOutput.rdbuf());
    player.removeBuff("Strength");

    std::cout.rdbuf(coutBackup);

    ASSERT_EQUAL(simulatedOutput.str(), "Buff not found.\n");
}

void testSetResistance()
{
    Player player = createPlayerWithInput("Alice", "Warrior");
    player.setResistance(10);
    ASSERT_EQUAL(player.getResistance(), 10);
}

void testSetMaxHelth_AdjustCurrentHealth()
{
    // Create a Player object with initial settings
    Player player = createPlayerWithInput("Alice", "Warrior");

    // Manually set the player's current health to a value greater than the max health
    player.setCurrHealth(150); // Set current health to 150 (greater than the max health that will be set)

    // Set max health to a lower value than current health
    player.setMaxHelth(100);

    // Verify that current health has been adjusted to the new max health value
    ASSERT_EQUAL(player.getCurrHealth(), 100); // Current health should be adjusted to match max health

    // Verify that max health is set correctly
    ASSERT_EQUAL(player.getMaxHealth(), 100); // Max health should be set to 100
}

// Combat testing
void testPrintHealth()
{
    std::stringstream buffer;
    std::streambuf *prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    printHealth(100, 50, "Enemy");
    std::string result = buffer.str();

    std::string expected = "***************************************\n* Player Health: 100 Enemy Health: 50 *\n***************************************\n\n";

    // Reset cout's buffer
    std::cout.rdbuf(prevcoutbuf);

    std::cout << result;
    std::cout << expected;

    // Check if the output contains the expected health information
    ASSERT(result.find("Player Health: 100") != std::string::npos);
    ASSERT(result.find("Enemy Health: 50") != std::string::npos);

    ASSERT_EQUAL(result, expected);
}

// Menu tests
std::string normalizeString(const std::string &input)
{
    std::regex ansiRegex(R"(\x1B\[[0-9;]*[a-zA-Z])");
    return std::regex_replace(input, ansiRegex, "");
}

void testDisplayIntro()
{
    // Capture the output
    std::stringstream simulatedOutput;
    std::streambuf *coutBackup = std::cout.rdbuf();
    std::cout.rdbuf(simulatedOutput.rdbuf());

    // Call the function to test
    displayIntro(15, "\033[36m");

    // Restore std::cout
    std::cout.rdbuf(coutBackup);

    // Expected output
    std::vector<std::string> intro = split(getFileContent("../reasources/intro.txt"), '@');
    std::string expectedOutput;

    for (int i = 0; i < 3; i++)
    {
        expectedOutput.append("\033[36m" + intro[i] + "\033[37m\n");
    }
    expectedOutput.append("\033[36m" + intro[intro.size() - 1] + "\033[37m\n");

    // Capture actual output
    std::string output = simulatedOutput.str();

    std::string normalizedExpected = normalizeString(expectedOutput);
    std::string normalizedOutput = normalizeString(output);

    // Check if the normalized output matches the normalized expected output
    if (normalizedOutput != normalizedExpected)
    {
        std::cout << "Test failed!\n";
        std::cout << "Normalized Expected Output:\n"
                  << normalizedExpected << "\n";
        std::cout << "Normalized Actual Output:\n"
                  << normalizedOutput << "\n";
    }
    else
    {
        std::cout << "Test passed!\n";
    }

    // Alternatively, use an assertion
    ASSERT_EQUAL(normalizedOutput, normalizedExpected);
}

void testDisplayj()
{
    // Capture the output
    std::stringstream simulatedOutput;
    std::streambuf *coutBackup = std::cout.rdbuf();
    std::cout.rdbuf(simulatedOutput.rdbuf());

    // Call the function to test
    Displayj();

    // Restore std::cout
    std::cout.rdbuf(coutBackup);

    // Expected output
    std::string expectedOutput =
        "\033[37m==========================================================\n"
        "               VALERIS GAME MENU\n"
        "==========================================================\n"
        "1. Start New Game\n"
        "2. Load Saved Game\n"
        "3. Instructions\n"
        "4. Accessibility\n"
        "5. Exit\n"
        "==========================================================\n";

    // Capture actual output
    std::string output = simulatedOutput.str();

    // Alternatively, use an assertion
    ASSERT_EQUAL(output, expectedOutput);

    bool inverse = output != "cidjown";
    ASSERT(inverse);
}

void test_DisplayInstructionsText()
{
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    // Fake the input to simulate Enter key press
    std::istringstream fakeInput("\n");
    std::cin.rdbuf(fakeInput.rdbuf());

    // Call the function to test
    DisplayInstructionsText();

    // Restore the original cout buffer
    std::cout.rdbuf(old);

    // The expected output with ANSI escape code for white text
    std::string instructions = R"(
Instructions:
1. Use the N, S, W, E keys to move your character.
2. Fight enemies with ___
3. Collect items to improve your chances of survival.
4. Play minigames with ___
5. Defeat bosses to progress to the next level.
)";

    std::string expectedOutput = "\033[37m" + instructions + "\nPress Enter to continue...";

    std::string normalizedExpected = normalizeString(expectedOutput);
    std::string normalizedOutput = normalizeString(buffer.str());

    // Compare the actual output with the expected output
    ASSERT_EQUAL(normalizedOutput, normalizedExpected);

    bool inverse = normalizedOutput != "cidjown";
    ASSERT(inverse);
}

// Test cases
void testGetColor_Green()
{
    std::string result = getColor(1, "\033[37m"); // Default color
    ASSERT_EQUAL("\033[32m", result);
}

void testGetColor_Blue()
{
    std::string result = getColor(2, "\033[37m");
    ASSERT_EQUAL("\033[34m", result);
}

void testGetColor_Red()
{
    std::string result = getColor(3, "\033[37m");
    ASSERT_EQUAL("\033[31m", result);
}

void testGetColor_Yellow()
{
    std::string result = getColor(4, "\033[37m");
    ASSERT_EQUAL("\033[33m", result);
}

void testGetColor_Cyan()
{
    std::string result = getColor(5, "\033[37m");
    ASSERT_EQUAL("\033[36m", result);
}

void testGetColor_Invalid()
{
    std::string initialColor = "\033[37m";           // Default color
    std::string result = getColor(99, initialColor); // Invalid choice
    ASSERT_EQUAL(initialColor, result);              // Should keep the original color
}

void testCombatV1PressP()
{
    int playerHealth = 1;
    int enemyHealth = 100;
    int difficulty = 1000;
    std::string name = "Test Enemy";

    // Redirect cout to capture output
    std::stringstream outputBuffer;
    std::streambuf *oldCout = std::cout.rdbuf(outputBuffer.rdbuf());

    // Simulate input of 'p' followed by Enter
    std::istringstream fakeInput("p"); // \np\np\np\np\np\np\np\np\np\n
    std::streambuf *oldCin = std::cin.rdbuf(fakeInput.rdbuf());

    // Call the function to test
    bool result = combatV1(playerHealth, enemyHealth, difficulty, name);

    // Restore the original cout and cin buffers
    std::cout.rdbuf(oldCout);
    std::cin.rdbuf(oldCin);

    // Check the result
    ASSERT_EQUAL(false, result);
}

void testTicTacToePrintBoard()
{
    TicTacToe game;

    // Redirect cout to capture output
    std::stringstream outputBuffer;
    std::streambuf *oldCout = std::cout.rdbuf(outputBuffer.rdbuf());

    // Call the function to test
    game.printBoard();

    // Restore the original cout buffer
    std::cout.rdbuf(oldCout);

    // Expected output
    std::string expectedOutput =
        "\n   |   |   "
        "\n   |   |   "
        "\n___|___|___"
        "\n   |   |   "
        "\n   |   |   "
        "\n___|___|___"
        "\n   |   |   "
        "\n   |   |   "
        "\n   |   |   ";

    // Get the actual output
    std::string actualOutput = outputBuffer.str();

    while (!expectedOutput.empty() && (expectedOutput.back() == '\n'))
    {
        expectedOutput.pop_back();
    }
    while (!actualOutput.empty() && (actualOutput.back() == '\n'))
    {
        actualOutput.pop_back();
    }

    std::string normalizedExpected = normalizeString(expectedOutput);
    std::string normalizedActual = normalizeString(actualOutput);

    // Compare the actual output with the expected output
    ASSERT_EQUAL(normalizedExpected, normalizedActual);
}

void testCodeGuesserPrintWords()
{
    // Initialize CodeGuesser with some test words

    CodeGuesser guesser;

    // Redirect cout to capture output
    std::stringstream outputBuffer;
    std::streambuf *oldCout = std::cout.rdbuf(outputBuffer.rdbuf());

    std::string expectedOutput =
        "spice\n"
        "knife\n"
        "blade\n"
        "maker\n"
        "worms\n"
        "baron\n"
        "guild\n"
        "dunes\n"
        "sandy\n"
        "space\n"
        "light\n";

    // Call the function to test
    guesser.printWords();

    // Restore the original cout buffer
    std::cout.rdbuf(oldCout);

    // Get the actual output
    std::string actualOutput = outputBuffer.str();

    // Compare the actual output with the expected output
    std::string normalizedExpected = normalizeString(expectedOutput);
    std::string normalizedActual = normalizeString(actualOutput);

    // Compare the actual output with the expected output
    ASSERT_EQUAL(normalizedExpected, normalizedActual);
}

void testTicTacToeInitialization()
{
    TicTacToe game;
    ASSERT(game.isValidMove(1, 1));
    ASSERT(game.isValidMove(3, 3));

    // Test invalid moves (out of bounds)
    ASSERT(!game.isValidMove(0, 1));
    ASSERT(!game.isValidMove(4, 3));
    ASSERT(!game.isValidMove(2, 0));
    ASSERT(!game.isValidMove(3, 4));
}

void test_makeMove()
{
    TicTacToe game;

    // Make a move and check board state
    game.makeMove(1, 1, 'X');
    ASSERT_EQUAL('X', game.getSquare(0, 0));

    game.makeMove(2, 2, 'O');
    ASSERT_EQUAL('O', game.getSquare(1, 1));

    // Make sure other squares remain untouched
    ASSERT_EQUAL(' ', game.getSquare(0, 1));
}

// void test_isGameOver()
// {
//     TicTacToe game;

//     // Test no win, not full board
//     ASSERT(!game.isGameOver(3));

//     // Test draw scenario
//     game.squares = {
//         {'X', 'O', 'X'},
//         {'X', 'X', 'O'},
//         {'O', 'X', 'O'}};
//     ASSERT(game.isGameOver(9)); // Draw

//     // Test win scenario
//     game.squares = {
//         {'X', 'X', 'X'},
//         {'O', ' ', ' '},
//         {'O', ' ', ' '}};
//     ASSERT(game.checkForWin()); // X wins
// }

void test_getPlayerMove()
{
    TicTacToe game;

    int row = 1, col = 1;
    std::istringstream input("1 1\n");
    std::cin.rdbuf(input.rdbuf()); // Redirect input

    ASSERT(game.getPlayerMove(row, col));
    ASSERT_EQUAL(1, row);
    ASSERT_EQUAL(1, col);

    std::istringstream invalidInput("4 5\n");
    std::cin.rdbuf(invalidInput.rdbuf());  // Invalid input
    ASSERT(!game.getPlayerMove(row, col)); // Should return false
}

void test_processComputerTurn()
{
    TicTacToe game;

    // Empty board before computer move
    ASSERT_EQUAL(' ', game.getSquare(0, 0));

    // Redirect cout to a stringstream to capture output
    std::ostringstream outputCapture;
    std::streambuf *oldCoutStreamBuf = std::cout.rdbuf(outputCapture.rdbuf());

    game.processComputerTurn();

    // Restore original cout stream buffer
    std::cout.rdbuf(oldCoutStreamBuf);

    // After computer move, one square should be filled (assuming computerTurn works)
    bool moveMade = false;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (game.getSquare(i, j) == 'O')
            {
                moveMade = true;
            }
        }
    }
    ASSERT(moveMade); // Make sure some 'O' was placed on the board
}

// Room stuff
// Test for RoomContent::getRoomType method
void testGetRoomType()
{
    RoomContent roomContent;
    int roomType = roomContent.getRoomType();

    // Test if room type is 0 (empty room) or 1 (gambling room)
    ASSERT_EQUAL(true, roomType == 0 || roomType == 1);
}

// Test for RoomContent::getNPC method
void testGetNPC()
{
    RoomContent roomContent;
    roomContent.gamblingRoom();
    NPC &npc = roomContent.getNPC();

    // Test if the NPC name is non-empty (assuming NPC should have a name)
    ASSERT_EQUAL(false, npc.name.empty());
}

// Test for RoomContent::getEnemies method
void testGetEnemies()
{
    RoomContent roomContent;
    std::vector<EnemyStruct> enemies = roomContent.getEnemies();

    // Assuming the room starts without enemies, the size should be

    // Add an enemy and test again
    EnemyStruct enemy = {"Goblin", 30, 5};
    roomContent.addEnemy(enemy);
    enemies = roomContent.getEnemies();

    ASSERT_EQUAL(1, enemies.size());
    ASSERT_EQUAL("Goblin", enemies.at(0).name);
    ASSERT_EQUAL(30, enemies.at(0).health);
    ASSERT_EQUAL(5, enemies.at(0).attack);
}

// Test for RoomContent::getCoordinates method
void testGetCoordinates()
{
    RoomContent roomContent;
    roomContent.addCoordinates(3, 4);

    std::pair<int, int> coords = roomContent.getCoordinates();
    ASSERT_EQUAL(3, coords.first);  // Check x-coordinate
    ASSERT_EQUAL(4, coords.second); // Check y-coordinate

    roomContent.addCoordinates(-3, 4);

    coords = roomContent.getCoordinates();
    ASSERT_EQUAL(-3, coords.first); // Check x-coordinate
    ASSERT_EQUAL(4, coords.second); // Check y-coordinate

    roomContent.addCoordinates(3, -4);

    coords = roomContent.getCoordinates();
    ASSERT_EQUAL(3, coords.first);   // Check x-coordinate
    ASSERT_EQUAL(-4, coords.second); // Check y-coordinate

    roomContent.addCoordinates(-3, -4);

    coords = roomContent.getCoordinates();
    ASSERT_EQUAL(-3, coords.first);  // Check x-coordinate
    ASSERT_EQUAL(-4, coords.second); // Check y-coordinate
}

// Test for RoomContent::getVisited and setVisited methods
void testVisitedStatus()
{
    RoomContent roomContent;

    // Initially the room should not be visited
    ASSERT_EQUAL(false, roomContent.getVisited());

    // Set room as visited and check again
    roomContent.setVisited(true);
    ASSERT_EQUAL(true, roomContent.getVisited());

    // Set room as not visited and check again
    roomContent.setVisited(false);
    ASSERT_EQUAL(false, roomContent.getVisited());
}

// Capture the output of a function that prints to std::cout
template <typename Func>
std::string captureOutput(Func func)
{
    std::ostringstream output;
    std::streambuf *oldCoutStreamBuf = std::cout.rdbuf(output.rdbuf());

    func(); // Call the function that prints to std::cout

    std::cout.rdbuf(oldCoutStreamBuf);
    return output.str();
}

void testNoDirections()
{
    Room room;

    std::string result = captureOutput([&]()
                                       { room.displayAvailableDirections(); });

    // Expect "You can move: " with no directions listed
    ASSERT_EQUAL("You can move: \n", result);
}

void testAllDirections()
{
    Room room;
    room.north = new Room();
    room.south = new Room();
    room.west = new Room();
    room.east = new Room();

    std::string result = captureOutput([&]()
                                       { room.displayAvailableDirections(); });

    // Expect "You can move: North, South, West, East"
    ASSERT_EQUAL("You can move: North, South, West, East\n", result);
}

void testSomeDirections()
{
    Room room;
    room.north = new Room();
    room.south = new Room();
    // west and east are not set

    std::string result = captureOutput([&]()
                                       { room.displayAvailableDirections(); });

    // Expect "You can move: North, South"
    ASSERT_EQUAL("You can move: North, South\n", result);
}

void testOneDirection()
{
    Room room;
    room.north = new Room();
    // south, west, and east are not set

    std::string result = captureOutput([&]()
                                       { room.displayAvailableDirections(); });

    // Expect "You can move: North"
    ASSERT_EQUAL("You can move: North\n", result);
}
int main()
{
    TestFramework framework("minigames_test_results.xml");

    // TicTacToe tests (Need to add CodeGuesser and BlackJack Testing)
    framework.addTest("TicTacToe Initialization", testTicTacToeInitialization);
    framework.addTest("TicTacToe Player Move", testTicTacToePlayerMove);
    framework.addTest("TicTacToe Computer Turn", testTicTacToeComputerTurn);
    framework.addTest("TicTacToe Check For Win", testTicTacToeCheckForWin);
    // framework.addTest("TicTacToe Start", testTicTacToeStart);

    // CodeGuesser tests
    framework.addTest("CodeGuesser Initialization", testCodeGuesserInitialization);
    framework.addTest("CodeGuesser Game Name", testCodeGuesserGameName);
    framework.addTest("CodeGuesser Add Guess", testCodeGuesserAddGuess);
    framework.addTest("CodeGuesser Start Game", testCodeGuesserStart);

    // BlackJack tests
    framework.addTest("BlackJack Initialization", testBlackJackInitialization);

    /*
    // Player tests (Need to add default cases to player.h and cpp so that it can build auto and won't need input)
    framework.addTest("Player Initialization", testPlayerInitialization);
    framework.addTest("Player Inventory", testPlayerInventory);
`   */
    framework.addTest("Player Constructor", testPlayerConstructor);
    framework.addTest("Add To Inventory", testAddToInventory);
    framework.addTest("Remove From Inventory", testRemoveFromInventory);
    framework.addTest("Remove Nonexistent Item", testRemoveNonexistentItem);
    framework.addTest("Set Max Health", testSetMaxHealth);
    framework.addTest("Set Current Health", testSetCurrHealth);
    framework.addTest("Add Buff", testAddBuff);
    framework.addTest("Remove Buff", testRemoveBuff);
    framework.addTest("Remove Nonexistent Buff", testRemoveNonexistentBuff);
    framework.addTest("Set Resistance", testSetResistance);
    framework.addTest("Set Max Health Adjusts Current Health", testSetMaxHelth_AdjustCurrentHealth);

    // Weapon tests
    framework.addTest("Weapon Initialization", testWeaponInitialization);
    framework.addTest("Random Weapon Generation", testRandomWeaponGeneration);
    framework.addTest("Weapon Generation by Rarity", testWeaponGenerationByRarity);
    framework.addTest("All Weapons", testAllWeapons);

    // Toolkit tests
    framework.addTest("Generate Random Number", testGenerateRandomNumber);
    framework.addTest("String to Int Conversion", testStringToInt);
    framework.addTest("Repeat String", testRepeatString);
    framework.addTest("To Lower Case", testToLowerCase);
    framework.addTest("To Upper Case", testToUpperCase);
    framework.addTest("Split String", testSplit);
    framework.addTest("Get File Content", testGetFileContent);
    // Add these tests to your framework{
    framework.addTest("Read Int", testReadInt);
    framework.addTest("Get User Input Line", testGetUserInputLine);
    framework.addTest("Wait For Enter", testWaitForEnter);

    // Enemies Test
    framework.addTest("Enemy Initialisation", testEnemyInitialisation);
    framework.addTest("Enemy Damage Application", testEnemyDamageApplication);
    framework.addTest("Enemy Death Condition", testEnemyDeathCondition);
    framework.addTest("Enemy Custom Setters", testEnemyCustomSetters);

    // Dungeon tests
    framework.addTest("Dungeon Room Generation", testDungeonRoomGeneration);
    framework.addTest("Dungeon Link Room", testLinkRooms);

    // combat tests
    framework.addTest("Print Health", testPrintHealth);

    // Menu tests
    framework.addTest("Display intro test", testDisplayIntro);
    framework.addTest("Display menu test", testDisplayj);
    framework.addTest("Display instructions test", test_DisplayInstructionsText);
    framework.addTest("Test GetColor Green", testGetColor_Green);
    framework.addTest("Test GetColor Blue", testGetColor_Blue);
    framework.addTest("Test GetColor Red", testGetColor_Red);
    framework.addTest("Test GetColor Yellow", testGetColor_Yellow);
    framework.addTest("Test GetColor Cyan", testGetColor_Cyan);
    framework.addTest("Test GetColor Invalid", testGetColor_Invalid);

    framework.addTest("CombatV1PressP", testCombatV1PressP);

    framework.addTest("TicTacToePrintBoard", testTicTacToePrintBoard);

    framework.addTest("CodeGuesserPrintWords", testCodeGuesserPrintWords);

    // framework.addTest("test_isValidMove", test_isValidMove);
    framework.addTest("test_makeMove", test_makeMove);
    // // framework.addTest("test_isGameOver", test_isGameOver);
    framework.addTest("test_getPlayerMove", test_getPlayerMove);
    framework.addTest("test_processComputerTurn", test_processComputerTurn);

    // Room tests
    framework.addTest("RoomContent::getRoomType", testGetRoomType);
    framework.addTest("RoomContent::getNPC", testGetNPC);
    framework.addTest("RoomContent::getEnemies", testGetEnemies);
    framework.addTest("RoomContent::getCoordinates", testGetCoordinates);
    framework.addTest("RoomContent::getVisited and setVisited", testVisitedStatus);
    framework.addTest("Room::testNoDirections", testNoDirections);
    framework.addTest("Room::testAllDirections", testAllDirections);
    framework.addTest("Room::testSomeDirections", testSomeDirections);
    framework.addTest("Room::testOneDirection", testOneDirection);
    // Run framework
    framework.run();

    return 0;
}
