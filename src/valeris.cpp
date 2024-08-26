// #include "../helper/combat.cpp"
// #include "../helper/minigames.cpp"
#include "../lib/player.h"
#include "../lib/toolkit.h"

int main()
{
#if defined(_WIN32) || defined(_WIN64)
  SetConsoleSize(800, 600);
#else
  SetTerminalSize(24, 80);
#endif

  // typePrint(getFileContent("../reasources/intro.txt"));
  // combatV1(100, 100, 2000);
  // TicTacToe game;
  // game.startGame();

  // CodeGuesser ggame;
  // ggame.start();

  Player player;

  return 0;
}