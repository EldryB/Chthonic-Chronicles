#include "Fighter.hpp"

void Fighter::initVariables(std::string& _name, float& _hp, float& _attackPower, int& _defense, int& _initiative)
{
	this->name = _name;
	this->hp = _hp;
	this->attackPower = _attackPower;
	this->defense = _defense;
	this->initiative = _initiative;
}

Fighter::Fighter(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float _attackPower, int _defense, int _initiative)
{
	this->initVariables(_name, _hp, _attackPower, _defense, _initiative);
	this->setPosition(_x, _y);
}

Fighter::~Fighter()
{

}

float Fighter::getHp() const
{
	return this->hp;
}

float Fighter::getAttackPower() const
{
	return this->attackPower;
}

int Fighter::getDefense() const
{
	return this->defense;
}

int Fighter::getInitiative() const
{
	return this->initiative;
}

void Fighter::setHp(float _hp)
{
	this->hp = _hp;
}

void Fighter::setAttackPower(float attack_power)
{
	this->attackPower = attack_power;
}

void Fighter::setDefense(int _defense)
{
	this->defense = _defense;
}

void Fighter::setInitiative(int _initiative)
{
	this->initiative = _initiative;
}

void Fighter::setAttributes(float _x, float _y, std::string _name, float _hp, float _damage)
{
	this->sprite->setPosition(_x, _y);
	this->name = _name;
	this->hp = _hp;
	this->attackPower = _damage;
}

void Fighter::attack(Fighter* target)
{
	target->takeDamage(this->attackPower);
}

void Fighter::takeDamage(float _attackPower)
{
	float takeDamage = _attackPower * (100.f / (100.f + this->defense));
	this->hp -= takeDamage;

	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

bool Fighter::isAlive() const
{
	return this->hp > 0;
}

void Fighter::update(const float& _dt)
{
	
}
