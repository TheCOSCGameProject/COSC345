/*!
 * @file toolkit.cpp
 * @brief Implements utility functions for the Valeris game.
 * @details This file contains various utility functions used throughout the Valeris game, including console/terminal manipulation, input handling, string processing, and delays.
 */

#define NOMINMAX
#include "../lib/toolkit.h"
#include "../lib/dependencies.h"

#ifdef _WIN32
/*!
 * @brief Sets the console window size on Windows.
 * @param width The desired width of the console window.
 * @param height The desired height of the console window.
 */
// LCOV_EXCL_START
void SetConsoleSize(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
    SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_SIZEBOX);
}
#else
/*!
 * @brief Sets the terminal window size on non-Windows systems.
 * @param height The desired height of the terminal window.
 * @param width The desired width of the terminal window.
 */
void SetTerminalSize(int height, int width)
{
    std::cout << "\033[8;" << height << ";" << width << "t";
}
// LCOV_EXCL_STOP
#endif

/*!
 * @brief Creates a delay for a specified amount of time.
 * @param milliseconds The number of milliseconds to delay.
 * @details This function uses a busy-wait loop to create a delay, which can be used to control the timing of text display or other actions.
 */
void delay(int milliseconds)
{
    auto start = std::chrono::high_resolution_clock::now();
    while (std::chrono::high_resolution_clock::now() - start < std::chrono::milliseconds(milliseconds))
    {
        // Busy-waiting loop to create a delay
    }
}
/*!
 * @brief Disables user input on the console/terminal.
 * @details Disables input features such as echo and canonical mode on both Windows and non-Windows systems.
 */
// LCOV_EXCL_START
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

/*!
 * @brief Enables user input on the console/terminal.
 * @details Restores input features such as echo and canonical mode on both Windows and non-Windows systems.
 */

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
// LCOV_EXCL_STOP
/*!
 * @brief Prints text with a typing effect.
 * @param content The text content to print.
 * @param delayTime The delay between each character in milliseconds. Default is 15 milliseconds.
 * @param color The color code for the text. Default is cyan ("\033[36m").
 * @details This function prints text one character at a time, simulating a typing effect, with customizable delay and color.
 */
void typePrint(const std::string &content, int delayTime, const std::string &color)
{
    for (char c : content)
    {
        std::cout << color << c << std::flush;
        delay(delayTime);
    }
    std::cout << "\033[37m";
}

/*!
 * @brief Reads the content of a file into a string.
 * @param fileName The name of the file to read.
 * @return A string containing the contents of the file.
 */

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
/*!
 * @brief Splits a string into tokens based on a delimiter.
 * @param str The string to split.
 * @param delimiter The character used as the delimiter.
 * @return A vector of strings representing the tokens.
 */
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

/*!
 * @brief Clears a specified number of lines from the console/terminal.
 * @param limit The number of lines to clear.
 * @details This function moves the cursor up and clears the specified number of lines from the console or terminal output.
 */
void clear(int limit)
{
    for (int i = 0; i < limit; i++)
    {
        std::cout << "\033[A\033[K";
        std::cout.flush();
        // delay(300);
    }
}
/*!
 * @brief Gets a full line of user input from the console.
 * @return A string containing the user's input.
 */
std::string getUserInputLine()
{
    std::string input;
    std::getline(std::cin, input);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character
    return input;
}
/*!
 * @brief Gets a single word or token of user input from the console.
 * @return A string containing the user's input.
 */
std::string getUserInputToken()
{
    std::string input;
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character
    return input;
}
/*!
 * @brief Generates a random number within a specified range.
 * @param low The lower bound of the range.
 * @param high The upper bound of the range.
 * @return A randomly generated integer within the specified range.
 */

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
/*!
 * @brief Converts a string to an integer.
 * @param str The string to convert.
 * @return The integer value of the string, or 0 if the conversion fails.
 */
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
/*!
 * @brief Repeats a string a specified number of times.
 * @param str The string to repeat.
 * @param count The number of times to repeat the string.
 * @return A string containing the repeated sequence.
 */
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
/*!
 * @brief Converts a string to lowercase.
 * @param str The string to convert.
 * @return The lowercase version of the string.
 */
std::string toLowerCase(const std::string &str)
{
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return lowerStr;
}
/*!
 * @brief Reads an integer from user input.
 * @return The integer value entered by the user.
 * @details This function ensures that the input is a valid integer, handling errors and prompting the user until a valid input is received.
 */
int readInt()
{
    int value;
    while (true)
    {
        try
        {

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

/*!
 * @brief Waits for the user to press Enter.
 * @details This function pauses the program and waits for the user to press the Enter key before continuing.
 */
void waitForEnter()
{
    std::cout << "Press Enter to continue...";
    // system("stty -echo -icanon");

    // std::cin.ignore(); // Waits for the user to press Ente
    std::cin.get();

    // system("stty echo icanon");
}
/*!
 * @brief Converts a string to uppercase.
 * @param input The string to convert.
 * @return The uppercase version of the string.
 */
std::string toUpperCase(const std::string &input)
{
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}
