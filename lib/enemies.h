#ifndef ENEMIES_H
#define ENEMIES_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

// Enemy struct definition
struct Enemy
{
    std::string name;
    int health;
    int attack;
    std::string type;        // Enemy type
    int defence;             // Damage taken modifier
    std::string personality; // Dialogue/Combat 'aggressiveness'
};

// EnemySpawner class definition
class EnemySpawner
{
public:
    EnemySpawner(); // Constructor

    Enemy spawnEnemy(); // Spawns an enemy with random attributes

    // Getters for Enemy attributes
    int getHealth(const Enemy &enemy);
    int getAttack(const Enemy &enemy);
    std::string getName(const Enemy &enemy);
    std::string getType(const Enemy &enemy);
    std::string getPersonality(const Enemy &enemy);
    int getDefence(const Enemy &enemy);

    bool isDead(const Enemy &enemy); // Checks if the enemy is dead

    // Methods to modify Enemy attributes
    void damageDelt(Enemy &enemy, int hurt);
    void setAttack(Enemy &enemy, int attack);
    void setHealth(Enemy &enemy, int health); // Don't use to update health from attacks

private:
    // Methods to generate random attributes for the enemy
    std::string generateName();
    int generateHealth();
    int generateAttack();
    std::string generateType();
    std::string generatePersonality();
    int generateDefence();
};

#endif // ENEMIES_H
