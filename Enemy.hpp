#pragma once

#include "Consumable.hpp"
#include "Equipable.hpp"
#include "Dice.hpp"

class Enemy : 
    public Fighter
{
public:
    Enemy(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float attack_power, int _defense, int _initiative);
    virtual ~Enemy();

    void addItem(Item* _item);

    Item* dropItem();

    virtual void update(const float& _dt);

protected:
    std::vector<Item*> items;
};

class Skeleton : 
    public Enemy
{
public:
    Skeleton(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float attack_power, int _defense, int _initiative);
    virtual ~Skeleton();

    void update(const float& _dt);
};

class Slime : 
    public Enemy
{
public:
    Slime(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float attack_power, int _defense, int _initiative);
    virtual ~Slime();

    void update(const float& _dt);
};

class Bat : 
    public Enemy
{
public:
    Bat(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float attack_power, int _defense, int _initiative);
    virtual ~Bat();

    void update(const float& _dt);
};

class Rat : 
    public Enemy
{
public:
    Rat(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float attack_power, int _defense, int _initiative);
    virtual ~Rat();

    void update(const float& _dt);
};

