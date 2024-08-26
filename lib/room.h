#ifndef ROOMCONTENT_H
#define ROOMCONTENT_H

#include <vector>
#include <string>
#include <iostream>
#include "../helper/minigames.cpp"

// Assuming these functions are declared in the toolkit.h
// std::vector<std::string> split(const std::string &str, char delimiter);
// int generateRandomNumber(int low, int high);
// int stringToInt(const std::string &str);
// std::string getFileContent(const std::string &filePath);

struct EnemyStruct
{
    std::string name;
    int health;
    int attack;
};

struct NPC
{
    std::string name;
    std::unique_ptr<Game> gamblingGame;
    int skillLevel;
};

class RoomContent
{
public:
    RoomContent();

    void emptyRoom();
    void gamblingRoom();
    void addItem(const std::string &item);
    void addEnemy(const EnemyStruct &enemy);
    void displayContent() const;
    int getRoomType();
    NPC &getNPC();

private:
    std::vector<std::string> items;
    std::vector<EnemyStruct> enemies;
    NPC npc;
    bool passcode;
    int roomType;
};

class Room
{
public:
    Room();

    Room *north;
    Room *south;
    Room *west;
    Room *east;
    RoomContent roomContent;
};

#endif // ROOMCONTENT_H
