#pragma once

#include "Enemy.hpp"
#include "Jobs.hpp"
#include "Consumable.hpp"

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

    sf::Time getCollectionClock() const;

    std::string getResourceName(ResourceTypes _r);

    void setWeapon(Weapon* _weapon);

    void setArmor(Armor* _armor);

    void addItem(Item* _item);

    int eraseItem(Item* _item);

    void update(const float& _dt);

    int getResourceAmoun(ResourceTypes _r);

    void setResourceAmoun(ResourceTypes _r, int amount);

    void updateCollection(const float& _dt);

protected:
    Resources* resources;
    Jobs* jobs;
    Armor* armor;
    Weapon* weapon;

    sf::Clock collectionClock;

    std::vector<Item*>* inventory = new std::vector<Item*>();
};