/*!
 * @file combat.h
 * @brief Declares combat-related functions for the Valeris game.
 * @details This file contains the declarations of functions used to manage and execute combat scenarios in the game,
 * including printing health statuses and handling different versions of combat mechanics.
 */

#ifndef COMBAT_H
#define COMBAT_H

#include "../lib/dependencies.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

/*!
 * @brief Prints the health status of the player and the enemy.
 * @param playerHealth The current health of the player.
 * @param enemyHealth The current health of the enemy.
 * @param name The name of the enemy.
 * @details This function displays the current health points of both the player and the enemy, providing an overview of the combat situation.
 */
void printHealth(int playerHealth, int enemyHealth, const std::string &name);

/*!
 * @brief Handles combat mechanics for version 1.
 * @param playerHealth The initial health of the player.
 * @param enemyHealth The initial health of the enemy.
 * @param difficulty The difficulty level of the combat (e.g., easy, medium, hard).
 * @param name The name of the enemy.
 * @return True if the player wins the combat, otherwise false.
 * @details This function simulates a combat scenario between the player and an enemy, taking into account the difficulty level.
 * The outcome of the combat is determined based on the player's and enemy's health.
 */
bool combatV1(int playerHealth, int enemyHealth, int difficulty, const std::string &name);

/*!
 * @brief Handles combat mechanics for version 2.
 * @param playerHealth The initial health of the player.
 * @param enemyHealth The initial health of the enemy.
 * @details This function provides an alternative combat system with potentially different rules or mechanics compared to combatV1.
 */
void combatV2(int playerHealth, int enemyHealth);

#endif // COMBAT_H