#include "../lib/toolkit.h"
#include "../lib/dependencies.h"
#include "../lib/minigames.h"
/* TicTacToe */

void TicTacToe::printBoard()
{
    std::string arr[2] = {"\n   |   |   ", "\n___|___|___"};

    std::string top = std::string("\n ") + squares[0][0] + " | " + squares[0][1] + " | " + squares[0][2] + " ";
    std::string middle = std::string("\n ") + squares[1][0] + " | " + squares[1][1] + " | " + squares[1][2] + " ";
    std::string bottom = std::string("\n ") + squares[2][0] + " | " + squares[2][1] + " | " + squares[2][2] + " ";

    std::cout << arr[0] + top + arr[1] + arr[0] + middle + arr[1] + arr[0] + bottom + arr[0] << std::endl;
    std::cout.flush();
}

char TicTacToe::getSquare(int row, int col) const
{
    return squares[row][col];
}

void TicTacToe::playerMove(int row, int col)
{
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && squares[row][col] == ' ')
    {
        squares[row][col] = 'X';
    }
}

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

void TicTacToe::start()
{
    printBoard();
    int row, col;
    int count = 0;
    while (true)
    {
        std::cout << "\nEnter your move (row and column separated by a space, e.g., '1 1'): ";
        std::cin >> row >> col;

        if (std::cin.fail() || row < 1 || row > 3 || col < 1 || col > 3)
        {
            std::cin.clear();            // clear the error flag on cin
            std::cin.ignore(1000, '\n'); // discard invalid input
            std::cout << "Invalid input. Please enter numbers between 1 and 3." << std::endl;
            continue;
        }

        if (squares[row - 1][col - 1] != ' ')
        {
            std::cout << "That square is already taken. Please choose another one." << std::endl;
            continue;
        }

        squares[row - 1][col - 1] = 'X';
        clear(12);
        printBoard();
        if (checkForWin())
        {
            std::cout << "You win!" << std::endl;
            break;
        }
        count++;
        if (count == 9)
        {
            std::cout << "Draw!" << std::endl;
            break;
        }

#ifdef _WIN32
        Sleep(1); // Sleep for 1 second
#else
        sleep(1);
#endif

        computerTurn();
        if (checkForWin())
        {
            std::cout << "You lose!" << std::endl;
            break;
        }
        count++;
        if (count == 9)
        {
            std::cout << "Draw!" << std::endl;
            break;
        }
    }
}

/** CodeGuesser game */

int CodeGuesser::generateRandomIndex(size_t size)
{
    if (size == 0)
    {
        throw std::invalid_argument("Size of words vector must be greater than 0");
    }
    std::random_device rd;                            // Seed
    std::mt19937 gen(rd());                           // Mersenne Twister engine
    std::uniform_int_distribution<> dis(0, (int)size - 1); // Distribution range
    return dis(gen);
}

CodeGuesser::CodeGuesser()
    : words(split(getFileContent("../reasources/cg_words.txt"), '\n')),
      index(generateRandomIndex(words.size())) {}

void CodeGuesser::start()
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
    }
    else
    {
        std::cout << "Too many failed attempts! Please restart";
    }
}

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

void CodeGuesser::printGuesses()
{
    for (const auto &guess : guesses)
    {
        std::cout << guess << "\n";
    }
    std::cout << +"\npasscode: ";
}

void CodeGuesser::printWords()
{
    for (int i = 0; i < (int)words.size(); i++)
    {
        std::cout << words.at(i) + "\n";
    }
}

int CodeGuesser::getWordLength() const
{
    return 5; // For testing...
}

int CodeGuesser::getGuessCount() const
{
    return (int)guesses.size();
}

std::string CodeGuesser::getLastGuess() const
{
    return guesses.empty() ? "" : guesses.back();
}

BlackJack::BlackJack()
{
    newGame();
}

void BlackJack::start()
{
    int maxRounds = generateRandomNumber(3, 15);
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
            for (int i = 0; i < 9; i++)
            {
                std::cout << "\033[A\033[K" << std::flush;
                // delay(1000);
            }
            wasHit = true;
            playersCards.push_back(cards.back());
            cards.pop_back();
        }
        int eval = evaluate(wasHit);

        if (eval == -1)
        {
            if (!wasHit)
            {
                for (int i = 0; i < 9; i++)
                {
                    std::cout << "\033[A\033[K" << std::flush;
                    // delay(1000);
                }
            }
            rounds++;
            displayState(true);
            std::cout << "Round " << rounds << ": Round lost.\n";
            std::cout << "Rounds left: " << (maxRounds - rounds) << std::endl;
            std::cout << "Total rounds won: " << totalWins << std::endl;
            waitForEnter();
            for (int i = 0; i < 11; i++)
            {
                std::cout << "\033[A\033[K" << std::flush;
                // delay(1000);
            }
            initDecks();
        }
        else if (eval == 1)
        {
            if (!wasHit)
            {
                for (int i = 0; i < 9; i++)
                {
                    std::cout << "\033[A\033[K" << std::flush;
                    // delay(1000);
                }
            }
            rounds++;
            totalWins++;
            displayState(true);
            std::cout << "Round " << rounds << ": Round won.\n";
            std::cout << "Rounds left: " << (maxRounds - rounds) << std::endl;
            std::cout << "Total rounds won: " << totalWins << std::endl;
            waitForEnter();
            for (int i = 0; i < 11; i++)
            {
                std::cout << "\033[A\033[K" << std::flush;
                // delay(1000);
            }
            initDecks();
        }
    }

    if (totalWins >= maxRounds / 2)
    {
        std::cout << "Game Over You Win!" << std::endl;
    }
    else
    {
        std::cout << "Game Over You Loose!" << std::endl;
    }
}

void BlackJack::waitForEnter()
{
    std::cout << "Press Enter to continue..." << std::endl;
    system("stty -echo -icanon");

    std::cin.ignore(); // Waits for the user to press Ente
    std::cin.get();

    system("stty echo icanon");
}

int BlackJack::evaluate(bool hit)
{
    int dealerTotal = dealer[0] + dealer[1];
    int playerTotal = 0;
    for (int i = 0; i < (int)playersCards.size(); i++)
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
    unsigned seed = (int)std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine(seed);
    std::shuffle(std::begin(cards), std::end(cards), rng);

    initDecks();
}

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
