// enemies.cpp
#include "../lib/enemies.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

/**
 * @brief Constructor for the EnemySpawner class.
 * @details Seeds the random number generator with the current time.
 */
EnemySpawner::EnemySpawner()
{
    srand(static_cast<unsigned int>(time(0)));
}

/**
 * @brief Spawns a new enemy with random attributes.
 * @return An Enemy object with randomly generated attributes.
 */
Enemy EnemySpawner::spawnEnemy()
{
    Enemy enemy;
    enemy.name = generateName();
    enemy.health = generateHealth();
    enemy.attack = generateAttack();
    enemy.type = generateType();
    enemy.personality = generatePersonality();
    enemy.defence = generateDefence();
    return enemy;
}

// Methods to get enemy attributes

/**
 * @brief Retrieves the health of a specified enemy.
 * @param enemy The Enemy object whose health is to be retrieved.
 * @return The health value of the enemy.
 */
int EnemySpawner::getHealth(const Enemy &enemy) { return enemy.health; }

/**
 * @brief Retrieves the attack value of a specified enemy.
 * @param enemy The Enemy object whose attack value is to be retrieved.
 * @return The attack value of the enemy.
 */
int EnemySpawner::getAttack(const Enemy &enemy) { return enemy.attack; }

/**
 * @brief Retrieves the name of a specified enemy.
 * @param enemy The Enemy object whose name is to be retrieved.
 * @return The name of the enemy.
 */
std::string EnemySpawner::getName(const Enemy &enemy) { return enemy.name; }

/**
 * @brief Retrieves the type of a specified enemy.
 * @param enemy The Enemy object whose type is to be retrieved.
 * @return The type of the enemy.
 */
std::string EnemySpawner::getType(const Enemy &enemy) { return enemy.type; }

/**
 * @brief Retrieves the personality of a specified enemy.
 * @param enemy The Enemy object whose personality is to be retrieved.
 * @return The personality of the enemy.
 */
std::string EnemySpawner::getPersonality(const Enemy &enemy) { return enemy.personality; }

/**
 * @brief Retrieves the defence value of a specified enemy.
 * @param enemy The Enemy object whose defence value is to be retrieved.
 * @return The defence value of the enemy.
 */
int EnemySpawner::getDefence(const Enemy &enemy) { return enemy.defence; }

/**
 * @brief Checks if a specified enemy is dead.
 * @param enemy The Enemy object to check.
 * @return True if the enemy's health is less than or equal to 0, otherwise false.
 */
bool EnemySpawner::isDead(const Enemy &enemy) { return enemy.health <= 0; }

/**
 * @brief Applies damage to a specified enemy.
 * @details Adjusts damage based on the enemy's type and defence value.
 * @param enemy The Enemy object to apply damage to.
 * @param hurt The amount of damage to apply.
 */
void EnemySpawner::damageDelt(Enemy &enemy, int hurt)
{
    if (enemy.type == "Sardaukar")
    {
        hurt = hurt * 0.8; // Sardaukar enemies take reduced damage
    }
    enemy.health -= hurt * (1 - enemy.defence / 100);
}

// Methods to set enemy attributes

/**
 * @brief Sets the attack value of a specified enemy.
 * @param enemy The Enemy object whose attack value is to be set.
 * @param attack The new attack value to set.
 */
void EnemySpawner::setAttack(Enemy &enemy, int attack) { enemy.attack = attack; }

/**
 * @brief Sets the health value of a specified enemy.
 * @param enemy The Enemy object whose health value is to be set.
 * @param health The new health value to set.
 */
void EnemySpawner::setHealth(Enemy &enemy, int health) { enemy.health = health; }

// Private methods to generate random enemy attributes

/**
 * @brief Generates a random name for an enemy.
 * @return A string representing the generated name.
 */
std::string EnemySpawner::generateName()
{
    std::vector<std::string> names = {"Kaelen", "Liora", "Orin", "Zylara", "KL-98", "RW-07", "Charles", "Jacket", "Raid"};
    return names[rand() % names.size()];
}

/**
 * @brief Generates a random health value for an enemy.
 * @return An integer representing the generated health (between 50 and 100).
 */
int EnemySpawner::generateHealth()
{
    return rand() % 51 + 50; // Health between 50 and 100
}

/**
 * @brief Generates a random attack value for an enemy.
 * @return An integer representing the generated attack (between 10 and 30).
 */
int EnemySpawner::generateAttack()
{
    return rand() % 21 + 10; // Attack between 10 and 30
}

/**
 * @brief Generates a random type for an enemy.
 * @return A string representing the generated type.
 */
std::string EnemySpawner::generateType()
{
    std::vector<std::string> types = {"Sardaukar", "Fremen", "AI", "Rodians"};
    return types[rand() % types.size()];
}

/**
 * @brief Generates a random personality trait for an enemy.
 * @return A string representing the generated personality.
 */
std::string EnemySpawner::generatePersonality()
{
    std::vector<std::string> personalities = {"Upstanding", "Martial", "Cunning", "Sadistic", "Cautious"};
    return personalities[rand() % personalities.size()];
}

/**
 * @brief Generates a random defence value for an enemy.
 * @return An integer representing the generated defence (between 5 and 80).
 */
int EnemySpawner::generateDefence()
{
    return rand() % 76 + 5; // Defence between 5 and 80
}
