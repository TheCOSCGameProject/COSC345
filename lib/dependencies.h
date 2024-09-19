#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <random>
#include <cstdlib>
#include <iomanip>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#include <CoreAudio/CoreAudio.h>
#include <AudioToolbox/AudioToolbox.h>
#endif