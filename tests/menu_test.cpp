#include "../lib/menu.h"
#include "custom_test_framework.h"
#include <sstream>
#include "../lib/toolkit.h"
#include <cassert>
#include <algorithm>
#include <cctype>
#include <regex>

std::string normalizeString(const std::string &input)
{
    std::regex ansiRegex(R"(\x1B\[[0-9;]*[a-zA-Z])");
    return std::regex_replace(input, ansiRegex, "");
}

void testDisplayIntro()
{
    // Capture the output
    std::stringstream simulatedOutput;
    std::streambuf *coutBackup = std::cout.rdbuf();
    std::cout.rdbuf(simulatedOutput.rdbuf());

    // Call the function to test
    displayIntro(15, "\033[36m");

    // Restore std::cout
    std::cout.rdbuf(coutBackup);

    // Expected output
    std::vector<std::string> intro = split(getFileContent("../reasources/intro.txt"), '@');
    std::string expectedOutput;

    for (int i = 0; i < 3; i++)
    {
        expectedOutput.append("\033[36m" + intro[i] + "\033[37m\n");
    }
    expectedOutput.append("\033[36m" + intro[intro.size() - 1] + "\033[37m\n");

    // Capture actual output
    std::string output = simulatedOutput.str();

    std::string normalizedExpected = normalizeString(expectedOutput);
    std::string normalizedOutput = normalizeString(output);

    // Check if the normalized output matches the normalized expected output
    if (normalizedOutput != normalizedExpected)
    {
        std::cout << "Test failed!\n";
        std::cout << "Normalized Expected Output:\n"
                  << normalizedExpected << "\n";
        std::cout << "Normalized Actual Output:\n"
                  << normalizedOutput << "\n";
    }
    else
    {
        std::cout << "Test passed!\n";
    }

    // Alternatively, use an assertion
    ASSERT_EQUAL(normalizedOutput, normalizedExpected);
}

void testDisplayj()
{
    // Capture the output
    std::stringstream simulatedOutput;
    std::streambuf *coutBackup = std::cout.rdbuf();
    std::cout.rdbuf(simulatedOutput.rdbuf());

    // Call the function to test
    Displayj();

    // Restore std::cout
    std::cout.rdbuf(coutBackup);

    // Expected output
    std::string expectedOutput =
        "\033[37m==========================================================\n"
        "               VALERIS GAME MENU\n"
        "==========================================================\n"
        "1. Start New Game\n"
        "2. Load Saved Game\n"
        "3. Instructions\n"
        "4. Accessibility\n"
        "5. Exit\n"
        "==========================================================\n";

    // Capture actual output
    std::string output = simulatedOutput.str();

    // Alternatively, use an assertion
    ASSERT_EQUAL(output, expectedOutput);
}

void test_DisplayInstructionsText()
{
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    // Fake the input to simulate Enter key press
    std::istringstream fakeInput("\n");
    std::cin.rdbuf(fakeInput.rdbuf());

    // Call the function to test
    DisplayInstructionsText();

    // Restore the original cout buffer
    std::cout.rdbuf(old);

    // The expected output with ANSI escape code for white text
    std::string expectedOutput = "\033[37m\nInstructions:\n1. Use the N, S, W, E keys to move your character.\n2. Fight enemies with ___\n3. Collect items to improve your chances of survival.\n4. Play minigames with ___\n5. Defeat bosses to progress to the next level.\n\n\033[0mPress Enter to continue...\n";

    std::string normalizedExpected = normalizeString(expectedOutput);
    std::string normalizedOutput = normalizeString(buffer.str());

    // Compare the actual output with the expected output
    ASSERT_EQUAL(normalizedOutput, normalizedExpected);
}