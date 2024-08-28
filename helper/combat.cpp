#include "../lib/dependencies.h"
#include "../lib/combat.h"

/**
 * @brief Prints the current health of both the player and the enemy.
 * @param playerHealth The current health of the player.
 * @param enemyHealth The current health of the enemy.
 */
void printHealth(int playerHealth, int enemyHealth)
{
    // Clear the previous health display (5 lines up)
    for (int i = 0; i < 5; i++)
    {
        std::cout << "\033[A\033[K";
    }

    // Prepare the health bar string
    std::string healthBars = "* Player Health: " + std::to_string(playerHealth) + "  Enemy Health: " + std::to_string(enemyHealth) + " *";
    
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

/**
 * @brief Implements the first version of combat mechanics with directional input.
 * @param playerHealth The current health of the player.
 * @param enemyHealth The current health of the enemy.
 * @param difficulty The difficulty level affecting the speed of input reactions.
 */
void combatV1(int playerHealth, int enemyHealth, int difficulty)
{
    // Define directional moves and their keyboard equivalents
    std::string moves[] = {"\u2190", "\u2191", "\u2192", "\u2193"};
    std::string keyBoardEquivalent[] = {"a", "w", "d", "s"};
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed for randomness

    // Combat loop: continue while both player and enemy have health
    while (playerHealth > 0 && enemyHealth > 0)
    {
        int random_number = std::rand() % 4; // Select a random direction
        std::cout << moves[random_number] << std::flush; // Display the move symbol

        auto start = std::chrono::high_resolution_clock::now(); // Start timer for user input
        std::string inputStr;

        while (true)
        {
            std::getline(std::cin, inputStr); // Get user input
            auto now = std::chrono::high_resolution_clock::now(); // Capture current time
            std::chrono::duration<double> elapsed = now - start; // Calculate elapsed time

            // Check if user input matches and is within the allowed time
            if (inputStr == keyBoardEquivalent[random_number] && elapsed.count() < difficulty / 1000.0)
            {
                enemyHealth -= 5; // Successful hit on the enemy
                printHealth(playerHealth, enemyHealth);
                break;
            }
            else if (elapsed.count() >= difficulty / 1000.0)
            {
                playerHealth -= 10; // Player takes damage due to slow response
                printHealth(playerHealth, enemyHealth);
                break;
            }
            else
            {
                playerHealth -= 5; // Incorrect input results in minor damage
                printHealth(playerHealth, enemyHealth);
                break;
            }
        }
    }

    // Print win or lose message based on remaining health
    if (playerHealth > 0)
    {
        std::cout << "You Win!";
    }
    else
    {
        std::cout << "You Lose!";
    }

    std::cout << moves[0] << std::endl; // End message or action
}

/**
 * @brief Implements the second version of combat mechanics with type-based combat.
 * @param playerHealth The current health of the player.
 * @param enemyHealth The current health of the enemy.
 */
void combatV2(int playerHealth, int enemyHealth)
{
    // Define combat types: Offensive, Sneaky, Defensive
    char combatType[] = {'o', 'd', 's'};
    std::string options[] = {"Offensive", "Sneaky", "Defensive"};
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed for randomness
    int random_number = std::rand() % 3; // Randomly choose an enemy attack type

    // Combat loop: continue while both player and enemy have health
    while (playerHealth > 0 && enemyHealth > 0)
    {
        std::cout << "Please select an attack type";
        // Further implementation for player choices and combat resolution needed here
    }
}
