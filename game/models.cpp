#include <string>
#include <vector>
#include <memory>

// Items
class Item
{
public:
    std::string name;
    short quantity;
    std::string description;

    // Constructor
    Item(std::string name, short qty, std::string desc) : name(name), quantity(qty), description(desc) {}
};

/* Armor, subclass of Item.
Constructor arguments include:

name, qty, desc,
health (max health), value.
*/
class Armor : public Item
{
public:
    short health;
    short health_max;
    short value;

    // Constructor
    Armor(std::string name, short qty, std::string desc, short health, short health_max, short value) : Item(name, qty, desc), health(health), health_max(health_max), value(value) {}

    void check_broken()
    {
        if (health == 0)
        {
            health_max = 0;
            value = 0;
        }
    }
};

/* Weapon, subclass of Item.
Constructor arguments include:

name, qty, desc,
dmg_min, dmg_max, ms_chance, crit_chance. */
class Weapon : public Item
{
public:
    short damage_min;
    short damage_max;
    short miss_chance;
    short critical_chance;

    // Constructor
    Weapon(std::string name, short qty, std::string desc, short dmg_min, short dmg_max, short ms_chance, short crit_chance) : Item(name, qty, desc), damage_min(dmg_min), damage_max(dmg_max), miss_chance(ms_chance), critical_chance(crit_chance) {}
};

/* Ranged Weapon, subclass of Weapon.
Constructor arguments include:

name, qty, desc,
dmg_min, dmg_max, ms_chance, crit_chance,
mag, burst. */
class Ranged : public Weapon
{
public:
    short magazine;
    short burst;

    // Constructor
    Ranged(std::string name, short qty, std::string desc, short dmg_min, short dmg_max, short ms_chance, short crit_chance, short mag, short brst)
        : Weapon(name, qty, desc, dmg_min, dmg_max, ms_chance, crit_chance), magazine(mag), burst(brst) {}

    void shoot()
    {
        magazine -= burst;
    }

    short check_mag()
    {
        return magazine;
    }

    bool mag_empty()
    {
        return magazine == 0;
    }
};

class Enemy
{
public:
    std::string name;
    short health;
    short health_max;
    Armor armor;
    Weapon weapon;

    void harm(short amount)
    {
        short damage = amount - armor.value;
        armor.health -= amount;
        health -= damage;
    }
};

/* The player character
Constructor arguments include:

name, health, max health, armor, weapon, exp, level, inventory
*/
class Player
{
public:
    std::string name;
    short health;
    short health_max;
    Armor armor;
    Weapon weapon;
    unsigned int exp;
    int level;
    std::vector<std::shared_ptr<Item>> inventory;

    // Constructor
    Player(std::string name, short health, short health_max, Armor armor, Weapon weapon, unsigned int exp, short level, std::vector<std::shared_ptr<Item>> inventory) : name(name), health_max(health_max), armor(armor), weapon(weapon), exp(exp), level(level), inventory(inventory) {}

    void harm(short amount)
    {
        armor.check_broken();

        // calculate damage considering the armor's value
        short damage = amount - armor.value;
        if (damage > 0)
        {
            health -= damage; // apply damage to player health
        }

        if (health < 0)
        {
            health = 0; // ensure health doesn't go below 0
        }
    }

    void heal(short amount)
    {
        health += amount;
        if (health > health_max)
        {
            health = health_max; // prevents overheal
        }
    }

    void equip(Armor item)
    {
        armor = item;
    }

    void equip(Weapon item)
    {
        weapon = item;
    }
};