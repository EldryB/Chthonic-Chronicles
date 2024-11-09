#include "Equipable.hpp"

Equipable::Equipable(sf::Texture& _texture, std::string _name, std::string _description)
	: Item(_texture, _name, _description)
{

}

Equipable::~Equipable()
{

}

void Equipable::use(Fighter* target)
{

}

Weapon::Weapon(sf::Texture& _texture, std::string _name, float attack_power, std::string _description)
	: attackPower(attack_power), Equipable(_texture, _name, _description)
{

}

Weapon::~Weapon()
{

}

float Weapon::getAttackPower() const
{
	return this->attackPower;
}

void Weapon::use(Fighter* target)
{
	target->setAttackPower(target->getAttackPower() + this->getAttackPower());
}

Armor::Armor(sf::Texture& _texture, std::string _name, int _defense, std::string _description)
	: defense(_defense), Equipable(_texture, _name, _description)
{

}

Armor::~Armor()
{

}

int Armor::getDefense() const
{
	return this->defense;
}

void Armor::use(Fighter* target)
{
	target->setDefense(target->getDefense() + this->getDefense());
}
