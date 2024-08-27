#ifndef ENEMIES_H
#define ENEMIES_H

#include <string>

// Define the Enemy structure
struct Enemy
{
    std::string name;
    int health;
    int attack;
    std::string type;
    std::string personality;
    int defence;
};

// Declare the EnemySpawner class
class EnemySpawner
{
public:
    EnemySpawner();
    Enemy spawnEnemy();

    int getHealth(const Enemy& enemy);
    int getAttack(const Enemy& enemy);
    std::string getName(const Enemy& enemy);
    std::string getType(const Enemy& enemy);
    std::string getPersonality(const Enemy& enemy);
    int getDefence(const Enemy& enemy);
    bool isDead(const Enemy& enemy);
    void damageDelt(Enemy& enemy, int hurt);

    void setAttack(Enemy& enemy, int attack);
    void setHealth(Enemy& enemy, int health);

private:
    std::string generateName();
    int generateHealth();
    int generateAttack();
    std::string generateType();
    std::string generatePersonality();
    int generateDefence();
};

#endif // ENEMIES_H
