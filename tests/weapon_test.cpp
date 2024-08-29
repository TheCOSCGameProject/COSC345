/**
 * @file weapon_test.cpp
 * @brief Unit tests for the Weapon class.
 *
 * This file contains test cases for verifying the correct behavior of the Weapon class,
 * including weapon initialization, random weapon generation, and weapon generation by rarity.
 */

#include "../lib/weapon.h"
#include "custom_test_framework.h"

// g++ -std=c++17 -o run_tests.exe tests/weapon_test.cpp ./helper/weapon.cpp
// ./run_tests.exe

/**
 * @brief Test the initialization of weapons and their attributes.
 *
 * This test verifies that the Weapon class correctly initializes weapons with their
 * respective attributes such as name, description, damage, rarity, and properties
 * like ranged and stun capabilities.
 */
void testWeaponInitialization()
{
    Weapon weaponSystem;
    ASSERT_EQUAL("Plasma Rifle", weaponSystem.getName(1));
    ASSERT_EQUAL("A high-energy weapon that fires concentrated plasma bolts.", weaponSystem.getDescription(1));
    ASSERT_EQUAL(45, weaponSystem.getDamage(1));
    ASSERT_EQUAL("Rare", weaponSystem.getRarity(1));
    ASSERT(weaponSystem.getRanged(1));
    ASSERT(!weaponSystem.getStun(1));
}

/**
 * @brief Test the random weapon generation functionality.
 *
 * This test ensures that the Weapon class can generate a random weapon ID within
 * the valid range and that the generated weapon has a non-empty name.
 */
void testRandomWeaponGeneration()
{
    Weapon weaponSystem;
    int weaponId = weaponSystem.giveRandWeapon();
    ASSERT(weaponId >= 1 && weaponId <= 27);
    ASSERT(!weaponSystem.getName(weaponId).empty());
}

/**
 * @brief Test the generation of weapons by rarity.
 *
 * This test verifies that the Weapon class can correctly generate weapons based on
 * specified rarity levels (e.g., "Common", "Rare") and ensures that it returns -1
 * when attempting to generate a weapon of a nonexistent rarity.
 */
void testWeaponGenerationByRarity()
{
    Weapon weaponSystem;

    int commonWeaponId = weaponSystem.giveRariWeapon("Common");
    ASSERT(commonWeaponId != -1);
    ASSERT_EQUAL("Common", weaponSystem.getRarity(commonWeaponId));

    int rareWeaponId = weaponSystem.giveRariWeapon("Rare");
    ASSERT(rareWeaponId != -1);
    ASSERT_EQUAL("Rare", weaponSystem.getRarity(rareWeaponId));

    int nonexistentWeaponId = weaponSystem.giveRariWeapon("Nonexistent");
    ASSERT_EQUAL(-1, nonexistentWeaponId); // No weapons of this rarity should exist
}

/**
 * @brief Main function that runs the test cases for the Weapon class.
 *
 * The main function creates a TestFramework object, adds the test cases for the Weapon class,
 * and then runs the tests, outputting the results to an XML file.
 *
 * @return int Returns 0 upon successful execution of the tests.
 */
int main()
{
    TestFramework framework("weapon_test_results.xml");

    framework.addTest("Weapon Initialization", testWeaponInitialization);
    framework.addTest("Random Weapon Generation", testRandomWeaponGeneration);
    framework.addTest("Weapon Generation by Rarity", testWeaponGenerationByRarity);

    framework.run();

    return 0;
}
