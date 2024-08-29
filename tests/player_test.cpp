// #include "../helper/minigames.cpp"
#include "../lib/player.h"
#include "custom_test_framework.h"

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