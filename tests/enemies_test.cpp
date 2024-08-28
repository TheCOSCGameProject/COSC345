#include "../lib/enemies.h"
#include "custom_test_framework.h"

// g++ -std=c++17 -o run_tests.exe tests/enemies_test.cpp ./helper/enemies.cpp
// ./ run_tests.exe

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

int main()
{
    TestFramework framework("enemy_test_results.xml");

    framework.addTest("Enemy Initialisation", testEnemyInitialisation);
    framework.addTest("Enemy Damage Application", testEnemyDamageApplication);
    framework.addTest("Enemy Death Condition", testEnemyDeathCondition);
    framework.addTest("Enemy Custom Setters", testEnemyCustomSetters);

    framework.run();

    return 0;
}