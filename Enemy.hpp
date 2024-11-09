#pragma once

#include "Item.hpp"
#include "Dice.hpp"

class Enemy : 
    public Fighter
{
public:
    Enemy(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float _attackPower, int _defense, int _initiative);
    virtual ~Enemy();

    Item* dropItem();

    void update(const float& _dt);

private:
    std::vector<Item*> items;
};

class Skeleton : 
    public Enemy
{
public:
    Skeleton();
};

class Slime : 
    public Enemy
{
public:
    Slime();
};

class Bat : 
    public Enemy
{
public:
    Bat();
};

class Rat : 
    public Enemy
{
public:
    Rat();
};

