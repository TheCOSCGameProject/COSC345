/*!
@file minigames.cpp
@brief Implementation of the TicTacToe, CodeGuesser, and BlackJack games.
@details This file contains the implementation of three mini-games: TicTacToe, CodeGuesser, and BlackJack.
Each game has methods for setting up the game, handling player input, and determining the outcome.
*/

#include "../lib/toolkit.h"
#include "../lib/dependencies.h"
#include "../lib/minigames.h"

/* TicTacToe */

/*!
@brief Get the name of the TicTacToe game.
@return A string representing the name of the game.
*/


std::string TicTacToe::getGameName()
{
    return "TicTacToe";
}

/*!
@brief Print the current state of the TicTacToe board.
@details Displays the current state of the TicTacToe board, showing the positions of 'X', 'O', and empty spaces.
*/
void TicTacToe::printBoard()
{
    std::string arr[2] = {"\n   |   |   ", "\n___|___|___"};

    std::string top = std::string("\n ") + squares[0][0] + " | " + squares[0][1] + " | " + squares[0][2] + " ";
    std::string middle = std::string("\n ") + squares[1][0] + " | " + squares[1][1] + " | " + squares[1][2] + " ";
    std::string bottom = std::string("\n ") + squares[2][0] + " | " + squares[2][1] + " | " + squares[2][2] + " ";

    std::cout << arr[0] + top + arr[1] + arr[0] + middle + arr[1] + arr[0] + bottom + arr[0] << std::endl;
    std::cout.flush();
}

/*!
@brief Get the value at a specific square on the TicTacToe board.
@param row The row of the square (0-indexed).
@param col The column of the square (0-indexed).
@return The character ('X', 'O', or ' ') at the specified square.
*/
char TicTacToe::getSquare(int row, int col) const
{
    return squares[row][col];
}

/*!
@brief Handle the player's move in TicTacToe.
@param row The row where the player wants to place their 'X' (1-indexed).
@param col The column where the player wants to place their 'X' (1-indexed).
*/
void TicTacToe::playerMove(int row, int col)
{
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && squares[row][col] == ' ')
    {
        squares[row][col] = 'X';
    }
}

/*!
@brief Handle the computer's turn in TicTacToe.
@details The computer randomly selects an empty square to place its 'O'.
*/
void TicTacToe::computerTurn()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    while (true)
    {
        int row = std::rand() % 3;
        int col = std::rand() % 3;

        if (squares[row][col] == ' ')
        {
            squares[row][col] = 'O';
            break;
        }
    }
    std::cout << "\n\n";
    clear(12);
    printBoard();
}

/*!
@brief Check if there is a winner in TicTacToe.
@return True if there is a winner, false otherwise.
@details Checks all rows, columns, and diagonals for three matching symbols ('X' or 'O').
*/
bool TicTacToe::checkForWin()
{
    bool wasWin = false;
    // Horizontal Check
    for (int i = 0; i < 3; i++)
    {
        if (squares[i][0] == squares[i][1] && squares[i][0] == squares[i][2] && squares[i][0] != ' ')
        {
            wasWin = true;
        }
    }

    // Vertical check
    for (int i = 0; i < 3; i++)
    {
        if (squares[0][i] == squares[1][i] && squares[0][i] == squares[2][i] && squares[0][i] != ' ')
        {
            wasWin = true;
        }
    }

    // Diagonal Check
    if (squares[0][0] == squares[1][1] && squares[0][0] == squares[2][2] && squares[0][0] != ' ')
    {
        wasWin = true;
    }
    if (squares[0][2] == squares[1][1] && squares[0][2] == squares[2][0] && squares[0][2] != ' ')
    {
        wasWin = true;
    }
    return wasWin;
}

bool TicTacToe::start()
{   
    printBoard();
    int moveCount = 0;

    while (true)
    {
        // Player's turn
        if (!handlePlayerTurn())
            continue;

        moveCount++;
        if (isGameOver(moveCount))
            return true;

        // Computer's turn
        delayTurn(); // Optional: add delay to make gameplay smoother
        if (!processComputerTurn())
            return false;

        moveCount++;
        if (isGameOver(moveCount))
            return true;
    }
}

void TicTacToe::setBoard(char newBoard[3][3])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            squares[i][j] = newBoard[i][j]; // Copy each element from newBoard to squares
        }
    }
}

// std::array<std::array<char, 3>, 3> TicTacToe::getSquares()
// {
//         // for (int i = 0; i < 3; ++i)
//         // {
//         //     for (int j = 0; j < 3; ++j)
//         //     {
//         //         boardCopy[i][j] = squares[i][j];
//         //     }
//         // }
//     return squares;
// }

bool TicTacToe::handlePlayerTurn()
{
    int row, col;
    if (!getPlayerMove(row, col))
        return false; // Invalid move, loop back for a valid one

    makeMove(row, col, 'X'); // Player move
    clear(12);               // Clear console
    printBoard();

    return true;
}

bool TicTacToe::getPlayerMove(int &row, int &col)
{
    std::cout << "\nEnter your move (row and column separated by a space, e.g., '1 1'): ";
    std::cin >> row >> col;

    if (std::cin.fail() || !isValidMove(row, col))
    {
        std::cin.clear();            // Clear error flag on cin
        std::cin.ignore(1000, '\n'); // Discard invalid input
        std::cout << "Invalid input. Please enter numbers between 1 and 3." << std::endl;
        return false;
    }

    if (squares[row - 1][col - 1] != ' ')
    {
        std::cout << "That square is already taken. Please choose another one." << std::endl;
        return false;
    }

    return true;
}

bool TicTacToe::isValidMove(int row, int col)
{
    return row >= 1 && row <= 3 && col >= 1 && col <= 3;
}

void TicTacToe::makeMove(int row, int col, char symbol)
{
    squares[row - 1][col - 1] = symbol;
}

bool TicTacToe::isGameOver(int moveCount)
{
    if (checkForWin())
    {
        std::cout << (moveCount % 2 == 1 ? "You win!" : "You lose!") << std::endl;
        delay(3000);
        clear(11);
        return true;
    }

    if (moveCount == 9)
    {
        std::cout << "Draw!" << std::endl;
        delay(3000);
        clear(11);
        return true;
    }

    return false;
}

bool TicTacToe::processComputerTurn()
{
    computerTurn(); // Computer makes its move

    clear(12);    // Clear console
    printBoard(); // Show updated board

    if (checkForWin())
    {
        std::cout << "You lose!" << std::endl;
        delay(3000);
        clear(11);
        return false;
    }

    return true;
}

void TicTacToe::delayTurn()
{
#ifdef _WIN32
    Sleep(1); // Sleep for 1 second on Windows
#else
    sleep(1);
#endif
}

/** CodeGuesser game */

/*!
@brief Get the name of the CodeGuesser game.
@return A string representing the name of the game.
*/
std::string CodeGuesser::getGameName()
{
    return "Code Guesser";
}

/*!
@brief Generate a random index for selecting a word.
@param size The size of the list of words.
@return A random index within the range of the word list.
@throws std::invalid_argument if the size is 0.
*/
int CodeGuesser::generateRandomIndex(size_t size)
{
    if (size == 0)
    {
        throw std::invalid_argument("Size of words vector must be greater than 0");
    }
    std::random_device rd;                            // Seed
    std::mt19937 gen(rd());                           // Mersenne Twister engine
    std::uniform_int_distribution<> dis(0, size - 1); // Distribution range
    return dis(gen);
}

/*!
@brief Constructor for the CodeGuesser class.
@details Initializes the word list and randomly selects one word for the game.
*/
CodeGuesser::CodeGuesser()
    : words(split(getFileContent("../reasources/cg_words.txt"), '\n')),
      index(generateRandomIndex(words.size())) {}

/*!
@brief Start the CodeGuesser game.
@return True if the player successfully guesses the code, false otherwise.
@details The player has five attempts to guess a five-letter passcode.
*/
bool CodeGuesser::start()
{
    bool success = false;
    int count = 0;
    while (count < 5)
    {
        std::cout << "Please enter the five lettered passcode: " + std::to_string(5 - count) + " guesses remaining\n\n";
        printGuesses();

        if (addGuess())
        {
            success = true;
            break;
        }
        clear(4 + count);
        count++;
    }

    if (success)
    {
        std::cout << "Passcode Accepted!";
        return true;
    }
    else
    {
        std::cout << "Too many failed attempts! Please restart";
        return false;
    }
}

/*!
@brief Add a guess and check it against the secret passcode.
@return True if the guess matches the passcode, false otherwise.
@details Colors the guess based on correctness (green for correct letters in the correct position, yellow for correct letters in the wrong position).
*/
bool CodeGuesser::addGuess()
{
    // Yellow, Green, Reset
    std::string colorCodes[] = {"\033[43m", "\033[42m", "\033[0m"};
    std::string guess, coloredGuess;
    std::cin >> guess;

    bool correct = true;

    for (int i = 0; i < 5; i++)
    {
        if (words.at(index).at(i) == guess.at(i))
        {
            coloredGuess.append(colorCodes[1] + guess.substr(i, 1) + colorCodes[2] + " ");
            continue;
        }
        else
        {
            correct = false;
        }
        bool contains = false;
        for (int j = 0; j < 5; j++)
        {
            if (words.at(index).at(j) == guess.at(i))
            {
                contains = true;
                break;
            }
        }
        if (contains)
        {
            coloredGuess.append(colorCodes[0] + guess.substr(i, 1) + colorCodes[2] + " ");
        }
        else
        {
            coloredGuess.append(guess.substr(i, 1) + " ");
        }
    }
    guesses.push_back(coloredGuess);
    return correct;
}

/*!
@brief Print all the guesses made by the player so far.
*/
void CodeGuesser::printGuesses()
{
    for (const auto &guess : guesses)
    {
        std::cout << guess << "\n";
    }
    std::cout << +"\npasscode: ";
}

/*!
@brief Print all the possible words (for debugging or testing).
*/
void CodeGuesser::printWords()
{
    for (int i = 0; i < words.size(); i++)
    {
        std::cout << words.at(i) + "\n";
    }
}

/*!
@brief Get the length of the word (always 5 in this game).
@return The length of the word (5).
*/
int CodeGuesser::getWordLength() const
{
    return 5; // For testing...
}

/*!
@brief Get the number of guesses made by the player.
@return The number of guesses as an integer.
*/
int CodeGuesser::getGuessCount() const
{
    return guesses.size();
}

/*!
@brief Get the last guess made by the player.
@return The last guess as a string.
*/
std::string CodeGuesser::getLastGuess() const
{
    return guesses.empty() ? "" : guesses.back();
}

/** BlackJack game */

/*!
@brief Constructor for the BlackJack class.
@details Initializes a new game of BlackJack by shuffling the deck and dealing cards to the player and dealer.
*/
BlackJack::BlackJack()


: bid(0)
{
    newGame();


}

/*!
@brief Get the name of the BlackJack game.
@return A string representing the name of the game.
*/
std::string BlackJack::getGameName()
{
    return "Black Jack";
}

/*!
@brief Start the BlackJack game.
@return True if the player wins, false otherwise.
@details The player plays against the dealer, attempting to win the majority of rounds.
*/
bool BlackJack::start()
{
    int maxRounds = 1; // generateRandomNumber(1, 5);
    if (maxRounds % 2 == 0)
    {
        maxRounds++;
    }
    int rounds = 0;
    int totalWins = 0;
    while (rounds < maxRounds)
    {
        displayState(false);
        std::cout << "Hit or Stand?\n";
        std::string hit = getUserInputToken();
        bool wasHit = false;
        if (toLowerCase(hit) == "hit")
        {
            clear(9);
            wasHit = true;
            playersCards.push_back(cards.back());
            cards.pop_back();
        }
        int eval = evaluate(wasHit);

        if (eval == -1)
        {
            if (!wasHit)
            {
                clear(9);
            }
            rounds++;
            displayState(true);
            std::cout << "Round " << rounds << ": Round lost.\n";
            std::cout << "Rounds left: " << (maxRounds - rounds) << std::endl;
            std::cout << "Total rounds won: " << totalWins << std::endl;
            waitForEnter();
            clear(11);
            initDecks();
        }
        else if (eval == 1)
        {
            if (!wasHit)
            {
                clear(9);
            }
            rounds++;
            totalWins++;
            displayState(true);
            std::cout << "Round " << rounds << ": Round won.\n";
            std::cout << "Rounds left: " << (maxRounds - rounds) << std::endl;
            std::cout << "Total rounds won: " << totalWins << std::endl;
            waitForEnter();
            clear(11);
            initDecks();
        }
    }

    if (totalWins >= maxRounds / 2)
    {
        std::cout << "Game Over You Win!" << std::endl;
        delay(2000);
        clear(1);
        return true;
    }
    else
    {
        std::cout << "Game Over You Lose!" << std::endl;
        delay(2000);
        clear(1);
        return false;
    }
}

/*!
@brief Evaluate the player's hand against the dealer's.
@param hit A boolean indicating if the player chose to hit.
@return An integer indicating the outcome (-1 for loss, 0 for continue, 1 for win).
*/
int BlackJack::evaluate(bool hit)
{
    int dealerTotal = dealer[0] + dealer[1];
    int playerTotal = 0;
    for (int i = 0; i < playersCards.size(); i++)
    {
        playerTotal += playersCards[i];
    }

    if ((!hit && playerTotal < dealerTotal) || playerTotal > 21)
    {
        return -1;
    }
    else if (hit && playerTotal != 21)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*!
@brief Initialize the decks for a new round of BlackJack.
@details Deals two cards to both the player and the dealer.
*/
void BlackJack::initDecks()
{

    dealer[0] = cards.back();
    cards.pop_back();
    dealer[1] = cards.back();
    cards.pop_back();

    playersCards.clear();
    playersCards.push_back(cards.back());
    cards.pop_back();
    playersCards.push_back(cards.back());
    cards.pop_back();
}

/*!
@brief Set up a new game of BlackJack by shuffling the deck and dealing initial cards.
@details Shuffles the deck using the Mersenne Twister engine and deals cards to both the player and the dealer.
*/
void BlackJack::newGame()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            cards.push_back(j);
        }
        for (int j = 0; j < 4; j++)
        {
            cards.push_back(10);
        }
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine(seed);
    std::shuffle(std::begin(cards), std::end(cards), rng);

    initDecks();
}

/*!
@brief Display the current state of the BlackJack game.
@param printAll A boolean indicating whether to show all the dealer's cards.
@details Prints the dealer's and player's cards, and whether the dealer's second card should be hidden.
*/
void BlackJack::displayState(bool printAll)
{
    const int terminalWidth = 40; // Example width, adjust based on your terminal size

    // Repeat character to match terminal width
    std::string line = repeatString("=", terminalWidth);
    std::string dealersSecond = "X";
    if (printAll)
    {
        dealersSecond = std::to_string(dealer[1]);
    }

    // Print dealer's cards
    std::cout << std::setw((terminalWidth - 16) / 2) << "" << "Dealer's Cards\n";
    std::cout << line << "\n";
    std::cout << std::setw((terminalWidth - 4) / 2) << dealer[0] << " " + dealersSecond + "\n\n";

    // Print player's cards
    std::string playerCardsLine;
    for (const auto &card : playersCards)
    {
        playerCardsLine += std::to_string(card) + " ";
    }
    // Trim trailing space
    if (!playerCardsLine.empty())
    {
        playerCardsLine.pop_back();
    }

    std::cout << std::setw((terminalWidth - 16) / 2) << "" << "Player's Cards\n";
    std::cout << line << "\n";
    std::cout << std::setw((terminalWidth - playerCardsLine.length()) / 2 - 1) << "" << playerCardsLine << "\n";
}
