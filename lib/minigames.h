/*!
 * @file minigames.h
 * @brief Defines the base Game class and its derived classes for the Valeris game.
 * @details This file contains the declaration of the Game class, which is a base class for different mini-games 
 * such as TicTacToe, CodeGuesser, and BlackJack. Each game has its own implementation for starting the game and 
 * other game-specific functionality.
 */

#ifndef MINIGAMES_H
#define MINIGAMES_H

#include "../lib/toolkit.h"
#include "../lib/dependencies.h"
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <iomanip>
#include <chrono>
#include <algorithm>

/*!
 * @class Game
 * @brief Abstract base class for mini-games.
 * @details The Game class provides a common interface for all mini-games, enforcing the implementation 
 * of the start method and providing a way to retrieve the game's name.
 */
class Game
{
public:
    /*!
     * @brief Starts the game.
     * @details This is a pure virtual function that must be implemented by any derived class.
     * @return True if the game was completed successfully, otherwise false.
     */
    virtual bool start() = 0;

    /*!
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~Game() {}

    /*!
     * @brief Gets the name of the game.
     * @return A string representing the name of the game.
     */
    virtual std::string getGameName() = 0;
};

/*!
 * @class TicTacToe
 * @brief Implements the TicTacToe mini-game.
 * @details The TicTacToe class allows two players (or a player and the computer) to play a game of TicTacToe.
 */
class TicTacToe : public Game
{
private:
    char squares[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}; //!< The TicTacToe board.

public:
    /*!
     * @brief Prints the TicTacToe board.
     */
    void printBoard();

    /*!
     * @brief Gets the value of a specific square on the board.
     * @param row The row of the square.
     * @param col The column of the square.
     * @return The character at the specified position on the board.
     */
    char getSquare(int row, int col) const;

    /*!
     * @brief Handles the player's move.
     * @param row The row of the square where the player wants to move.
     * @param col The column of the square where the player wants to move.
     */
    void playerMove(int row, int col);

    /*!
     * @brief Handles the computer's move.
     */
    void computerTurn();

    /*!
     * @brief Checks if there is a winner.
     * @return True if there is a winner, otherwise false.
     */
    bool checkForWin();

    /*!
     * @brief Starts the TicTacToe game.
     * @return True if the game was completed successfully, otherwise false.
     */
    bool start() override;

    bool handlePlayerTurn();

    bool getPlayerMove(int &row, int &col);

    bool isValidMove(int row, int col);

    void makeMove(int row, int col, char symbol);

    bool isGameOver(int moveCount);

    bool processComputerTurn();

    void setBoard(char newBoard[3][3]);

    void delayTurn();


        /*!
         * @brief Gets the name of the game.
         * @return A string representing the name of the game.
         */
    std::string getGameName() override;
};

/*!
 * @class CodeGuesser
 * @brief Implements the CodeGuesser mini-game.
 * @details The CodeGuesser class challenges the player to guess a secret code, which is a randomly selected word.
 */
class CodeGuesser : public Game
{
private:
    std::vector<std::string> words; //!< List of possible secret words.
    std::vector<std::string> guesses; //!< List of player guesses.
    int index; //!< Index of the current secret word.

    /*!
     * @brief Generates a random index within a given range.
     * @param size The size of the range.
     * @return A random index within the range.
     */
    static int generateRandomIndex(size_t size);

public:
    /*!
     * @brief Constructor for the CodeGuesser game.
     * @details Initializes the list of possible words and sets up the game.
     */
    CodeGuesser();

    /*!
     * @brief Starts the CodeGuesser game.
     * @return True if the game was completed successfully, otherwise false.
     */
    bool start() override;

    /*!
     * @brief Adds a guess to the list of guesses.
     * @return True if the guess was added successfully, otherwise false.
     */
    bool addGuess();

    /*!
     * @brief Prints all the player's guesses.
     */
    void printGuesses();

    /*!
     * @brief Prints all possible words.
     */
    void printWords();

    /*!
     * @brief Gets the length of the secret word.
     * @return The length of the current secret word.
     */
    int getWordLength() const;

    /*!
     * @brief Gets the number of guesses made by the player.
     * @return The number of guesses made by the player.
     */
    int getGuessCount() const;

    /*!
     * @brief Gets the last guess made by the player.
     * @return The last guess made by the player.
     */
    std::string getLastGuess() const;

    /*!
     * @brief Gets the name of the game.
     * @return A string representing the name of the game.
     */
    std::string getGameName() override;
};

/*!
 * @class BlackJack
 * @brief Implements the BlackJack mini-game.
 * @details The BlackJack class allows the player to play a simple version of the BlackJack card game against a dealer.
 */
class BlackJack : public Game
{
private:
    std::vector<int> cards; //!< Deck of cards for the game.
    int dealer[2]; //!< Dealer's hand.
    std::vector<int> playersCards; //!< Player's hand.
    int bid; //!< The player's current bid.

    /*!
     * @brief Evaluates the player's hand.
     * @param hit Indicates if the player has chosen to hit or stand.
     * @return The result of the evaluation.
     */
    int evaluate(bool hit);

    /*!
     * @brief Initializes the deck of cards.
     */
    void initDecks();

    /*!
     * @brief Sets up a new game of BlackJack.
     */
    void newGame();

    /*!
     * @brief Displays the current state of the game.
     * @param printAll Indicates whether to print all details or just the player's perspective.
     */
    void displayState(bool printAll);

public:
    /*!
     * @brief Constructor for the BlackJack game.
     * @details Initializes the game with default settings.
     */
    BlackJack();

    /*!
     * @brief Starts the BlackJack game.
     * @return True if the game was completed successfully, otherwise false.
     */
    bool start() override;

    /*!
     * @brief Gets the name of the game.
     * @return A string representing the name of the game.
     */
    std::string getGameName() override;
};

#endif // MINIGAMES_H