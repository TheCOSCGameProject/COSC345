/*!
 * @file weapon.cpp
 * @brief Implements the Weapon class for managing weapon data in the Valeris game.
 * @details This file defines the methods of the Weapon class, which is responsible for handling various weapons, including generating random weapons, filtering weapons by rarity, and accessing weapon attributes.
 */
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "../lib/weapon.h"

/*!
 * @brief Constructor for the Weapon class.
 * @details Initializes the weapon system by seeding the random number generator and adding a predefined set of weapons to the system.
 */
Weapon::Weapon()
{
    // seed
    srand(static_cast<unsigned int>(time(0)));

    // weapons
    addWeapon(1, "Plasma Rifle", "A high-energy weapon that fires concentrated plasma bolts.", 45, "Rare", true, false);
    addWeapon(2, "Laser Pistol", "A compact, high-precision laser pistol ideal for close combat.", 25, "Common", true, false);
    addWeapon(3, "Icicle", "A grenade that releases a freezing gas upon hit, freezing enemies.", 35, "Uncommon", false, true);
    addWeapon(4, "Sonic Blaster", "Emits sound waves capable of shattering solid objects.", 40, "Rare", true, true);
    addWeapon(5, "Electro Blade", "A sword infused with electrical energy, delivering a shock with each strike.", 30, "Uncommon", false, true);
    addWeapon(6, "Ion Cannon", "A heavy-duty weapon that fires a massive ion beam, effective against armored targets.", 60, "Epic", true, true);
    addWeapon(7, "Pulse Rifle", "Fires rapid bursts of energy pulses, excellent for crowd control.", 38, "Common", true, true);
    addWeapon(8, "Nano Sword", "A blade composed of nanobots, able to cut through virtually anything.", 50, "Epic", false, false);
    addWeapon(9, "Graviton Hammer", "A weapon that manipulates gravity to deliver devastating blows.", 55, "Legendary", false, true);
    addWeapon(10, "Neutron Bomb", "A bomb that releases neutron radiation, lethal to organic life.", 100, "Legendary", true, false);
    addWeapon(11, "Crysknife", "A sacred knife made from the tooth of a sandworm. Deadly in close combat.", 50, "Rare", false, false);
    addWeapon(12, "Maula Pistol", "A small, easily concealable projectile weapon used by assassins.", 25, "Common", false, false);
    addWeapon(13, "Lasgun", "A powerful beam weapon capable of cutting through almost any material.", 60, "Uncommon", false, false);
    addWeapon(14, "Spice Grenade", "An explosive that disperses spice particles, causing hallucinations and disorientation.", 50, "Epic", true, true);
    addWeapon(15, "Gom Jabbar", "A needle-like weapon that delivers a lethal poison. Used in specific assassination rituals.", 100, "Legendary", false, false);
    addWeapon(16, "Hunter-Seeker", "A remote-controlled assassination device that seeks out its target with precision.", 45, "Epic", true, false);
    addWeapon(17, "Stunner", "A non-lethal weapon used to incapacitate enemies, commonly used by law enforcement.", 20, "Common", false, true);
    addWeapon(18, "Spice-Enhanced Blade", "A blade tempered with the essence of spice, increasing its sharpness and durability.", 55, "Epic", false, true);
    addWeapon(19, "Shai-Hulud's Tooth", "A weapon made from a sandworm tooth, infused with the power of the desert.", 70, "Legendary", false, false);
    addWeapon(20, "Weirding Module", "A sound-based weapon that amplifies the voice of its user to deliver devastating sonic attacks.", 70, "Legendary", true, true);
    addWeapon(21, "Sand Compactor", "A tool-turned-weapon that uses compressed sand to create projectiles.", 30, "Uncommon", true, false);
    addWeapon(22, "Fremen Hook", "A specialized tool used by the Fremen to ride sandworms, can also be used as a weapon.", 40, "Rare", false, true);
    addWeapon(23, "Injector Dart", "A small dart that can deliver a variety of substances, from tranquilizers to lethal toxins.", 35, "Uncommon", true, true);
    addWeapon(24, "Spice Harvester's Wrench", "A large, heavy tool used in spice harvesting, repurposed as a weapon.", 45, "Common", true, false);
    addWeapon(25, "Glowglobe Bomb", "A light-emitting device that can be overloaded to explode, blinding enemies temporarily.", 20, "Uncommon", true, true);
    addWeapon(26, "Stilgar's Blade", "A unique knife belonging to the legendary Fremen leader Stilgar, revered for its history.", 55, "Epic", false, false);
    addWeapon(27, "Sardaukar Blade", "A razor-sharp sword used by the elite Sardaukar troops, feared across the galaxy.", 65, "Rare", false, false);
}





/*!
 * @brief Returns a random weapon ID.
 * @details Selects a random weapon from the available weapons.
 * @return An integer representing the ID of the randomly selected weapon.
 */
int Weapon::giveRandWeapon()
{
    int randomIndex = rand() % weaponIds.size();
    return weaponIds[randomIndex];
}



/*!
 * @brief Returns a weapon ID based on the specified rarity.
 * @param rarity The rarity of the desired weapon (e.g., "Common", "Rare", "Epic").
 * @return An integer representing the ID of the randomly selected weapon with the specified rarity, or -1 if no such weapon exists.
 */
int Weapon::giveRariWeapon(const std::string &rarity)
{
    std::vector<int> filteredIds;
    for (const auto &weapon : weapons)
    {
        if (weapon.second.rarity == rarity)
        {
            filteredIds.push_back(weapon.first);
        }
    }
    if (!filteredIds.empty())
    {
        int randomIndex = rand() % filteredIds.size();
        return filteredIds[randomIndex];
    }
    return -1;
}

/*!
 * @brief Returns the name of the weapon with the specified ID.
 * @param weaponId The ID of the weapon.
 * @return A string representing the name of the weapon.
 */
std::string Weapon::getName(int weaponId)
{
    return weapons[weaponId].name;
}
/*!
 * @brief Returns the description of the weapon with the specified ID.
 * @param weaponId The ID of the weapon.
 * @return A string representing the description of the weapon.
 */
std::string Weapon::getDescription(int weaponId)
{
    return weapons[weaponId].description;
}
/*!
 * @brief Returns the damage value of the weapon with the specified ID.
 * @param weaponId The ID of the weapon.
 * @return An integer representing the damage dealt by the weapon.
 */
int Weapon::getDamage(int weaponId)
{
    return weapons[weaponId].damage;
}
/*!
 * @brief Returns the rarity of the weapon with the specified ID.
 * @param weaponId The ID of the weapon.
 * @return A string representing the rarity of the weapon.
 */
std::string Weapon::getRarity(int weaponId)
{
    return weapons[weaponId].rarity;
}

/*!
 * @brief Checks if the weapon with the specified ID is ranged.
 * @param weaponId The ID of the weapon.
 * @return True if the weapon is ranged, otherwise false.
 */

bool Weapon::getRanged(int weaponId)
{
    return weapons[weaponId].ranged;
}
/*!
 * @brief Checks if the weapon with the specified ID has stun capability.
 * @param weaponId The ID of the weapon.
 * @return True if the weapon has stun capability, otherwise false.
 */
bool Weapon::getStun(int weaponId)
{
    return weapons[weaponId].stun;
}

/*!
 * @brief Adds a new weapon to the weapon system.
 * @param id The ID of the weapon.
 * @param name The name of the weapon.
 * @param description The description of the weapon.
 * @param damage The damage dealt by the weapon.
 * @param rarity The rarity of the weapon (e.g., "Common", "Rare").
 * @param ranged Indicates if the weapon is ranged.
 * @param stun Indicates if the weapon has stun capability.
 * @details This function adds a new weapon to the internal storage, making it available for selection and use within the game.
 */
void Weapon::addWeapon(int id, const std::string &name, const std::string &description, int damage, const std::string &rarity, bool ranged, bool stun)
{
    weapons[id] = {name, description, damage, rarity, ranged, stun};
    weaponIds.push_back(id);
}

// how to use
// int main()
// {
//     Weapon weaponSystem;

//     // get a random weapon
//     int randWeaponId = weaponSystem.giveRandWeapon();

//     // get a rare weapon
//     int rareWeaponId = weaponSystem.giveRariWeapon("Epic");

//     return 0;
// }
