/*!
@file combat.cpp
@brief Implementation of combat functions for the game.
@details This file contains two versions of combat systems used in the game. The first version involves quick reflexes to match directional inputs, while the second version is a placeholder for a more strategic combat system.
*/

#include "../lib/dependencies.h"
#include "../lib/combat.h"
#include "../lib/toolkit.h"

/*!
@brief Print the current health status of the player and enemy.
@param playerHealth The current health of the player.
@param enemyHealth The current health of the enemy.
@param name The name of the enemy.
@details This function prints the player's and enemy's health in a formatted health bar.
*/
void printHealth(int playerHealth, int enemyHealth, const std::string &name)
{
    // Prepare the health bar string
    std::string healthBars = "* Player Health: " + std::to_string(playerHealth) + " " + name + " Health: " + std::to_string(enemyHealth) + " *";

    // Create a width string of '*' matching the length of healthBars
    std::string width = "";
    for (int i = 0; i < healthBars.length(); i++)
    {
        width += "*";
    }

    // Print the health bar surrounded by asterisks
    std::cout << width + "\n"
              << healthBars << "\n" + width + "\n"
              << std::endl;
}

/*!
@brief First version of the combat system.
@param playerHealth The initial health of the player.
@param enemyHealth The initial health of the enemy.
@param difficulty The difficulty level of the combat, influencing the response time allowed.
@param name The name of the enemy G.
@return True if the player wins, false if the player loses.
@details This combat system involves the player quickly matching directional inputs to attack the enemy. The enemy's attacks decrease the player's health if the player fails to respond correctly or quickly enough.
*/
bool combatV1(int playerHealth, int enemyHealth, int difficulty, const std::string &name)
{
    // Define directional moves and their keyboard equivalents
    const std::string moves[] = {"A", "W", "D", "S"};
    const std::string keyBoardEquivalent[] = {"a", "w", "d", "s"};
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed for randomness
    printHealth(playerHealth, enemyHealth, name);
    // Combat loop: continue while both player and enemy have health
    while (playerHealth > 0 && enemyHealth > 0)
    {
        int random_number = std::rand() % 4;                      // Select a random direction
        std::cout << moves[random_number] + "    " << std::flush; // Display the move symbol

        auto start = std::chrono::high_resolution_clock::now(); // Start timer for user input
        std::string inputStr;

        std::getline(std::cin, inputStr);                     // Get user input
        auto now = std::chrono::high_resolution_clock::now(); // Capture current time
        std::chrono::duration<double> elapsed = now - start;  // Calculate elapsed time

        // Check if user input matches and is within the allowed time
        if (inputStr == keyBoardEquivalent[random_number] && elapsed.count() < difficulty / 1000.0)
        {
            enemyHealth -= 5; // Successful hit on the enemy
            clear(5);
            printHealth(playerHealth, enemyHealth, name);
        }
        else if (elapsed.count() >= difficulty / 1000.0)
        {
            playerHealth -= 10; // Player takes damage due to slow response
            clear(5);
            printHealth(playerHealth, enemyHealth, name);
        }
        else
        {
            playerHealth -= 5; // Incorrect input results in minor damage
            clear(5);
            printHealth(playerHealth, enemyHealth, name);
        }
    }

    // Print win or lose message based on remaining health
    if (playerHealth > 0)
    {
        std::cout << "You Win!" << std::endl;
        delay(3000);
        return true;
    }
    else
    {
        std::cout << "You Lose!" << std::endl;
        delay(3000);
        return false;
    }
}

// LCOV_EXCL_START
/*!
@brief Placeholder for the second version of the combat system.
@param playerHealth The initial health of the player.
@param enemyHealth The initial health of the enemy.
@details This version of the combat system is intended to be more strategic, allowing the player to choose different combat styles (Offensive, Sneaky, Defensive). The implementation details are yet to be completed.
*/
void combatV2(int playerHealth, int enemyHealth)
{
    // Define combat types: Offensive, Sneaky, Defensive
    const char combatType[] = {'o', 'd', 's'};
    const std::string options[] = {"Offensive", "Sneaky", "Defensive"};
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed for randomness
    int random_number = std::rand() % 3;                       // Randomly choose an enemy attack type

    // Combat loop: continue while both player and enemy have health
    while (playerHealth > 0 && enemyHealth > 0)
    {
        std::cout << "Please select an attack type";
        // Further implementation for player choices and combat resolution needed here
    }
}
// LCOV_EXCL_STOP