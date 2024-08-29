/*!
 * @file enemies.h
 * @brief Defines the Enemy structure and EnemySpawner class for the Valeris game.
 * @details This file contains the declaration of the Enemy structure, which represents an enemy character in the game,
 * and the EnemySpawner class, which is responsible for spawning enemies with randomly generated attributes.
 */

#ifndef ENEMIES_H
#define ENEMIES_H

#include <string>

/*!
 * @struct Enemy
 * @brief Represents an enemy character in the game.
 * @details The Enemy structure contains attributes such as name, health, attack, type, personality, and defense 
 * that define the characteristics of an enemy.
 */
struct Enemy
{
    std::string name; //!< The name of the enemy.
    int health; //!< The health points of the enemy.
    int attack; //!< The attack power of the enemy.
    std::string type; //!< The type or category of the enemy.
    std::string personality; //!< The personality trait of the enemy.
    int defence; //!< The defense value of the enemy.
};

/*!
 * @class EnemySpawner
 * @brief Responsible for spawning enemies in the game.
 * @details The EnemySpawner class generates enemies with random attributes, and provides methods to interact with 
 * and modify the properties of these enemies.
 */
class EnemySpawner
{
public:
    /*!
     * @brief Constructor for the EnemySpawner class.
     * @details Initializes the EnemySpawner object, preparing it to generate enemies.
     */
    EnemySpawner();

    /*!
     * @brief Spawns a new enemy with randomly generated attributes.
     * @return An Enemy object with generated attributes.
     */
    Enemy spawnEnemy();

    /*!
     * @brief Gets the health of the specified enemy.
     * @param enemy The enemy whose health is to be retrieved.
     * @return The health points of the enemy.
     */
    int getHealth(const Enemy &enemy);

    /*!
     * @brief Gets the attack power of the specified enemy.
     * @param enemy The enemy whose attack power is to be retrieved.
     * @return The attack power of the enemy.
     */
    int getAttack(const Enemy &enemy);

    /*!
     * @brief Gets the name of the specified enemy.
     * @param enemy The enemy whose name is to be retrieved.
     * @return The name of the enemy.
     */
    std::string getName(const Enemy &enemy);

    /*!
     * @brief Gets the type of the specified enemy.
     * @param enemy The enemy whose type is to be retrieved.
     * @return The type of the enemy.
     */
    std::string getType(const Enemy &enemy);

    /*!
     * @brief Gets the personality of the specified enemy.
     * @param enemy The enemy whose personality is to be retrieved.
     * @return The personality of the enemy.
     */
    std::string getPersonality(const Enemy &enemy);

    /*!
     * @brief Gets the defense value of the specified enemy.
     * @param enemy The enemy whose defense value is to be retrieved.
     * @return The defense value of the enemy.
     */
    int getDefence(const Enemy &enemy);

    /*!
     * @brief Checks if the specified enemy is dead.
     * @param enemy The enemy to check.
     * @return True if the enemy's health is zero or below, otherwise false.
     */
    bool isDead(const Enemy &enemy);

    /*!
     * @brief Applies damage to the specified enemy.
     * @param enemy The enemy to damage.
     * @param hurt The amount of damage to apply.
     */
    void damageDelt(Enemy &enemy, int hurt);

    /*!
     * @brief Sets the attack power of the specified enemy.
     * @param enemy The enemy whose attack power is to be set.
     * @param attack The attack power to set.
     */
    void setAttack(Enemy &enemy, int attack);

    /*!
     * @brief Sets the health of the specified enemy.
     * @param enemy The enemy whose health is to be set.
     * @param health The health value to set.
     */
    void setHealth(Enemy &enemy, int health);

private:
    /*!
     * @brief Generates a random name for an enemy.
     * @return A randomly generated name.
     */
    std::string generateName();

    /*!
     * @brief Generates a random health value for an enemy.
     * @return A randomly generated health value.
     */
    int generateHealth();

    /*!
     * @brief Generates a random attack value for an enemy.
     * @return A randomly generated attack value.
     */
    int generateAttack();

    /*!
     * @brief Generates a random type for an enemy.
     * @return A randomly generated type.
     */
    std::string generateType();

    /*!
     * @brief Generates a random personality trait for an enemy.
     * @return A randomly generated personality trait.
     */
    std::string generatePersonality();

    /*!
     * @brief Generates a random defense value for an enemy.
     * @return A randomly generated defense value.
     */
    int generateDefence();
};

#endif // ENEMIES_H
