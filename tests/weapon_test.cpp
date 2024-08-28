#include "../lib/weapon.h"
#include "custom_test_framework.h"

// g++ -std=c++17 -o run_tests.exe tests/weapon_test.cpp ./helper/weapon.cpp
// ./ run_tests.exe

// Test the initialization of weapons and their attributes
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

// Test random weapon generation
void testRandomWeaponGeneration()
{
    Weapon weaponSystem;
    int weaponId = weaponSystem.giveRandWeapon();
    ASSERT(weaponId >= 1 && weaponId <= 27);
    ASSERT(!weaponSystem.getName(weaponId).empty());
}

// Test weapon generation by rarity
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

int main()
{
    TestFramework framework("weapon_test_results.xml");

    framework.addTest("Weapon Initialization", testWeaponInitialization);
    framework.addTest("Random Weapon Generation", testRandomWeaponGeneration);
    framework.addTest("Weapon Generation by Rarity", testWeaponGenerationByRarity);

    framework.run();

    return 0;
}