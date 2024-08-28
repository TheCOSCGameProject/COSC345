#include "../lib/valerisgame.h"
#include "../lib/combat.h"

ValerisGame::ValerisGame()
{
    numRooms = 10;
    currentRoom = dungeon.generateFloor(numRooms);
}

void ValerisGame::start()
{
    bool exploring = true;
    while (exploring)
    {
        std::cout << "You have entered a " << currentRoom->roomContent.getRoomDesc() << ".\n\n";
        currentRoom->displayAvailableDirections();

        std::cout << "Enter Action: ";
        std::string direction = getUserInputToken();

        // Convert direction to uppercase for consistent comparisons
        std::string upperDirection = toUpperCase(direction);

        if (upperDirection == "N")
        {
            if (currentRoom->north)
            {
                currentRoom = currentRoom->north;
            }
            else
            {
                std::cout << "You can't move North." << std::endl;
            }
        }
        else if (upperDirection == "S")
        {
            if (currentRoom->south)
            {
                currentRoom = currentRoom->south;
            }
            else
            {
                std::cout << "You can't move South." << std::endl;
            }
        }
        else if (upperDirection == "E")
        {
            if (currentRoom->east)
            {
                currentRoom = currentRoom->east;
            }
            else
            {
                std::cout << "You can't move East." << std::endl;
            }
        }
        else if (upperDirection == "W")
        {
            if (currentRoom->west)
            {
                currentRoom = currentRoom->west;
            }
            else
            {
                std::cout << "You can't move West." << std::endl;
            }
        }
        else if (upperDirection == "/PLAY" && currentRoom->roomContent.getRoomType() == 1)
        {
            while (!currentRoom->roomContent.getNPC().gamblingGame.get()->start())
            {
            }
        }
        else if (upperDirection == "/FIGHT" && currentRoom->roomContent.getRoomType() == 0)
        {
            // std::vector<EnemyStruct> enemies = currentRoom->roomContent.getEnemies();
            // for (int i = 0; i < (int)enemies.size(); i++)
            // {
            //     EnemyStruct enemy = enemies[i];
            //     int enemyHealth = enemy.health;
            //     combatV1(player.getCurrHealth(), enemyHealth, 3000, enemy.name);
            // }
        }
        else if (upperDirection == "Q")
        {
            exploring = false;
            std::cout << "Exiting dungeon exploration." << std::endl;
        }
        else if (upperDirection == "/HELP")
        {
            std::cout << getFileContent("../reasources/help.txt") << std::endl;
        }
        else
        {
            std::cout << "Invalid direction. Please enter N, S, E, W, or Q." << std::endl;
        }
    }
}
