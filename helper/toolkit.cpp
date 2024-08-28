// toolkit.cpp
#define NOMINMAX
#include "../lib/toolkit.h"
#include "../lib/dependencies.h"

#ifdef _WIN32
void SetConsoleSize(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
    SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_SIZEBOX);
}
#else
void SetTerminalSize(int height, int width)
{
    std::cout << "\033[8;" << height << ";" << width << "t";
}
#endif

void delay(int milliseconds)
{
    auto start = std::chrono::high_resolution_clock::now();
    while (std::chrono::high_resolution_clock::now() - start < std::chrono::milliseconds(milliseconds))
    {
        // Busy-waiting loop to create a delay
    }
}

void disableInput()
{
#ifdef _WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hStdin, 0);
#else
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON; // Disable canonical mode
    t.c_lflag &= ~ECHO;   // Disable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
#endif
}

void enableInput()
{
#ifdef _WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hStdin, ENABLE_ECHO_INPUT | ENABLE_INSERT_MODE | ENABLE_LINE_INPUT | ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE | ENABLE_WINDOW_INPUT | ENABLE_VIRTUAL_TERMINAL_INPUT);
#else
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ICANON; // Enable canonical mode
    t.c_lflag |= ECHO;   // Enable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    tcflush(STDIN_FILENO, TCIFLUSH);
#endif
}

void typePrint(std::string content, int delayTime = 15, std::string color = "\033[36m")
{

    for (char c : content)
    {
        std::cout << color << c << std::flush;
        delay(delayTime);
    }
    std::cout << "\033[37m";
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

void clear(int limit)
{
    for (int i = 0; i < limit; i++)
    {
        std::cout << "\033[A\033[K";
        std::cout.flush();
        // delay(300);
    }
}

std::string getUserInputLine()
{
    std::string input;
    std::getline(std::cin, input);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character
    return input;
}

std::string getUserInputToken()
{
    std::string input;
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character
    return input;
}

int generateRandomNumber(int low, int high)
{
    // Create a random device and use it to seed the random number generator
    std::random_device rd;
    std::mt19937 rng(rd());

    // Create a uniform integer distribution between low and high inclusive
    std::uniform_int_distribution<int> dist(low, high);

    // Generate and return the random number
    return dist(rng);
}

int stringToInt(const std::string &str)
{
    try
    {
        // Attempt to convert the string to an integer
        return std::stoi(str);
    }
    catch (const std::invalid_argument &e)
    {
        // Handle the case where the input is not a valid integer
        std::cerr << "Invalid argument: " + str << e.what() << std::endl;
        return 0; // or throw an exception, or handle as needed
    }
    catch (const std::out_of_range &e)
    {
        // Handle the case where the integer is out of range
        std::cerr << "Out of range: " << e.what() << std::endl;
        return 0; // or throw an exception, or handle as needed
    }
}

std::string repeatString(const std::string &str, int count)
{
    if (count <= 0)
        return ""; // Return an empty string for non-positive count

    std::string result;
    result.reserve(str.size() * count); // Optimize memory allocation

    for (int i = 0; i < count; ++i)
    {
        result += str;
    }
    return result;
}

std::string toLowerCase(const std::string &str)
{
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return lowerStr;
}

int readInt()
{
    int value;
    while (true)
    {
        try
        {
            std::cout << "Enter your choice: " << std::flush;
            std::cout << "Enter your choice: " << std::flush;

            std::cin >> value;

            // Check if the input operation failed (non-integer input)
            if (std::cin.fail())
            {
                disableInput();
                throw std::runtime_error("Invalid input; please enter a valid integer.");
            }

            // Clear any remaining input from the buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // If everything is fine, return the value
            return value;
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            delay(2000);
            // Clear the error flags
            std::cin.clear();

            // Discard invalid input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            clear(2);
            enableInput();
        }
    }
}

void waitForEnter()
{
    std::cout << "Press Enter to continue..." << std::endl;
    system("stty -echo -icanon");

    std::cin.ignore(); // Waits for the user to press Ente
    std::cin.get();

    system("stty echo icanon");
}

std::string toUpperCase(const std::string &input)
{
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}
