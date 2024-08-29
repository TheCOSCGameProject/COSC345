/*!
@file enemies.cpp
@brief Implementation of the EnemySpawner class.
@details This file contains the implementation of the EnemySpawner class, which is responsible for creating and managing enemies in the game. The class includes methods for spawning enemies with randomized attributes, retrieving and modifying those attributes, and applying damage to enemies.
*/

#include "../lib/enemies.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

/*!
@brief Constructor for the EnemySpawner class.
@details Initializes the random number generator used for generating random enemy attributes.
*/
EnemySpawner::EnemySpawner()
{
    srand(static_cast<unsigned int>(time(0)));
}

/*!
@brief Spawn a new enemy with randomized attributes.
@return An Enemy object with randomly generated name, health, attack, type, personality, and defence.
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

/*!
@brief Get the health of a given enemy.
@param enemy The enemy whose health is to be retrieved.
@return The health value of the enemy.
*/
int EnemySpawner::getHealth(const Enemy &enemy) { return enemy.health; }

/*!
@brief Get the attack value of a given enemy.
@param enemy The enemy whose attack value is to be retrieved.
@return The attack value of the enemy.
*/
int EnemySpawner::getAttack(const Enemy &enemy) { return enemy.attack; }

/*!
@brief Get the name of a given enemy.
@param enemy The enemy whose name is to be retrieved.
@return The name of the enemy.
*/
std::string EnemySpawner::getName(const Enemy &enemy) { return enemy.name; }

/*!
@brief Get the type of a given enemy.
@param enemy The enemy whose type is to be retrieved.
@return The type of the enemy.
*/
std::string EnemySpawner::getType(const Enemy &enemy) { return enemy.type; }

/*!
@brief Get the personality of a given enemy.
@param enemy The enemy whose personality is to be retrieved.
@return The personality of the enemy.
*/
std::string EnemySpawner::getPersonality(const Enemy &enemy) { return enemy.personality; }

/*!
@brief Get the defence value of a given enemy.
@param enemy The enemy whose defence value is to be retrieved.
@return The defence value of the enemy.
*/
int EnemySpawner::getDefence(const Enemy &enemy) { return enemy.defence; }

/*!
@brief Check if a given enemy is dead.
@param enemy The enemy to check.
@return True if the enemy's health is 0 or less, false otherwise.
*/
bool EnemySpawner::isDead(const Enemy &enemy) { return enemy.health <= 0; }

/*!
@brief Apply damage to a given enemy.
@param enemy The enemy to apply damage to.
@param hurt The amount of damage to apply.
@details The damage is reduced based on the enemy's type and defence value. Sardaukar enemies take 20% less damage.
*/
void EnemySpawner::damageDelt(Enemy &enemy, int hurt)
{
    double newHurt = hurt;
    if (enemy.type == "Sardaukar")
    {
        newHurt = hurt * 0.8; // Sardaukar enemies take reduced damage
    }
    enemy.health -= (int)(newHurt * (1 - enemy.defence / 100.0));
}

// Methods to set enemy attributes

/*!
@brief Set the attack value of a given enemy.
@param enemy The enemy whose attack value is to be set.
@param attack The new attack value.
*/
void EnemySpawner::setAttack(Enemy &enemy, int attack) { enemy.attack = attack; }

/*!
@brief Set the health value of a given enemy.
@param enemy The enemy whose health value is to be set.
@param health The new health value.
*/
void EnemySpawner::setHealth(Enemy &enemy, int health) { enemy.health = health; }

// Private methods to generate random enemy attributes

/*!
@brief Generate a random name for an enemy.
@return A string representing the randomly generated name.
@details The name is selected randomly from a predefined list of names.
*/
std::string EnemySpawner::generateName()
{
    std::vector<std::string> names = {"Kaelen", "Liora", "Orin", "Zylara", "KL-98", "RW-07", "Charles", "Jacket", "Raid"};
    return names[rand() % names.size()];
}

/*!
@brief Generate a random health value for an enemy.
@return An integer representing the randomly generated health value, between 50 and 100.
*/
int EnemySpawner::generateHealth()
{
    return rand() % 51 + 50; // Health between 50 and 100
}

/*!
@brief Generate a random attack value for an enemy.
@return An integer representing the randomly generated attack value, between 10 and 30.
*/
int EnemySpawner::generateAttack()
{
    return rand() % 21 + 10; // Attack between 10 and 30
}

/*!
@brief Generate a random type for an enemy.
@return A string representing the randomly generated type.
@details The type is selected randomly from a predefined list of types.
*/
std::string EnemySpawner::generateType()
{
    std::vector<std::string> types = {"Sardaukar", "Fremen", "AI", "Rodians"};
    return types[rand() % types.size()];
}

/*!
@brief Generate a random personality for an enemy.
@return A string representing the randomly generated personality.
@details The personality is selected randomly from a predefined list of personalities.
*/
std::string EnemySpawner::generatePersonality()
{
    std::vector<std::string> personalities = {"Upstanding", "Martial", "Cunning", "Sadistic", "Cautious"};
    return personalities[rand() % personalities.size()];
}

/*!
@brief Generate a random defence value for an enemy.
@return An integer representing the randomly generated defence value, between 5 and 80.
*/
int EnemySpawner::generateDefence()
{
    return rand() % 76 + 5; // Defence between 5 and 80
}
