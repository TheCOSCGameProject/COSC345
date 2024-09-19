/*!
@file player.cpp
@brief Implementation of the Player class.
@details This file contains the implementation of the Player class, which manages player attributes such as name, class type, health, inventory, buffs, and resistance. It includes methods for interacting with these attributes, allowing for adding/removing inventory items and buffs, setting health values, and more.
*/

#include "../lib/dependencies.h"
#include "../lib/player.h"

/*!
@brief Constructor for the Player class.
@details Initializes the player by obtaining the player's name and class type from user input, and setting the player's maximum and current health to 100.
*/


Player::Player()
    : maxHealth(100), 
      currHealth(100)   
{
    getNameFromUser();
    getClassFromUser();
    clear(2);
}

/*!
@brief Destructor for the Player class.
@details Cleans up resources when the Player object is destroyed.
*/
Player::~Player()
{
    // Cleanup code (if any) goes here
}

/*!
@brief Get the player's name from user input.
@details Prompts the user to enter their name and stores it in the `firstName` attribute.
*/
void Player::getNameFromUser()
{
    std::cout << "Enter your name: ";
    firstName = getUserInputToken();
}

/*!
@brief Get the player's class type from user input.
@details Prompts the user to enter their class type and stores it in the `classType` attribute.
*/
void Player::getClassFromUser()
{
    std::cout << "Enter your class type: ";
    classType = getUserInputToken();
}

/*!
@brief Add an item to the player's inventory.
@param item The name of the item to add to the inventory.
*/
void Player::addToInventory(std::string item)
{
    inventory.push_back(item);
}

/*!
@brief Remove an item from the player's inventory.
@param item The name of the item to remove from the inventory.
@details If the item is not found in the inventory, a message is displayed to the user.
*/
void Player::removeFromInventory(std::string item)
{
    auto it = std::find(inventory.begin(), inventory.end(), item);
    if (it != inventory.end())
    {
        inventory.erase(it);
    }
    else
    {
        std::cout << "Item not found in inventory." << std::endl;
    }
}

/*!
@brief Set the player's maximum health.
@param maxHealth The new maximum health value.
@details If the current health exceeds the new maximum health, it is reduced to the maximum health.
*/
void Player::setMaxHelth(int maxHealth)
{
    this->maxHealth = maxHealth;
    if (currHealth > maxHealth)
    {
        currHealth = maxHealth; // Ensure current health does not exceed maximum health
    }
}

/*!
@brief Set the player's current health.
@param health The new current health value.
@details The health value is clamped between 0 and the player's maximum health.
*/
void Player::setCurrHealth(int health)
{
    if (health > maxHealth)
    {
        currHealth = maxHealth;
    }
    else if (health < 0)
    {
        currHealth = 0;
    }
    else
    {
        currHealth = health;
    }
}

/*!
@brief Add a buff to the player's active buffs.
@param buff The name of the buff to add.
*/
void Player::addBuff(std::string buff)
{
    buffs.push_back(buff);
}

/*!
@brief Remove a buff from the player's active buffs.
@param buff The name of the buff to remove.
@details If the buff is not found, a message is displayed to the user.
*/
void Player::removeBuff(std::string buff)
{
    auto it = std::find(buffs.begin(), buffs.end(), buff);
    if (it != buffs.end())
    {
        buffs.erase(it);
    }
    else
    {
        std::cout << "Buff not found." << std::endl;
    }
}

/*!
@brief Set the player's resistance value.
@param resistance The new resistance value.
*/
void Player::setResistance(int resistance)
{
    this->resistance = resistance;
}

/*!
@brief Get the player's name.
@return The player's name as a string.
*/
std::string Player::getName()
{
    return firstName;
}

/*!
@brief Get the player's class type.
@return The player's class type as a string.
*/
std::string Player::getClassType()
{
    return classType;
}

/*!
@brief Get the player's inventory.
@return A vector of strings representing the items in the player's inventory.
*/
std::vector<std::string> Player::getInventory()
{
    return inventory;
}

/*!
@brief Get the player's maximum health.
@return The player's maximum health as an integer.
*/
int Player::getMaxHealth()
{
    return maxHealth;
}

/*!
@brief Get the player's current health.
@return The player's current health as an integer.
*/
int Player::getCurrHealth()
{
    return currHealth;
}

/*!
@brief Get the player's resistance value.
@return The player's resistance as an integer.
*/
int Player::getResistance()
{
    return resistance;
}

/*!
@brief Get the player's active buffs.
@return A vector of strings representing the player's active buffs.
*/
std::vector<std::string> Player::getBuffs()
{
    return buffs;
}
