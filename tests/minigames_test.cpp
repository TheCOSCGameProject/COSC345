#include "../lib/minigames.h"
#include "../lib/combat.h"
#include "../lib/dungeon.h"
#include "../lib/player.h"
#include "../lib/room.h"
#include "../lib/toolkit.h"
#include "../lib/weapon.h"
#include "../lib/enemies.h"

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

void testCodeGuesserInitialization()
{
    CodeGuesser game;
    ASSERT_EQUAL(5, game.getWordLength());
    ASSERT_EQUAL(0, game.getGuessCount());
    ASSERT_EQUAL("", game.getLastGuess());
}

void testCodeGuesserAddGuess()
{
    CodeGuesser game;
    int initialGuessCount = game.getGuessCount();
    game.addGuess();
    ASSERT_EQUAL(initialGuessCount + 1, game.getGuessCount());
    ASSERT(game.getLastGuess() != "");
}

void testCodeGuesserGameName()
{
    CodeGuesser game;
    ASSERT_EQUAL("Code Guesser", game.getGameName());
}

// BlackJack tests
void testBlackJackInitialization()
{
    BlackJack game;
    ASSERT_EQUAL("Black Jack", game.getGameName());
}

/* These two are currently set up for input, can easily change the player.h and cpp to have a default case but for now is fine as is. Leave commented out when syncing/pushing so build doesn't fail
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

void testWeaponInitialization()
{
    Weapon weaponSystem;
    ASSERT_EQUAL("Plasma Rifle", weaponSystem.getName(1));
    ASSERT_EQUAL("A high-energy weapon that fires concentrated plasma bolts.", weaponSystem.getDescription(1));
    ASSERT_EQUAL(45, weaponSystem.getDamage(1));
    ASSERT_EQUAL("Rare", weaponSystem.getRarity(1));
    ASSERT(weaponSystem.getRanged(1));
    ASSERT(!weaponSystem.getStun(1));
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
    // Simulate input for name
    std::stringstream simulatedInput("Alice\nWarrior\nFrank\nToolSmith");
    std::stringstream simulatedOutput;

    // Redirect std::cin and std::cout
    std::streambuf *cinBackup = std::cin.rdbuf();
    std::streambuf *coutBackup = std::cout.rdbuf();

    std::cin.rdbuf(simulatedInput.rdbuf());
    std::cout.rdbuf(simulatedOutput.rdbuf());

    // Create Player object and call getNameFromUser
    Player player;

    ASSERT_EQUAL(player.getName(), "Alice");
    ASSERT_EQUAL(player.getClassType(), "Warrior");
    ASSERT_EQUAL(player.getMaxHealth(), 100);
    ASSERT_EQUAL(player.getCurrHealth(), 100);

    player.getNameFromUser();
    player.getClassFromUser();

    // Restore std::cin and std::cout
    std::cin.rdbuf(cinBackup);
    std::cout.rdbuf(coutBackup);

    // Validate that the player name was correctly set
    ASSERT_EQUAL(player.getName(), "Frank");
    ASSERT_EQUAL(player.getClassType(), "ToolSmith");
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
// Combat testing
void testPrintHealth()
{
    std::stringstream buffer;
    std::streambuf *prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    printHealth(100, 50, "Enemy");
    std::string result = buffer.str();

    // Reset cout's buffer
    std::cout.rdbuf(prevcoutbuf);

    // Check if the output contains the expected health information
    ASSERT(result.find("Player Health: 100") != std::string::npos);
    ASSERT(result.find("Enemy Health: 50") != std::string::npos);
}

int main()
{
    TestFramework framework("minigames_test_results.xml");

    // TicTacToe tests (Need to add CodeGuesser and BlackJack Testing)
    framework.addTest("TicTacToe Initialization", testTicTacToeInitialization);
    framework.addTest("TicTacToe Player Move", testTicTacToePlayerMove);
    framework.addTest("TicTacToe Computer Turn", testTicTacToeComputerTurn);
    framework.addTest("TicTacToe Check For Win", testTicTacToeCheckForWin);

    // CodeGuesser tests
    framework.addTest("CodeGuesser Initialization", testCodeGuesserInitialization);
    // framework.addTest("CodeGuesser Add Guess", testCodeGuesserAddGuess); need to have not input based.
    framework.addTest("CodeGuesser Game Name", testCodeGuesserGameName);

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

    // Weapon tests
    framework.addTest("Weapon Initialization", testWeaponInitialization);
    framework.addTest("Random Weapon Generation", testRandomWeaponGeneration);
    framework.addTest("Weapon Generation by Rarity", testWeaponGenerationByRarity);

    // Toolkit tests
    framework.addTest("Generate Random Number", testGenerateRandomNumber);
    framework.addTest("String to Int Conversion", testStringToInt);
    framework.addTest("Repeat String", testRepeatString);
    framework.addTest("To Lower Case", testToLowerCase);
    framework.addTest("To Upper Case", testToUpperCase);
    framework.addTest("Split String", testSplit);
    framework.addTest("Get File Content", testGetFileContent);

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

    // Run framework
    framework.run();

    return 0;
}
