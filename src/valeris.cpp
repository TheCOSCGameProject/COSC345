#include "../lib/combat.h"
// #include "../helper/minigames.cpp"
#include "../lib/player.h"
#include "../lib/toolkit.h"
#include "../lib/room.h"
#include "../lib/dungeon.h"

int main()
{
#if defined(_WIN32) || defined(_WIN64)
  SetConsoleSize(800, 600);
#else
  SetTerminalSize(24, 80);
#endif
  // mini game testing ---------------------------------------------
  // typePrint(getFileContent("../reasources/intro.txt"));
  // combatV1(100, 100, 2000);
  // TicTacToe game;
  // game.startGame();

  // CodeGuesser ggame;
  // ggame.start();

  // Player player;

  // Room testing ---------------------------------------------
  // Room room;
  // room.roomContent.displayContent();

  // Room room2;
  // room2.roomContent.displayContent();

  // if (room2.roomContent.getRoomType() == 1)
  // {
  //   NPC &npc = room2.roomContent.getNPC();
  //   npc.gamblingGame->start();
  // }

  // Dungeon testing ---------------------------------------------
  Dungeon dungeon;
  int numRooms = 10;
  Room *currentRoom = dungeon.generateFloor(numRooms);

  dungeon.traverseAndPrint(currentRoom); // Checking

  // BlackJack blackjack;

  return 0;
}
