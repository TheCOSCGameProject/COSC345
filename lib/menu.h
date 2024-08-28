#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

// Function to display introductory text
void displayIntro(int delayTime, std::string color);

// Function to display the game menu
void Displayj();

// Function to start a new game
void StartGame();

// Function to load a saved game
void LoadSavedGame();

// Function to display game instructions
void DisplayInstructionsText();

// Function to manage accessibility options
void Accessiblity(int &delayTime, std::string &color);

#endif // MENU_H
