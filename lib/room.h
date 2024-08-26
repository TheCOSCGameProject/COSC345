#ifndef ROOMCONTENT_H
#define ROOMCONTENT_H

#include <vector>
#include <string>
#include <iostream>

// Assuming these functions are declared in the toolkit.h
// std::vector<std::string> split(const std::string &str, char delimiter);
// int generateRandomNumber(int low, int high);
// int stringToInt(const std::string &str);
// std::string getFileContent(const std::string &filePath);

struct Enemy
{
    std::string name;
    int health;
    int attack;
};

struct NPC
{
    std::string name;
    int gamblingGame;
    int skillLevel;
};

class RoomContent
{
public:
    RoomContent();

    void emptyRoom();
    void gamblingRoom();
    void addItem(const std::string &item);
    void addEnemy(const Enemy &enemy);
    void displayContent() const;

private:
    std::vector<std::string> items;
    std::vector<Enemy> enemies;
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
