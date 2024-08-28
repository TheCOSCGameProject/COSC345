#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <queue>
#include <map>
#include <sstream>
#include <thread>
#include <chrono>
#include <iomanip>

using namespace std;

#ifdef _WIN32
#include <windows.h>
#endif

/**
@brief class to generate room with directions.
@param The room directions are classified as North, South, East and West.
*/
class Room
{
public:
    Room *north;
    Room *south;
    Room *west;
    Room *east;
    std::string content;

    Room() : north(nullptr), south(nullptr), west(nullptr), east(nullptr), content("Empty room") {}

    void displayAvailableDirections() const
    {
        std::cout << "You can move: ";
        if (north)
            std::cout << ", North ";
        if (south)
            std::cout << ", South ";
        if (west)
            std::cout << ", West ";
        if (east)
            std::cout << ", East ";
        std::cout << std::endl;
    }
};

// Dungeon class definition
class Dungeon
{
private:
    std::vector<Room *> rooms;
    std::mt19937 rng;

    Room *generateRoom()
    {
        Room *newRoom = new Room();
        rooms.push_back(newRoom);
        return newRoom;
    }

    void linkRooms(Room *room1, Room *room2, int direction)
    {
        switch (direction)
        {
        case 0: // North
            room1->north = room2;
            room2->south = room1;
            break;
        case 1: // South
            room1->south = room2;
            room2->north = room1;
            break;
        case 2: // West
            room1->west = room2;
            room2->east = room1;
            break;
        case 3: // East
            room1->east = room2;
            room2->west = room1;
            break;
        }
    }

    void checkAndLink(Room *newRoom, int x, int y, std::map<std::pair<int, int>, Room *> &roomMap)
    {
        // Check north
        if (roomMap.find({x, y + 1}) != roomMap.end())
        {
            linkRooms(newRoom, roomMap[{x, y + 1}], 0);
        }
        // Check south
        if (roomMap.find({x, y - 1}) != roomMap.end())
        {
            linkRooms(newRoom, roomMap[{x, y - 1}], 1);
        }
        // Check west
        if (roomMap.find({x - 1, y}) != roomMap.end())
        {
            linkRooms(newRoom, roomMap[{x - 1, y}], 2);
        }
        // Check east
        if (roomMap.find({x + 1, y}) != roomMap.end())
        {
            linkRooms(newRoom, roomMap[{x + 1, y}], 3);
        }
    }

public:
    Dungeon() : rng(std::time(0)) {}

    ~Dungeon()
    {
        for (Room *room : rooms)
        {
            delete room;
        }
    }

    Room *generateFloor(int numRooms)
    {
        if (numRooms <= 0)
        {
            return nullptr;
        }

        Room *startRoom = generateRoom();
        std::map<std::pair<int, int>, Room *> roomMap;
        roomMap[{0, 0}] = startRoom;

        for (int i = 1; i < numRooms; ++i)
        {
            Room *existingRoom;
            int direction, x = 0, y = 0;

            do
            {
                auto it = roomMap.begin();
                std::advance(it, std::uniform_int_distribution<>(0, roomMap.size() - 1)(rng));
                existingRoom = it->second;
                x = it->first.first;
                y = it->first.second;

                direction = std::uniform_int_distribution<>(0, 3)(rng);
            } while (
                (direction == 0 && existingRoom->north != nullptr) ||
                (direction == 1 && existingRoom->south != nullptr) ||
                (direction == 2 && existingRoom->west != nullptr) ||
                (direction == 3 && existingRoom->east != nullptr));

            int newX = x, newY = y;

            switch (direction)
            {
            case 0:
                newY += 1;
                break; // North
            case 1:
                newY -= 1;
                break; // South
            case 2:
                newX -= 1;
                break; // West
            case 3:
                newX += 1;
                break; // East
            }

            Room *newRoom = generateRoom();
            roomMap[{newX, newY}] = newRoom;
            linkRooms(existingRoom, newRoom, direction);

            // Check and link to adjacent rooms
            checkAndLink(newRoom, newX, newY, roomMap);
        }

        return rooms[std::uniform_int_distribution<>(0, rooms.size() - 1)(rng)];
    }

    void relinkDungeon(Room *startRoom)
    {
        if (startRoom == nullptr)
            return;

        std::queue<std::pair<Room *, std::pair<int, int>>> q;
        std::map<std::pair<int, int>, Room *> visited;

        q.push({startRoom, {0, 0}});
        visited[{0, 0}] = startRoom;

        while (!q.empty())
        {
            auto [currentRoom, coords] = q.front();
            q.pop();

            int x = coords.first;
            int y = coords.second;

            // Check and relink all possible directions
            if (currentRoom->north && visited.find({x, y + 1}) == visited.end())
            {
                currentRoom->north->south = currentRoom;
                q.push({currentRoom->north, {x, y + 1}});
                visited[{x, y + 1}] = currentRoom->north;
            }

            if (currentRoom->south && visited.find({x, y - 1}) == visited.end())
            {
                currentRoom->south->north = currentRoom;
                q.push({currentRoom->south, {x, y - 1}});
                visited[{x, y - 1}] = currentRoom->south;
            }

            if (currentRoom->east && visited.find({x + 1, y}) == visited.end())
            {
                currentRoom->east->west = currentRoom;
                q.push({currentRoom->east, {x + 1, y}});
                visited[{x + 1, y}] = currentRoom->east;
            }

            if (currentRoom->west && visited.find({x - 1, y}) == visited.end())
            {
                currentRoom->west->east = currentRoom;
                q.push({currentRoom->west, {x - 1, y}});
                visited[{x - 1, y}] = currentRoom->west;
            }
        }
    }

    void traverseAndPrint(Room *startRoom)
    { // Traverse the floor (used for testing or can create floor maps)
        if (startRoom == nullptr)
            return;

        std::queue<std::pair<Room *, std::pair<int, int>>> q;
        std::map<std::pair<int, int>, Room *> visited;

        q.push({startRoom, {0, 0}});
        visited[{0, 0}] = startRoom;

        while (!q.empty())
        {
            auto [currentRoom, coords] = q.front();
            q.pop();

            int x = coords.first;
            int y = coords.second;
            std::cout << "Room at (" << x << ", " << y << "): " << currentRoom->content << std::endl;

            if (currentRoom->north && visited.find({x, y + 1}) == visited.end())
            {
                q.push({currentRoom->north, {x, y + 1}});
                visited[{x, y + 1}] = currentRoom->north;
            }
            if (currentRoom->south && visited.find({x, y - 1}) == visited.end())
            {
                q.push({currentRoom->south, {x, y - 1}});
                visited[{x, y - 1}] = currentRoom->south;
            }
            if (currentRoom->east && visited.find({x + 1, y}) == visited.end())
            {
                q.push({currentRoom->east, {x + 1, y}});
                visited[{x + 1, y}] = currentRoom->east;
            }
            if (currentRoom->west && visited.find({x - 1, y}) == visited.end())
            {
                q.push({currentRoom->west, {x - 1, y}});
                visited[{x - 1, y}] = currentRoom->west;
            }
        }
    }
};

#ifdef _WIN32
void ConsoleSizeControl(int width, int height)
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
    std::cout << "\e[8;" << height << ";" << width << "t";
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

void displayIntro(int delayTime, std::string color)
{
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

void Displayj()
{
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

void StartGame()
{
    std::cout << "Starting a new game..." << std::endl;

    Dungeon dungeon;
    int numRooms = 10;
    // dungeon.generateFloor(numRooms);
    Room *currentRoom = dungeon.generateFloor(numRooms);

    dungeon.traverseAndPrint(currentRoom); // layout checking
    dungeon.relinkDungeon(currentRoom);

    std::cout << "Dungeon generated with " << numRooms << " rooms." << std::endl;

    bool exploring = true;
    while (exploring)
    {
        std::cout << "Currently, you are in a " << currentRoom->content << "." << std::endl;
        currentRoom->displayAvailableDirections();

        std::cout << "Please enter a direction as N (North), S (South), E (East) and W (West) or Q (Quit): ";
        char direction;
        std::cin >> direction;

        switch (toupper(direction))
        {
        case 'N':
            if (currentRoom->north)
            {
                currentRoom = currentRoom->north;
            }
            else
            {
                std::cout << "You can't move North." << std::endl;
            }
            break;
        case 'S':
            if (currentRoom->south)
            {
                currentRoom = currentRoom->south;
            }
            else
            {
                std::cout << "You can't move South." << std::endl;
            }
            break;
        case 'E':
            if (currentRoom->east)
            {
                currentRoom = currentRoom->east;
            }
            else
            {
                std::cout << "You can't move East." << std::endl;
            }
            break;
        case 'W':
            if (currentRoom->west)
            {
                currentRoom = currentRoom->west;
            }
            else
            {
                std::cout << "You can't move West." << std::endl;
            }
            break;
        case 'Q':
            exploring = false;
            std::cout << "Exiting dungeon exploration." << std::endl;
            break;
        default:
            std::cout << "Invalid direction. Please enter N, S, E, W, or Q." << std::endl;
            break;
        }
    }
}

void LoadSavedGame()
{
    cout << "Loading game..." << endl;
}

void DisplayInstructionsText()
{
    string instructions = R"(
Instructions:
1. Use the arrow keys to move your character.
2. Avoid obstacles and enemies.
3. Collect items to improve your chances of survival.
4. Defeat bosses to progress to the next level.
)";
    typePrint(instructions);
}

void Accessiblity(int &delayTime, std::string &color)
{
    cout << "Accessibility Options:" << endl;
    cout << "1. Text Speed (current: " << delayTime << " ms)" << endl;
    cout << "2. Text Color (current: " << color << ")" << endl;
    cout << "3. Return to Main Menu" << endl;
    cout << "Enter your choice: ";

    int j;
    cin >> j;

    switch (j)
    {
    case 1:
        cout << "Enter new text speed in milliseconds: ";
        cin >> delayTime;
        break;
    case 2:
        cout << "Select text color:" << endl;
        cout << "1. Green" << endl;
        cout << "2. Blue" << endl;
        cout << "3. Red" << endl;
        cout << "4. Yellow" << endl;
        cout << "5. Default Cyan" << endl;
        cout << "Enter your choice: ";
        int colorChoice;
        cin >> colorChoice;
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
            cout << "Invalid choice. Keeping current color." << endl;
            break;
        }
        break;
    case 3:
        return;
    default:
        cout << "Invalid choice. Returning to Accessibility Options." << endl;
    }
}

int main()
{
    int j;
    bool running = true;

    int delayTime = 15;
    std::string color = "\033[36m";

#ifdef _WIN32
    ConsoleSizeControl(800, 600);
#else
    SetTerminalSize(50, 100);
#endif

    displayIntro(delayTime, color);

    while (running)
    {
        Displayj();
        cin >> j;

        switch (j)
        {
        case 1:
            StartGame();
            break;
        case 2:
            LoadSavedGame();
            break;
        case 3:
            DisplayInstructionsText();
            break;
        case 4:
            Accessiblity(delayTime, color);
            break;
        case 5:
            cout << "Exiting Game. We hope you enjoyed the Game Play." << endl;
            running = false;
            break;
        default:
            cout << "Error: An invalid choice has been entered please try again." << endl;
            break;
        }

        cout << endl;
    }

    return 0;
}
