#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <iostream>
#include "../lib/toolkit.h" // Assuming this header file contains the declaration of getUserInputToken()

class Player
{
private:
    std::vector<std::string> inventory;
    std::string classType;
    std::string firstName;
    int resistance;
    int maxHealth;
    int currHealth;
    std::vector<std::string> buffs;

public:
    // Constructor
    Player();

    // Destructor
    ~Player();

    void getNameFromUser();
    void getClassFromUser();
    void addToInventory(std::string item);
    void removeFromInventory(std::string item);
    void setMaxHelth(int maxHealth);
    void setCurrHealth(int health);
    void addBuff(std::string buff);
    void removeBuff(std::string buff);
    void setResistance(int resistance);
    std::string getName();
    std::string getClassType();
    std::vector<std::string> getInventory();
    int getMaxHealth();
    int getCurrHealth();
    int getResistance();
    std::vector<std::string> getBuffs();
};

#endif // PLAYER_H
