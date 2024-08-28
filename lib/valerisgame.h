#include "toolkit.h"
#include "player.h"
#include "dungeon.h"
#include "dependencies.h"

class ValerisGame
{
private:
    Player player;
    Dungeon dungeon;
    Room *currentRoom;
    int numRooms;

public:
    ValerisGame();

    void start();
};