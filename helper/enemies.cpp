#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Enemy
{
    std::string name;
    int health;
    int attack;
    std::string type;        // idk
    int defence;             // Damage taken modifier
    std::string personality; // Dialogue/Combat 'aggressiveness'
};

class EnemySpawner
{
public:
    EnemySpawner()
    {
        // seed
        srand(static_cast<unsigned int>(time(0)));
    }

    Enemy spawnEnemy()
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

    int getHealth(const Enemy &enemy)
    {
        return enemy.health;
    }

    int getAttack(const Enemy &enemy)
    {
        return enemy.attack;
    }

    std::string getName(const Enemy &enemy)
    {
        return enemy.name;
    }

    std::string getType(const Enemy &enemy)
    {
        return enemy.type;
    }

    std::string getPersonality(const Enemy &enemy) // For dialogue
    {
        return enemy.personality;
    }

    int getDefence(const Enemy &enemy)
    {
        return enemy.defence;
    }

    bool isDead(const Enemy &enemy)
    {
        return enemy.health <= 0;
    }

    void damageDelt(Enemy &enemy, int hurt)
    {
        if (enemy.type == "Sardaukar")
        {
            hurt = hurt * 0.8;
        }
        enemy.health -= hurt * (1 - enemy.defence / 100);
    }

    void setAttack(Enemy &enemy, int attack)
    {
        enemy.attack = attack;
    }

    void setHealth(Enemy &enemy, int health) // Don't use to update health from attacks
    {
        enemy.health = health;
    }

private:
    std::string generateName()
    {
        std::vector<std::string> names = {"Kaelen", "Liora", "Orin", "Zylara", "KL-98", "RW-07", "Charles", "Jacket", "Raid"};
        return names[rand() % names.size()];
    }

    int generateHealth()
    {
        return rand() % 51 + 50; // Health between 50 and 100
    }

    int generateAttack()
    {
        return rand() % 21 + 10; // Attack between 10 and 30
    }

    std::string generateType()
    {
        std::vector<std::string> types = {"Sardaukar", "Fremen", "AI", "Rodians"};
        return types[rand() % types.size()];
    }

    std::string generatePersonality()
    {
        std::vector<std::string> types = {"Upstanding", "Martial", "Cunning", "Sadistic", "Cautious"};
        return types[rand() % types.size()];
    }

    int generateDefence()
    {
        return rand() % 76 + 5; // Defence between 5 and 80
    }
};

// int main() // Hoaw to use
// {
//     EnemySpawner spawner;

//     // Spawn an enemy
//     Enemy enemy = spawner.spawnEnemy();

//     // Display the enemy's details
//     std::cout << "Enemy Name: " << spawner.getName(enemy) << std::endl;
//     std::cout << "Type: " << spawner.getType(enemy) << std::endl;
//     std::cout << "Health: " << spawner.getHealth(enemy) << std::endl;
//     std::cout << "Attack: " << spawner.getAttack(enemy) << std::endl;
//     std::cout << "Defence: " << spawner.getDefence(enemy) << std::endl;
//     std::cout << "Personality: " << spawner.getPersonality(enemy) << std::endl;
//     spawner.damageDelt(enemy, 50);
//     std::cout << "Health: " << spawner.getHealth(enemy) << std::endl;
//     std::cout << "Is dead: " << spawner.isDead(enemy) << std::endl;

//     return 0;
// }
