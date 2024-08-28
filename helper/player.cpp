#include "../lib/dependencies.h"
#include "../lib/player.h"

Player::Player()
{
    getNameFromUser();
    getClassFromUser();
    this->maxHealth = 100;
    this->currHealth = 100;
    clear(2);
}

// Destructor implementation
Player::~Player()
{
    // Cleanup code (if any) goes here
}

// Method to get the player's name from user input
void Player::getNameFromUser()
{
    std::cout << "Enter your name: ";
    firstName = getUserInputToken();
}

// Method to get the player's class type from user input
void Player::getClassFromUser()
{
    std::cout << "Enter your class type: ";
    classType = getUserInputToken();
}

// Method to add an item to the inventory
void Player::addToInventory(std::string item)
{
    inventory.push_back(item);
}

// Method to remove an item from the inventory
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

// Method to set the player's maximum health
void Player::setMaxHelth(int maxHealth)
{
    this->maxHealth = maxHealth;
    if (currHealth > maxHealth)
    {
        currHealth = maxHealth; // Ensure current health does not exceed maximum health
    }
}

// Method to set the player's current health
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

// Method to add a buff to the player's buffs
void Player::addBuff(std::string buff)
{
    buffs.push_back(buff);
}

// Method to remove a buff from the player's buffs
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

// Method to set the player's resistance
void Player::setResistance(int resistance)
{
    this->resistance = resistance;
}

// Method to get the player's name
std::string Player::getName()
{
    return firstName;
}

// Method to get the player's class type
std::string Player::getClassType()
{
    return classType;
}

// Method to get the player's inventory
std::vector<std::string> Player::getInventory()
{
    return inventory;
}

// Method to get the player's maximum health
int Player::getMaxHealth()
{
    return maxHealth;
}

// Method to get the player's current health
int Player::getCurrHealth()
{
    return currHealth;
}

// Method to get the player's resistance
int Player::getResistance()
{
    return resistance;
}

// Method to get the player's buffs
std::vector<std::string> Player::getBuffs()
{
    return buffs;
}
