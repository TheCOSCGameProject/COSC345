#ifndef MINIGAMES_H
#define MINIGAMES_H

#include <vector>
#include <string>

class Game
{
public:
    virtual void start() = 0; // Pure virtual function to enforce implementation in derived classes
    virtual ~Game() {}        // Virtual destructor for proper cleanup
};

class TicTacToe : public Game
{
private:
    char squares[3][3];

public:
    TicTacToe(); // Add this constructor declaration
    void printBoard();
    char getSquare(int row, int col) const;
    void playerMove(int row, int col);
    void computerTurn();
    bool checkForWin();
    void start() override;
};

class CodeGuesser : public Game
{
private:
    std::vector<std::string> words;
    std::vector<std::string> guesses;
    int index;

    static int generateRandomIndex(size_t size);

public:
    CodeGuesser();
    void start() override;
    bool addGuess();
    void printGuesses();
    void printWords();
    int getWordLength() const;
    int getGuessCount() const;
    std::string getLastGuess() const;
};

class BlackJack : public Game
{
private:
    std::vector<int> cards;
    int dealer[2];
    std::vector<int> playersCards;
    int bid;

public:
    BlackJack();
    void start() override;
    void waitForEnter();
    int evaluate(bool hit);
    void initDecks();
    void newGame();
    void displayState(bool printAll);
};

#endif // MINIGAMES_H