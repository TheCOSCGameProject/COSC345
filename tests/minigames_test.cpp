#include "../helper/minigames.cpp"
#include "custom_test_framework.h"
#include "cassert"

void testTicTacToeInitialization()
{
    TicTacToe game;
    // Test that the board is initially empty
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ASSERT_EQUAL(' ', game.getSquare(i, j));
        }
    }
}

void testTicTacToePlayerMove()
{
    TicTacToe game;
    game.playerMove(0, 0);
    ASSERT_EQUAL('X', game.getSquare(0, 0));
}

void testTicTacToeComputerTurn()
{
    TicTacToe game;
    game.computerTurn();
    // Check that the computer has made a move (one square should be 'O')
    bool computerMoved = false;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (game.getSquare(i, j) == 'O')
            {
                computerMoved = true;
                break;
            }
        }
        if (computerMoved)
            break;
    }
    ASSERT(computerMoved);
}

void testTicTacToeCheckForWin()
{
    TicTacToe game;
    // Test horizontal win
    game.playerMove(0, 0);
    game.playerMove(0, 1);
    game.playerMove(0, 2);
    ASSERT(game.checkForWin());

    // Reset and test vertical win
    game = TicTacToe();
    game.playerMove(0, 0);
    game.playerMove(1, 0);
    game.playerMove(2, 0);
    ASSERT(game.checkForWin());

    // Reset and test diagonal win
    game = TicTacToe();
    game.playerMove(0, 0);
    game.playerMove(1, 1);
    game.playerMove(2, 2);
    ASSERT(game.checkForWin());
}

int main()
{
    TestFramework framework("minigames_test_results.xml");

    framework.addTest("TicTacToe Initialization", testTicTacToeInitialization);
    framework.addTest("TicTacToe Player Move", testTicTacToePlayerMove);
    framework.addTest("TicTacToe Computer Turn", testTicTacToeComputerTurn);
    framework.addTest("TicTacToe Check For Win", testTicTacToeCheckForWin);

    framework.run();

    return 0;
}

// g++ -std=c++11 -o run_tests.exe tests/minigames_test.cpp
//./run_tests.exe