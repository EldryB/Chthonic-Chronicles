#include "Equipable.hpp"

Equipable::Equipable(sf::Texture& _texture, std::string _name, int _initiative, std::string _description, int _price) 
	: initiative(_initiative), equipped(false), Item(_texture, _name, _description, _price)
{
	this->equipped = false;
}

Equipable::~Equipable()
{

}

int Equipable::getInitiative() const
{
	return this->initiative;
}

bool Equipable::isEquipped() const
{
	return this->equipped;
}

void Equipable::use(Fighter* target)
{

}

Weapon::Weapon(sf::Texture& _texture, std::string _name, float attack_power, int _initiative, std::string _description, int _price)
	: attackPower(attack_power), Equipable(_texture, _name, _initiative, _description, _price)
{

}

Weapon::~Weapon()
{

}

float Weapon::getAttackPower() const
{
	return this->attackPower;
}

void Weapon::setAtributes(int _ini, float _attack)
{
	this->initiative = _ini;
	this->attackPower = _attack;
}

void Weapon::use(Fighter* target)
{
	if(!this->equipped)
	{
		this->equipped = true;
		target->setAttackPower(target->getAttackPower() + this->getAttackPower());
		target->setInitiative(target->getInitiative() + this->getInitiative());
	}
	else 
	{
		this->equipped = false;
		target->setAttackPower(target->getAttackPower() - this->getAttackPower());
		target->setInitiative(target->getInitiative() - this->getInitiative());
	}
}

Armor::Armor(sf::Texture& _texture, std::string _name, int _defense, int _initiative, std::string _description, int _price)
	: defense(_defense), Equipable(_texture, _name, _initiative, _description, _price)
{

}

Armor::~Armor()
{

}

int Armor::getDefense() const
{
	return this->defense;
}

void Armor::setAtributes(int _ini, int _defense)
{
	this->initiative = _ini;
	this->defense = _defense;
}

void Armor::use(Fighter* target)
{
	if (!this->equipped)
	{
		this->equipped = true;
		target->setDefense(target->getDefense() + this->getDefense());
		target->setInitiative(target->getInitiative() + this->getInitiative());
	}
	else
	{
		this->equipped = false;
		target->setDefense(target->getDefense() - this->getDefense());
		target->setInitiative(target->getInitiative() - this->getInitiative());
	}
}
