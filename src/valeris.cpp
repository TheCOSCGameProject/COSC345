#include "../lib/combat.h"
// #include "../helper/minigames.cpp"
#include "../lib/player.h"
#include "../lib/toolkit.h"
#include "../lib/room.h"
#include "../lib/dungeon.h"
#include "../lib/menu.h"

int main()
{
  int j;
  bool running = true;

  int delayTime = 0;
  std::string color = "\033[36m";

#ifdef _WIN32
  SetConsoleSize(800, 600);
#else
  SetTerminalSize(50, 100);
#endif
  while (running)
  {
    Displayj();
    j = readInt();

    switch (j)
    {
    case 1:
      clear(10);
      displayIntro(delayTime, color);
      StartGame();
      break;
    case 2:
      clear(10);
      LoadSavedGame();
      break;
    case 3:
      clear(11);
      DisplayInstructionsText();
      break;
    case 4:
      clear(10);
      Accessiblity(delayTime, color);
      break;
    case 5:
      std::cout << "Exiting Game. We hope you enjoyed the Game Play." << std::endl;
      running = false;
      break;
    default:
      std::cout << "Error: An invalid choice has been entered please try again." << std::endl;
      delay(2000);
      clear(12);
      break;
    }

    std::cout << std::endl;
  }

  return 0;
}
