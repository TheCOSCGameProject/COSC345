#include <iostream>
#include "../lib/dependencies.h"
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>  

using namespace std;

#ifdef _WIN32
#include <windows.h>

void SetConsoleSize(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    MoveWindow(console, r.left, r.top, width, height, TRUE);

    SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_SIZEBOX);
}

#else
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

void SetTerminalSize(int height, int width)
{
    std::cout << "\e[8;" << height << ";" << width << "t";
}

#endif


void delay(int milliseconds)
{
    auto start = std::chrono::high_resolution_clock::now();
    while (std::chrono::high_resolution_clock::now() - start < std::chrono::milliseconds(milliseconds))
    {
        
    }
}

void typePrint(std::string content, int delayTime = 15, std::string color = "\033[36m")
{
    std::string token;
    std::stringstream ss(content);
    std::vector<std::string> tokens;

    while (getline(ss, token, '@'))
    {
        tokens.push_back(token);
    }

    for (std::string &text : tokens)
    {
        for (char c : text)
        {
            std::cout << color << c << std::flush;
            delay(delayTime);
        }
    }
    std::cout << "\033[0m"; 
}

std::string getFileContent(std::string fileName)
{
    std::ifstream file(fileName);
    std::string str;
    std::string file_contents;
    while (std::getline(file, str))
    {
        file_contents += str;
        file_contents.push_back('\n');
    }
    return file_contents;
}

std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

void displayIntro(int delayTime, std::string color) {
    string intro = R"(
The Butlerian Jihad, also known as the Great Revolt, was a monumental crusade against computers, 
thinking machines, and conscious robots. It began in 201 BG and concluded in 108 BG, marking a pivotal period in history.@

During this time, few dared to oppose the Jihad. However, a select number of families with significant 
investments in thinking machines resisted their total destruction. The most prominent of these was House Valeris, 
responsible for the construction of over 45% of the thinking machines in the universe.@

As the Jihad concluded, those who opposed it were relentlessly hunted down and executed. 
Resistance was fierce but ultimately futile. Yet, rumours persist that members of House Valeris survived, 
and with them, the thinking machines...@

___________.__             ___________.__    .__        __   .__                    _____                .__    .__                      
\__    ___/|  |__   ____   \__    ___/|  |__ |__| ____ |  | _|__| ____    ____     /     \ _____    ____ |  |__ |__| ____   ____   ______
  |    |   |  |  \_/ __ \    |    |   |  |  \|  |/    \|  |/ /  |/    \  / ___\   /  \ /  \\__  \ _/ ___\|  |  \|  |/    \_/ __ \ /  ___/
  |    |   |   Y  \  ___/    |    |   |   Y  \  |   |  \    <|  |   |  \/ /_/  > /    Y    \/ __ \\  \___|   Y  \  |   |  \  ___/ \___ \ 
  |____|   |___|  /\___  >   |____|   |___|  /__|___|  /__|_ \__|___|  /\___  /  \____|__  (____  /\___  >___|  /__|___|  /\___  >____  >
                \/     \/                  \/        \/     \/       \//_____/           \/     \/     \/     \/        \/     \/     \/@

)";
    typePrint(intro, delayTime, color);  
}

void Displayj() {
    cout << "==========================================================" << endl;
    cout << setw(15) << " " << "VALERIS GAME MENU" << endl;  
    cout << "==========================================================" << endl;
    cout << "1. Start New Game" << endl;
    cout << "2. Load Saved Game" << endl;
    cout << "3. Instructions" << endl;
    cout << "4. Accessibility" << endl;
    cout << "5. Exit" << endl;
    cout << "==========================================================" << endl;
    cout << "Enter your choice (1-5): ";
}
