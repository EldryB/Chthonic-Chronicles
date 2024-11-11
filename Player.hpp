#pragma once

#include "Enemy.hpp"
#include "Jobs.hpp"

class Player :
    public Fighter
{
public:
    Player(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float _attackPower, int _defense, int _initiative);
    virtual ~Player();

    std::vector<Item*>* getInventory() const;

    Jobs* getJobs() const;

    Resources* getResources() const;

    Weapon* getWeapon() const;

    Armor* getArmor() const;

    void addItem(Item* _item);

    void removeItem(Item* _item);

    void update(const float& _dt);

protected:
    Resources* resources;
    Jobs* jobs;
    Armor* armor;
    Weapon* weapon;

    std::vector<Item*>* inventory = new std::vector<Item*>();
};

