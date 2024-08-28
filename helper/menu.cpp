#include "../lib/toolkit.h"
#include "../lib/dependencies.h"
#include "../lib/dungeon.h"
#include "../lib/menu.h"
#include "../lib/valerisgame.h"
#include <iomanip>

void displayIntro(int delayTime, std::string color)
{
    std::vector<std::string> intro = split(getFileContent("../reasources/intro.txt"), '@');

    for (int i = 0; i < 3; i++)
    {
        typePrint(intro[i], delayTime, color);
        std::cout << std::endl;
    }
    typePrint(intro[intro.size() - 1], 0, color);
    std::cout << std::endl;
}

void Displayj()
{
    std::cout << "\033[37m" << "==========================================================" << std::endl;
    std::cout << std::setw(15) << " " << "VALERIS GAME MENU" << std::endl;
    std::cout << "==========================================================" << std::endl;
    std::cout << "1. Start New Game" << std::endl;
    std::cout << "2. Load Saved Game" << std::endl;
    std::cout << "3. Instructions" << std::endl;
    std::cout << "4. Accessibility" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "==========================================================" << std::endl;
}

void StartGame()
{
    ValerisGame valerisGame;
    valerisGame.start();
}

void LoadSavedGame()
{
    std::cout << "\033[37m" << "Loading game..." << std::endl;
}

void DisplayInstructionsText()
{
    std::string instructions = R"(
Instructions:
1. Use the N, S, W, E keys to move your character.
2. Fight enemies with ___
3. Collect items to improve your chances of survival.
4. Play minigames with ___
5. Defeat bosses to progress to the next level.
)";
    std::cout << "\033[37m" << instructions << std::endl;

    waitForEnter();
    clear(8);
}

void Accessiblity(int &delayTime, std::string &color)
{
    std::cout << "\033[37m" << "Accessibility Options:" << std::endl;
    std::cout << "1. Text Speed (current: " << delayTime << " ms)" << std::endl;
    std::cout << "2. Text Color (current: " << color << "color" << "\033[37m" << ")" << std::endl;
    std::cout << "3. Return to Main Menu" << std::endl;

    int j = readInt();
    int colorChoice;

    switch (j)
    {
    case 1:
        std::cout << "Enter new text speed in milliseconds: ";
        delayTime = readInt();
        clear(6);
        Accessiblity(delayTime, color); // Recursive call
        break;

    case 2:
        std::cout << "Select text color:" << std::endl;
        std::cout << "1. Green" << std::endl;
        std::cout << "2. Blue" << std::endl;
        std::cout << "3. Red" << std::endl;
        std::cout << "4. Yellow" << std::endl;
        std::cout << "5. Default Cyan" << std::endl;
        colorChoice = readInt();
        switch (colorChoice)
        {
        case 1:
            color = "\033[32m";
            break;
        case 2:
            color = "\033[34m";
            break;
        case 3:
            color = "\033[31m";
            break;
        case 4:
            color = "\033[33m";
            break;
        case 5:
            color = "\033[36m";
            break;
        default:
            std::cout << "\033[91m" << "Invalid choice. Keeping current color." << "\033[37m" << std::endl;
            delay(2000);
            clear(1);
            break;
        }
        clear(12);
        Accessiblity(delayTime, color); // Recursive call
        break;

    case 3:
        clear(6);
        return;

    default:
        std::cout << "\033[91m" << "Invalid choice. Returning to Accessibility Options." << "\033[37m" << std::endl;
        delay(2000);
        clear(6);
        Accessiblity(delayTime, color); // Recursive call
        break;
    }
}
