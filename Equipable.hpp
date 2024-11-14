#pragma once

#include "Item.hpp"

class Equipable :
    public Item
{
public:
    Equipable(sf::Texture& _texture, std::string _name, int _initiative, std::string _description, int _price);
    virtual ~Equipable();

    int getInitiative() const;

    bool isEquipped() const;

    virtual void use(Fighter* target);

protected:
    int initiative;
    bool equipped;
    std::string lastDescrp;
};

class Weapon :
    public Equipable
{
public:
    Weapon(sf::Texture& _texture, std::string _name, float attack_power, int _initiative, std::string _description, int _price);
    virtual ~Weapon();

    float getAttackPower() const;

    void setAtributes(int _ini, float _attack);

    void use(Fighter* target);

private:
    float attackPower;
};

class Armor :
    public Equipable
{
public:
    Armor(sf::Texture& _texture, std::string _name, int _defense, int _initiative, std::string _description, int _price);
    virtual ~Armor();

    int getDefense() const;

    void setAtributes(int _ini, int _defense);

    void use(Fighter* target);

private:
    int defense;
};

