#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <random>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#endif