// enemies.cpp
#include "../lib/enemies.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Constructor to seed random number generator
EnemySpawner::EnemySpawner()
{
    srand(static_cast<unsigned int>(time(0)));
}

// Method to spawn an enemy
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
int EnemySpawner::getHealth(const Enemy &enemy) { return enemy.health; }
int EnemySpawner::getAttack(const Enemy &enemy) { return enemy.attack; }
std::string EnemySpawner::getName(const Enemy &enemy) { return enemy.name; }
std::string EnemySpawner::getType(const Enemy &enemy) { return enemy.type; }
std::string EnemySpawner::getPersonality(const Enemy &enemy) { return enemy.personality; }
int EnemySpawner::getDefence(const Enemy &enemy) { return enemy.defence; }
bool EnemySpawner::isDead(const Enemy &enemy) { return enemy.health <= 0; }

// Method to apply damage to an enemy
void EnemySpawner::damageDelt(Enemy &enemy, int hurt)
{
    if (enemy.type == "Sardaukar")
    {
        hurt = hurt * 0.8;
    }
    enemy.health -= hurt * (1 - enemy.defence / 100);
}

// Methods to set enemy attributes
void EnemySpawner::setAttack(Enemy &enemy, int attack) { enemy.attack = attack; }
void EnemySpawner::setHealth(Enemy &enemy, int health) { enemy.health = health; }

// Private methods to generate random enemy attributes
std::string EnemySpawner::generateName()
{
    std::vector<std::string> names = {"Kaelen", "Liora", "Orin", "Zylara", "KL-98", "RW-07", "Charles", "Jacket", "Raid"};
    return names[rand() % names.size()];
}

int EnemySpawner::generateHealth()
{
    return rand() % 51 + 50; // Health between 50 and 100
}

int EnemySpawner::generateAttack()
{
    return rand() % 21 + 10; // Attack between 10 and 30
}

std::string EnemySpawner::generateType()
{
    std::vector<std::string> types = {"Sardaukar", "Fremen", "AI", "Rodians"};
    return types[rand() % types.size()];
}

std::string EnemySpawner::generatePersonality()
{
    std::vector<std::string> types = {"Upstanding", "Martial", "Cunning", "Sadistic", "Cautious"};
    return types[rand() % types.size()];
}

int EnemySpawner::generateDefence()
{
    return rand() % 76 + 5; // Defence between 5 and 80
}
