#ifndef CUSTOM_TEST_FRAMEWORK_H
#define CUSTOM_TEST_FRAMEWORK_H

#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <fstream>
#include <chrono>

class TestFramework
{
private:
    struct Test
    {
        std::string name;
        std::function<void()> func;
    };
    std::vector<Test> tests;
    int passed = 0;
    int failed = 0;
    std::ofstream xml_output;

public:
    TestFramework(const std::string &xml_filename) : xml_output(xml_filename)
    {
        xml_output << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        xml_output << "<testsuites>\n";
    }

    ~TestFramework()
    {
        xml_output << "</testsuites>\n";
        xml_output.close();
    }

    void addTest(const std::string &name, std::function<void()> test)
    {
        tests.push_back({name, test});
    }

    void run()
    {
        for (const auto &test : tests)
        {
            std::cout << "Running test: " << test.name << "... ";
            xml_output << "  <testcase name=\"" << test.name << "\"";

            auto start = std::chrono::high_resolution_clock::now();
            try
            {
                test.func();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;

                std::cout << "PASSED" << std::endl;
                xml_output << " time=\"" << elapsed.count() << "\"";
                xml_output << "/>\n";
                passed++;
            }
            catch (const std::exception &e)
            {
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;

                std::cout << "FAILED" << std::endl;
                std::cout << "  Error: " << e.what() << std::endl;
                xml_output << " time=\"" << elapsed.count() << "\">\n";
                xml_output << "    <failure message=\"" << e.what() << "\"/>\n";
                xml_output << "  </testcase>\n";
                failed++;
            }
        }
        std::cout << "\nTest Results: " << passed << " passed, " << failed << " failed" << std::endl;
    }
};

#define ASSERT(condition) \
    if (!(condition))     \
    throw std::runtime_error("Assertion failed: " #condition)

#define ASSERT_EQUAL(expected, actual) \
    if ((expected) != (actual))        \
    throw std::runtime_error("Assertion failed: " #expected " != " #actual)

#endif // CUSTOM_TEST_FRAMEWORK_H