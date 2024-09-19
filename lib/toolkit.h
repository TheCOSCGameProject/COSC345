/*!
 * @file toolkit.h
 * @brief Utility functions for the Valeris game.
 * @details This file contains various utility functions that are used throughout the Valeris game.
 * These include functions for console manipulation, input handling, string processing, and more.
 */

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

/*!
 * @brief Set the console size on Windows.
 * @param width The desired width of the console.
 * @param height The desired height of the console.
 */
void SetConsoleSize(int width, int height);

#else
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

/*!
 * @brief Set the terminal size on non-Windows systems.
 * @param height The desired height of the terminal.
 * @param width The desired width of the terminal.
 */
void SetTerminalSize(int height, int width);

#endif

/*!
 * @brief Mimic a delay in milliseconds.
 * @param milliseconds The number of milliseconds to delay.
 */
void delay(int milliseconds);

/*!
 * @brief Print text with a typing effect.
 * @param content The text content to print.
 * @param delayTime The delay time between characters in milliseconds.
 * @param color The color code for the text.
 */
void typePrint(const std::string &content, int delayTime = 15, const std::string &color = "\033[36m");

/*!
 * @brief Read the content of a file and return it as a string.
 * @param fileName The name of the file to read.
 * @return The content of the file as a string.
 */
std::string getFileContent(std::string fileName);

/*!
 * @brief Split a string by a delimiter.
 * @param str The string to split.
 * @param delimiter The character used as the delimiter.
 * @return A vector of tokens resulting from the split.
 */
std::vector<std::string> split(const std::string &str, char delimiter);

/*!
 * @brief Clear the console up to a certain limit.
 * @param limit The number of lines to clear.
 */
void clear(int limit);

/*!
 * @brief Get a full line of user input.
 * @return The user's input as a string.
 */
std::string getUserInputLine();

/*!
 * @brief Get a single word or token of user input.
 * @return The user's input as a string.
 */
std::string getUserInputToken();

/*!
 * @brief Generate a random number between two values.
 * @param low The lower bound of the random number.
 * @param high The upper bound of the random number.
 * @return A random number between low and high.
 */
int generateRandomNumber(int low, int high);

/*!
 * @brief Convert a string to an integer.
 * @param str The string to convert.
 * @return The integer value of the string.
 */
int stringToInt(const std::string &str);

/*!
 * @brief Repeat a string a specified number of times.
 * @param str The string to repeat.
 * @param count The number of times to repeat the string.
 * @return The resulting string after repetition.
 */
std::string repeatString(const std::string &str, int count);

/*!
 * @brief Convert a string to lowercase.
 * @param str The string to convert.
 * @return The lowercase version of the string.
 */
std::string toLowerCase(const std::string &str);

/*!
 * @brief Read an integer from user input.
 * @return The integer value entered by the user.
 */
int readInt();

/*!
 * @brief Disable user input.
 */
void disableInput();

/*!
 * @brief Enable user input.
 */
void enableInput();

/*!
 * @brief Wait for the user to press Enter.
 */
void waitForEnter();

/*!
 * @brief Convert a string to uppercase.
 * @param input The string to convert.
 * @return The uppercase version of the string.
 */
std::string toUpperCase(const std::string &input);

#endif // TOOLKIT_H
