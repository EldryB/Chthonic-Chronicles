#pragma once

#include "Item.hpp"

class Equipable :
    public Item
{
public:
    Equipable(sf::Texture& _texture, std::string _name, int _initiative, std::string _description);
    virtual ~Equipable();

    int getInitiative() const;

    bool isEquipped() const;

    virtual void use(Fighter* target);

protected:
    int initiative;
    bool equipped;
};

class Weapon :
    public Equipable
{
public:
    Weapon(sf::Texture& _texture, std::string _name, float attack_power, int _initiative, std::string _description);
    virtual ~Weapon();

    float getAttackPower() const;

    void use(Fighter* target);

private:
    float attackPower;
};

class Armor :
    public Equipable
{
public:
    Armor(sf::Texture& _texture, std::string _name, int _defense, int _initiative, std::string _description);
    virtual ~Armor();

    int getDefense() const;

    void use(Fighter* target);

private:
    int defense;
};

