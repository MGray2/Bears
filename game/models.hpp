#ifndef MODELS_HPP
#define MODELS_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>

class Item;
class Armor;
class Weapon;
class Ranged;
class Player;
char itemType(const std::shared_ptr<Item> &item);

/* Item
Constructor arguments include:

name, qty, desc.
*/
class Item
{
public:
    std::string name;
    short quantity;
    std::string description;

    // Constructor
    Item(std::string name, short qty, std::string desc) : name(name), quantity(qty), description(desc) {}

    virtual ~Item() {}; // Destructor
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

    virtual ~Armor() {}; // Destructor

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

    virtual ~Weapon() {}; // Destructor
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

    virtual ~Ranged() {}; // Destructor

    void shoot()
    {
        magazine -= burst;
    }

    short check_mag()
    {
        return magazine;
    }

    // evaluates if ranged weapon's magazine is empty
    bool mag_empty()
    {
        return magazine == 0;
    }
};

class Inventory
{
public:
    std::vector<std::shared_ptr<Item>> items;

    // Add item to inventory
    void addItem(std::shared_ptr<Item> item)
    {
        items.push_back(item);
    }

    // Remove item from inventory by index
    void removeItem(int index)
    {
        if (index >= 0 && index < items.size())
        {
            items.erase(items.begin() + index);
        }
    }

    // Get item by index
    std::shared_ptr<Item> getItem(int index) const
    {
        if (index >= 0 && index < items.size())
        {
            return items[index];
        }
        return nullptr;
    }

    // Display all items
    void displayItems() const
    {
        for (const auto &item : items)
        {
            std::cout << "Name: " << item->name << ", Quantity: " << item->quantity << ", Description: " << item->description << std::endl;
        }
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

name, health, max health, armor, weapon, xp, max xp, inventory
*/
class Player
{
public:
    std::string name;
    short health;
    short health_max;
    Armor armor;
    Weapon weapon;
    unsigned int xp;
    unsigned int xp_max;
    Inventory inventory;

    // Constructor
    Player(std::string name, short health, short health_max, Armor armor, Weapon weapon, unsigned int xp, unsigned int xp_max, Inventory inventory) : name(name), health_max(health_max), armor(armor), weapon(weapon), xp(xp), xp_max(xp_max), inventory(inventory) {}

    virtual ~Player() {}; // Destructor

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

#endif