#include "../lib/dependencies.h"
#include "../lib/player.h"

Player::Player()
{
    std::cout << "Please choose a name for your character: ";
    this->firstName = getUserInputToken();
    std::cout << this->firstName;
}

// Destructor implementation
Player::~Player()
{
    // Cleanup code (if any) goes here
}
