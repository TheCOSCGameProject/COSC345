// toolkit.h
#ifndef TOOLKIT_H
#define TOOLKIT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

#ifdef _WIN32
#include <windows.h>

// Function to set the console size on Windows
void SetConsoleSize(int width, int height);

#else
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

// Function to set the terminal size on non-Windows systems
void SetTerminalSize(int height, int width);

#endif

// Function to mimic a delay
void delay(int milliseconds);

// Function to print text with a typing effect
void typePrint(std::string content, int delayTime, std::string color);

// Function to read the content of a file and return it as a string
std::string getFileContent(std::string fileName);

// Function to split a string by a delimiter and return a vector of tokens
std::vector<std::string> split(const std::string &str, char delimiter);

// Function to clear the console up to a certain limit
void clear(int limit);

// Function to get a full line of user input
std::string getUserInputLine();

// Function to get a single word or token of user input
std::string getUserInputToken();

int generateRandomNumber(int low, int high);

int stringToInt(const std::string &str);

std::string repeatString(const std::string &str, int count);

std::string toLowerCase(const std::string &str);

int readInt();

void disableInput();

void enableInput();

void waitForEnter();

#endif // TOOLKIT_H