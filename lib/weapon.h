/*!
 * @file weapon.h
 * @brief This file contains the declaration of the Weapon class used in the game.
 * @details The Weapon class is responsible for managing different types of weapons in the game,
 * including their attributes such as name, description, damage, rarity, and whether they are ranged or can stun.
 */

#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <unordered_map>
#include <vector>

/*!
 * @class Weapon
 * @brief Manages different types of weapons in the game.
 * @details The Weapon class provides methods to retrieve weapons based on randomness or rarity and access various attributes of the weapons.
 */
class Weapon
{
public:
    /*!
     * @brief Constructor for the Weapon class.
     * @details Initializes the weapons data structure and populates it with predefined weapons.
     */
    Weapon();

    /*!
     * @brief Get a random weapon ID.
     * @return The ID of a randomly selected weapon.
     */
    int giveRandWeapon();

    /*!
     * @brief Get a weapon ID based on its rarity.
     * @param rarity The rarity level of the desired weapon (e.g., "common", "rare", "epic").
     * @return The ID of a weapon that matches the specified rarity.
     */
    int giveRariWeapon(const std::string &rarity);

    /*!
     * @brief Get the name of a weapon.
     * @param weaponId The ID of the weapon.
     * @return The name of the weapon.
     */
    std::string getName(int weaponId);

    /*!
     * @brief Get the description of a weapon.
     * @param weaponId The ID of the weapon.
     * @return The description of the weapon.
     */
    std::string getDescription(int weaponId);

    /*!
     * @brief Get the damage value of a weapon.
     * @param weaponId The ID of the weapon.
     * @return The damage value of the weapon.
     */
    int getDamage(int weaponId);

    /*!
     * @brief Get the rarity of a weapon.
     * @param weaponId The ID of the weapon.
     * @return The rarity level of the weapon.
     */
    std::string getRarity(int weaponId);

    /*!
     * @brief Check if a weapon is ranged.
     * @param weaponId The ID of the weapon.
     * @return True if the weapon is ranged, otherwise false.
     */
    bool getRanged(int weaponId);

    /*!
     * @brief Check if a weapon can stun.
     * @param weaponId The ID of the weapon.
     * @return True if the weapon can stun, otherwise false.
     */
    bool getStun(int weaponId);

private:
    /*!
     * @brief Structure to hold weapon data.
     * @details This structure contains all the attributes of a weapon, including its name, description, damage, rarity, and whether it is ranged or can stun.
     */
    struct WeaponData
    {
        std::string name;           //!< Name of the weapon.
        std::string description;    //!< Description of the weapon.
        int damage;                 //!< Damage value of the weapon.
        std::string rarity;         //!< Rarity level of the weapon.
        bool ranged;                //!< Indicates if the weapon is ranged.
        bool stun;                  //!< Indicates if the weapon can stun.
    };

    /*!
     * @brief Dictionary to store weapons with their corresponding IDs.
     */
    std::unordered_map<int, WeaponData> weapons;

    /*!
     * @brief List of weapon IDs.
     */
    std::vector<int> weaponIds;

    /*!
     * @brief Add a weapon to the weapons dictionary.
     * @param id The ID of the weapon.
     * @param name The name of the weapon.
     * @param description The description of the weapon.
     * @param damage The damage value of the weapon.
     * @param rarity The rarity level of the weapon.
     * @param ranged True if the weapon is ranged, otherwise false.
     * @param stun True if the weapon can stun, otherwise false.
     */
    void addWeapon(int id, const std::string &name, const std::string &description, int damage, const std::string &rarity, bool ranged, bool stun);
};

#endif // WEAPON_H