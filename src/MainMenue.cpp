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
