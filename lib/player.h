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
    std::string species;
    std::string firstName;
    std::string resistance;
    int maxHealth;
    int currHealth;
    std::vector<std::string> buffs;

public:
    // Constructor
    Player();

    // Destructor
    ~Player();

    // Additional member functions can be declared here, if any
    // Example:
    // void addBuff(const std::string& buff);
    // void takeDamage(int damage);
    // void heal(int amount);
    // std::string getFirstName() const;
};

#endif // PLAYER_H
