/*!
 * @file player.h
 * @brief Defines the Player class for the Valeris game.
 * @details This file contains the declaration of the Player class, which manages player attributes such as health, inventory, class type, and buffs.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <iostream>
#include "../lib/toolkit.h" // Assuming this header file contains the declaration of getUserInputToken()

/*!
 * @class Player
 * @brief Manages player attributes and actions.
 * @details The Player class handles the player's inventory, health, class type, buffs, and other attributes. It also provides methods for interacting with these attributes.
 */
class Player
{
private:
    int maxHealth; //!< The maximum health of the player.
    int currHealth; //!< The current health of the player.
    std::vector<std::string> inventory; //!< Player's inventory containing item names.
    std::string classType; //!< The class type of the player (e.g., warrior, mage).
    std::string firstName; //!< The first name of the player.
    int resistance; //!< The player's resistance value, which might affect damage taken.
    std::vector<std::string> buffs; //!< List of active buffs on the player.

public:
    /*!
     * @brief Constructor for the Player class.
     * @details Initializes the player's attributes with default values.
     */
    Player();

    /*!
     * @brief Destructor for the Player class.
     */
    ~Player();

    /*!
     * @brief Get the player's name from user input.
     * @details Prompts the user to enter their name, which is then stored in the firstName attribute.
     */
    void getNameFromUser();

    /*!
     * @brief Get the player's class type from user input.
     * @details Prompts the user to choose a class type for the player character.
     */
    void getClassFromUser();

    /*!
     * @brief Add an item to the player's inventory.
     * @param item The name of the item to add.
     */
    void addToInventory(std::string item);

    /*!
     * @brief Remove an item from the player's inventory.
     * @param item The name of the item to remove.
     */
    void removeFromInventory(std::string item);

    /*!
     * @brief Set the player's maximum health.
     * @param maxHealth The maximum health value to set.
     */
    void setMaxHelth(int maxHealth);

    /*!
     * @brief Set the player's current health.
     * @param health The current health value to set.
     */
    void setCurrHealth(int health);

    /*!
     * @brief Add a buff to the player.
     * @param buff The name of the buff to add.
     */
    void addBuff(std::string buff);

    /*!
     * @brief Remove a buff from the player.
     * @param buff The name of the buff to remove.
     */
    void removeBuff(std::string buff);

    /*!
     * @brief Set the player's resistance value.
     * @param resistance The resistance value to set.
     */
    void setResistance(int resistance);

    /*!
     * @brief Get the player's name.
     * @return The player's name.
     */
    std::string getName();

    /*!
     * @brief Get the player's class type.
     * @return The player's class type.
     */
    std::string getClassType();

    /*!
     * @brief Get the player's inventory.
     * @return A vector of strings representing the items in the player's inventory.
     */
    std::vector<std::string> getInventory();

    /*!
     * @brief Get the player's maximum health.
     * @return The player's maximum health value.
     */
    int getMaxHealth();

    /*!
     * @brief Get the player's current health.
     * @return The player's current health value.
     */
    int getCurrHealth();

    /*!
     * @brief Get the player's resistance value.
     * @return The player's resistance value.
     */
    int getResistance();

    /*!
     * @brief Get the player's active buffs.
     * @return A vector of strings representing the player's active buffs.
     */
    std::vector<std::string> getBuffs();
};

#endif // PLAYER_H
