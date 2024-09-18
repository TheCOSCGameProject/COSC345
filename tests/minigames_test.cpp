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

#include "custom_test_framework.h"
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
/*
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
*/
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

void testWeaponInitialization()
{
    Weapon weaponSystem;

    // Test case for Weapon 1: Plasma Rifle
    ASSERT_EQUAL("Plasma Rifle", weaponSystem.getName(1));
    ASSERT_EQUAL("A high-energy weapon that fires concentrated plasma bolts.", weaponSystem.getDescription(1));
    ASSERT_EQUAL(45, weaponSystem.getDamage(1));
    ASSERT_EQUAL("Rare", weaponSystem.getRarity(1));
    ASSERT(weaponSystem.getRanged(1));
    ASSERT(!weaponSystem.getStun(1));

    // Test case for Weapon 2: Laser Pistol
    ASSERT_EQUAL("Laser Pistol", weaponSystem.getName(2));
    ASSERT_EQUAL("A compact, high-precision laser pistol ideal for close combat.", weaponSystem.getDescription(2));
    ASSERT_EQUAL(25, weaponSystem.getDamage(2));
    ASSERT_EQUAL("Common", weaponSystem.getRarity(2));
    ASSERT(weaponSystem.getRanged(2));
    ASSERT(!weaponSystem.getStun(2));

    // Test case for Weapon 3: Icicle
    ASSERT_EQUAL("Icicle", weaponSystem.getName(3));
    ASSERT_EQUAL("A grenade that releases a freezing gas upon hit, freezing enemies.", weaponSystem.getDescription(3));
    ASSERT_EQUAL(35, weaponSystem.getDamage(3));
    ASSERT_EQUAL("Uncommon", weaponSystem.getRarity(3));
    ASSERT(!weaponSystem.getRanged(3));
    ASSERT(weaponSystem.getStun(3));

    // Test case for Weapon 4: Sonic Blaster
    ASSERT_EQUAL("Sonic Blaster", weaponSystem.getName(4));
    ASSERT_EQUAL("Emits sound waves capable of shattering solid objects.", weaponSystem.getDescription(4));
    ASSERT_EQUAL(40, weaponSystem.getDamage(4));
    ASSERT_EQUAL("Rare", weaponSystem.getRarity(4));
    ASSERT(weaponSystem.getRanged(4));
    ASSERT(weaponSystem.getStun(4));

    // Test case for Weapon 5: Electro Blade
    ASSERT_EQUAL("Electro Blade", weaponSystem.getName(5));
    ASSERT_EQUAL("A sword infused with electrical energy, delivering a shock with each strike.", weaponSystem.getDescription(5));
    ASSERT_EQUAL(30, weaponSystem.getDamage(5));
    ASSERT_EQUAL("Uncommon", weaponSystem.getRarity(5));
    ASSERT(!weaponSystem.getRanged(5));
    ASSERT(weaponSystem.getStun(5));

    // Test case for Weapon 6: Ion Cannon
    ASSERT_EQUAL("Ion Cannon", weaponSystem.getName(6));
    ASSERT_EQUAL("A heavy-duty weapon that fires a massive ion beam, effective against armored targets.", weaponSystem.getDescription(6));
    ASSERT_EQUAL(60, weaponSystem.getDamage(6));
    ASSERT_EQUAL("Epic", weaponSystem.getRarity(6));
    ASSERT(weaponSystem.getRanged(6));
    ASSERT(weaponSystem.getStun(6));

    // Test case for Weapon 7: Pulse Rifle
    ASSERT_EQUAL("Pulse Rifle", weaponSystem.getName(7));
    ASSERT_EQUAL("Fires rapid bursts of energy pulses, excellent for crowd control.", weaponSystem.getDescription(7));
    ASSERT_EQUAL(38, weaponSystem.getDamage(7));
    ASSERT_EQUAL("Common", weaponSystem.getRarity(7));
    ASSERT(weaponSystem.getRanged(7));
    ASSERT(weaponSystem.getStun(7));

    // Test case for Weapon 8: Nano Sword
    ASSERT_EQUAL("Nano Sword", weaponSystem.getName(8));
    ASSERT_EQUAL("A blade composed of nanobots, able to cut through virtually anything.", weaponSystem.getDescription(8));
    ASSERT_EQUAL(50, weaponSystem.getDamage(8));
    ASSERT_EQUAL("Epic", weaponSystem.getRarity(8));
    ASSERT(!weaponSystem.getRanged(8));
    ASSERT(!weaponSystem.getStun(8));

    // Test case for Weapon 9: Graviton Hammer
    ASSERT_EQUAL("Graviton Hammer", weaponSystem.getName(9));
    ASSERT_EQUAL("A weapon that manipulates gravity to deliver devastating blows.", weaponSystem.getDescription(9));
    ASSERT_EQUAL(55, weaponSystem.getDamage(9));
    ASSERT_EQUAL("Legendary", weaponSystem.getRarity(9));
    ASSERT(!weaponSystem.getRanged(9));
    ASSERT(weaponSystem.getStun(9));

    // Test case for Weapon 10: Neutron Bomb
    ASSERT_EQUAL("Neutron Bomb", weaponSystem.getName(10));
    ASSERT_EQUAL("A bomb that releases neutron radiation, lethal to organic life.", weaponSystem.getDescription(10));
    ASSERT_EQUAL(100, weaponSystem.getDamage(10));
    ASSERT_EQUAL("Legendary", weaponSystem.getRarity(10));
    ASSERT(weaponSystem.getRanged(10));
    ASSERT(!weaponSystem.getStun(10));

    // Test case for Weapon 11: Crysknife
    ASSERT_EQUAL("Crysknife", weaponSystem.getName(11));
    ASSERT_EQUAL("A sacred knife made from the tooth of a sandworm. Deadly in close combat.", weaponSystem.getDescription(11));
    ASSERT_EQUAL(50, weaponSystem.getDamage(11));
    ASSERT_EQUAL("Rare", weaponSystem.getRarity(11));
    ASSERT(!weaponSystem.getRanged(11));
    ASSERT(!weaponSystem.getStun(11));

    // Test case for Weapon 12: Maula Pistol
    ASSERT_EQUAL("Maula Pistol", weaponSystem.getName(12));
    ASSERT_EQUAL("A small, easily concealable projectile weapon used by assassins.", weaponSystem.getDescription(12));
    ASSERT_EQUAL(25, weaponSystem.getDamage(12));
    ASSERT_EQUAL("Common", weaponSystem.getRarity(12));
    ASSERT(!weaponSystem.getRanged(12));
    ASSERT(!weaponSystem.getStun(12));

    // Test case for Weapon 13: Lasgun
    ASSERT_EQUAL("Lasgun", weaponSystem.getName(13));
    ASSERT_EQUAL("A powerful beam weapon capable of cutting through almost any material.", weaponSystem.getDescription(13));
    ASSERT_EQUAL(60, weaponSystem.getDamage(13));
    ASSERT_EQUAL("Uncommon", weaponSystem.getRarity(13));
    ASSERT(!weaponSystem.getRanged(13));
    ASSERT(!weaponSystem.getStun(13));

    // Test case for Weapon 14: Spice Grenade
    ASSERT_EQUAL("Spice Grenade", weaponSystem.getName(14));
    ASSERT_EQUAL("An explosive that disperses spice particles, causing hallucinations and disorientation.", weaponSystem.getDescription(14));
    ASSERT_EQUAL(50, weaponSystem.getDamage(14));
    ASSERT_EQUAL("Epic", weaponSystem.getRarity(14));
    ASSERT(weaponSystem.getRanged(14));
    ASSERT(weaponSystem.getStun(14));

    // Test case for Weapon 15: Gom Jabbar
    ASSERT_EQUAL("Gom Jabbar", weaponSystem.getName(15));
    ASSERT_EQUAL("A needle-like weapon that delivers a lethal poison. Used in specific assassination rituals.", weaponSystem.getDescription(15));
    ASSERT_EQUAL(100, weaponSystem.getDamage(15));
    ASSERT_EQUAL("Legendary", weaponSystem.getRarity(15));
    ASSERT(!weaponSystem.getRanged(15));
    ASSERT(!weaponSystem.getStun(15));

    // Test case for Weapon 16: Hunter-Seeker
    ASSERT_EQUAL("Hunter-Seeker", weaponSystem.getName(16));
    ASSERT_EQUAL("A remote-controlled assassination device that seeks out its target with precision.", weaponSystem.getDescription(16));
    ASSERT_EQUAL(45, weaponSystem.getDamage(16));
    ASSERT_EQUAL("Epic", weaponSystem.getRarity(16));
    ASSERT(weaponSystem.getRanged(16));
    ASSERT(!weaponSystem.getStun(16));

    // Test case for Weapon 17: Stunner
    ASSERT_EQUAL("Stunner", weaponSystem.getName(17));
    ASSERT_EQUAL("A non-lethal weapon used to incapacitate enemies, commonly used by law enforcement.", weaponSystem.getDescription(17));
    ASSERT_EQUAL(20, weaponSystem.getDamage(17));
    ASSERT_EQUAL("Common", weaponSystem.getRarity(17));
    ASSERT(!weaponSystem.getRanged(17));
    ASSERT(weaponSystem.getStun(17));

    // Test case for Weapon 18: Spice-Enhanced Blade
    ASSERT_EQUAL("Spice-Enhanced Blade", weaponSystem.getName(18));
    ASSERT_EQUAL("A blade tempered with the essence of spice, increasing its sharpness and durability.", weaponSystem.getDescription(18));
    ASSERT_EQUAL(55, weaponSystem.getDamage(18));
    ASSERT_EQUAL("Epic", weaponSystem.getRarity(18));
    ASSERT(!weaponSystem.getRanged(18));
    ASSERT(weaponSystem.getStun(18));

    // Test case for Weapon 19: Shai-Hulud's Tooth
    ASSERT_EQUAL("Shai-Hulud's Tooth", weaponSystem.getName(19));
    ASSERT_EQUAL("A weapon made from a sandworm tooth, infused with the power of the desert.", weaponSystem.getDescription(19));
    ASSERT_EQUAL(70, weaponSystem.getDamage(19));
    ASSERT_EQUAL("Legendary", weaponSystem.getRarity(19));
    ASSERT(!weaponSystem.getRanged(19));
    ASSERT(!weaponSystem.getStun(19));

    // Test case for Weapon 20: Weirding Module
    ASSERT_EQUAL("Weirding Module", weaponSystem.getName(20));
    ASSERT_EQUAL("A sound-based weapon that amplifies the voice of its user to deliver devastating sonic attacks.", weaponSystem.getDescription(20));
    ASSERT_EQUAL(70, weaponSystem.getDamage(20));
    ASSERT_EQUAL("Legendary", weaponSystem.getRarity(20));
    ASSERT(weaponSystem.getRanged(20));
    ASSERT(weaponSystem.getStun(20));

    // Test case for Weapon 21: Sand Compactor
    ASSERT_EQUAL("Sand Compactor", weaponSystem.getName(21));
    ASSERT_EQUAL("A tool-turned-weapon that uses compressed sand to create projectiles.", weaponSystem.getDescription(21));
    ASSERT_EQUAL(30, weaponSystem.getDamage(21));
    ASSERT_EQUAL("Uncommon", weaponSystem.getRarity(21));
    ASSERT(weaponSystem.getRanged(21));
    ASSERT(!weaponSystem.getStun(21));

    // Test case for Weapon 22: Fremen Hook
    ASSERT_EQUAL("Fremen Hook", weaponSystem.getName(22));
    ASSERT_EQUAL("A specialized tool used by the Fremen to ride sandworms, can also be used as a weapon.", weaponSystem.getDescription(22));
    ASSERT_EQUAL(40, weaponSystem.getDamage(22));
    ASSERT_EQUAL("Rare", weaponSystem.getRarity(22));
    ASSERT(!weaponSystem.getRanged(22));
    ASSERT(weaponSystem.getStun(22));

    // Test case for Weapon 23: Injector Dart
    ASSERT_EQUAL("Injector Dart", weaponSystem.getName(23));
    ASSERT_EQUAL("A small dart that can deliver a variety of substances, from tranquilizers to lethal toxins.", weaponSystem.getDescription(23));
    ASSERT_EQUAL(35, weaponSystem.getDamage(23));
    ASSERT_EQUAL("Uncommon", weaponSystem.getRarity(23));
    ASSERT(weaponSystem.getRanged(23));
    ASSERT(weaponSystem.getStun(23));

    // Test case for Weapon 24: Spice Harvester's Wrench
    ASSERT_EQUAL("Spice Harvester's Wrench", weaponSystem.getName(24));
    ASSERT_EQUAL("A large, heavy tool used in spice harvesting, repurposed as a weapon.", weaponSystem.getDescription(24));
    ASSERT_EQUAL(45, weaponSystem.getDamage(24));
    ASSERT_EQUAL("Common", weaponSystem.getRarity(24));
    ASSERT(weaponSystem.getRanged(24));
    ASSERT(!weaponSystem.getStun(24));

    // Test case for Weapon 25: Glowglobe Bomb
    ASSERT_EQUAL("Glowglobe Bomb", weaponSystem.getName(25));
    ASSERT_EQUAL("A light-emitting device that can be overloaded to explode, blinding enemies temporarily.", weaponSystem.getDescription(25));
    ASSERT_EQUAL(20, weaponSystem.getDamage(25));
    ASSERT_EQUAL("Uncommon", weaponSystem.getRarity(25));
    ASSERT(weaponSystem.getRanged(25));
    ASSERT(weaponSystem.getStun(25));

    // Test case for Weapon 26: Stilgar's Blade
    ASSERT_EQUAL("Stilgar's Blade", weaponSystem.getName(26));
    ASSERT_EQUAL("A unique knife belonging to the legendary Fremen leader Stilgar, revered for its history.", weaponSystem.getDescription(26));
    ASSERT_EQUAL(55, weaponSystem.getDamage(26));
    ASSERT_EQUAL("Epic", weaponSystem.getRarity(26));
    ASSERT(!weaponSystem.getRanged(26));
    ASSERT(!weaponSystem.getStun(26));

    // Test case for Weapon 27: Sardaukar Blade
    ASSERT_EQUAL("Sardaukar Blade", weaponSystem.getName(27));
    ASSERT_EQUAL("A razor-sharp sword used by the elite Sardaukar troops, feared across the galaxy.", weaponSystem.getDescription(27));
    ASSERT_EQUAL(65, weaponSystem.getDamage(27));
    ASSERT_EQUAL("Rare", weaponSystem.getRarity(27));
    ASSERT(!weaponSystem.getRanged(27));
    ASSERT(!weaponSystem.getStun(27));
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

    // Reset cout's buffer
    std::cout.rdbuf(prevcoutbuf);

    // Check if the output contains the expected health information
    ASSERT(result.find("Player Health: 100") != std::string::npos);
    ASSERT(result.find("Enemy Health: 50") != std::string::npos);
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
    std::string expectedOutput = "\033[37m\nInstructions:\n1. Use the N, S, W, E keys to move your character.\n2. Fight enemies with ___\n3. Collect items to improve your chances of survival.\n4. Play minigames with ___\n5. Defeat bosses to progress to the next level.\n\n\033[0mPress Enter to continue...\n";

    std::string normalizedExpected = normalizeString(expectedOutput);
    std::string normalizedOutput = normalizeString(buffer.str());

    // Compare the actual output with the expected output
    ASSERT_EQUAL(normalizedOutput, normalizedExpected);
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
    //framework.addTest("Display instructions test", test_DisplayInstructionsText);
    framework.addTest("Test GetColor Green", testGetColor_Green);
    framework.addTest("Test GetColor Blue", testGetColor_Blue);
    framework.addTest("Test GetColor Red", testGetColor_Red);
    framework.addTest("Test GetColor Yellow", testGetColor_Yellow);
    framework.addTest("Test GetColor Cyan", testGetColor_Cyan);
    framework.addTest("Test GetColor Invalid", testGetColor_Invalid);

    // Run framework
    framework.run();

    return 0;
}
