#pragma once

#include "Fighter.hpp"

class Player :
    public Fighter
{
public:
    Player(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float _attackPower, int _defense, int _initiative);
    virtual ~Player();

    std::vector<Item*>* getInventory() const;

    void addItem(Item* _item);

    void attack(Fighter* _p);

protected:
    std::vector<Item*>* inventory = new std::vector<Item*>();
};

