#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <unordered_map>
#include <vector>

class Weapon
{
public:
    // Constructor
    Weapon();

    // Methods to get weapons
    int giveRandWeapon();
    int giveRariWeapon(const std::string &rarity);

    // Accessors
    std::string getName(int weaponId);
    std::string getDescription(int weaponId);
    int getDamage(int weaponId);
    std::string getRarity(int weaponId);
    bool getRanged(int weaponId);
    bool getStun(int weaponId);

private:
    struct WeaponData
    {
        std::string name;
        std::string description;
        int damage;
        std::string rarity;
        bool ranged;
        bool stun;
    };

    // Dictionary to store weapons
    std::unordered_map<int, WeaponData> weapons;
    std::vector<int> weaponIds;

    // Add weapons to the dictionary
    void addWeapon(int id, const std::string &name, const std::string &description, int damage, const std::string &rarity, bool ranged, bool stun);
};

#endif // WEAPON_H
