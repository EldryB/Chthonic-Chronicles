#include "Player.hpp"

Player::Player(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float _attackPower, int _defense, int _initiative)
    : Fighter(_x, _y, texture_sheet, _name, _hp, _attackPower, _defense, _initiative)
{
    Item* item = new Item(texture_sheet, "Papa", 10, "Hola");
    this->addItem(item);
}

Player::~Player()
{

}

std::vector<Item*>* Player::getInventory() const
{
    return this->inventory;
}

void Player::attack(Fighter* _p)
{

}

void Player::addItem(Item* _item)
{
    this->inventory->push_back(_item);
}
