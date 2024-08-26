#ifndef COMBAT_H
#define COMBAT_H

#include "../lib/dependencies.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

// Function to print player and enemy health status
void printHealth(int playerHealth, int enemyHealth);

// Function to handle combat version 1
void combatV1(int playerHealth, int enemyHealth, int difficulty);

// Function to handle combat version 2
void combatV2(int playerHealth, int enemyHealth);

#endif // COMBAT_H