#include "../lib/valerisgame.h"

ValerisGame::ValerisGame()
{
    numRooms = 10;
    currentRoom = dungeon.generateFloor(numRooms);
}

void ValerisGame::start()
{
    this->dungeon.traverseAndPrint(currentRoom); // layout checking

    std::cout << "Dungeon generated with " << numRooms << " rooms." << std::endl;

    bool exploring = true;
    while (exploring)
    {
        std::cout << "Currently, you are in a " << currentRoom->roomContent.getRoomDesc() << "." << std::endl;
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
