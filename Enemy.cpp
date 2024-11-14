#include "Enemy.hpp"

Enemy::Enemy(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float _attackPower, int _defense, int _initiative)
	: Fighter (_x, _y, texture_sheet, _name, _hp, _attackPower, _defense, _initiative)
{
	this->setTexture(texture_sheet);
	
	this->createAnimationComponent(texture_sheet);
}

Enemy::~Enemy()
{

}

void Enemy::addItem(Item* _item)
{
	this->items.push_back(_item);
}

Item* Enemy::dropItem()
{
	Dice dice = Dice(this->items.size());
	int index = dice.getFace();

	return this->items[index - 1];
}

void Enemy::update(const float& _dt)
{

}

Skeleton::Skeleton(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float attack_power, int _defense, int _initiative)
	: Enemy(_x, _y, texture_sheet, _name, _hp, attack_power, _defense, _initiative)
{
	this->animationComponent->addAnimation("SKELETON_IDLE_LEFT", 40.f, 4, 0, 7, 0, 40, 40);
}

Skeleton::~Skeleton()
{

}

void Skeleton::update(const float& _dt)
{
	this->animationComponent->play("SKELETON_IDLE_LEFT", _dt);
}

Slime::Slime(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float attack_power, int _defense, int _initiative)
	: Enemy(_x, _y, texture_sheet, _name, _hp, attack_power, _defense, _initiative)
{
	this->animationComponent->addAnimation("SLIME_IDLE_LEFT", 40.f, 12, 0, 15, 0, 40, 40);
}

Slime::~Slime()
{

}

void Slime::update(const float& _dt)
{
	this->animationComponent->play("SLIME_IDLE_LEFT", _dt);
}

Bat::Bat(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float attack_power, int _defense, int _initiative)
	: Enemy(_x, _y, texture_sheet, _name, _hp, attack_power, _defense, _initiative)
{
	this->animationComponent->addAnimation("BAT_IDLE_LEFT", 40.f, 8, 0, 11, 0, 40, 40);
}

Bat::~Bat()
{

}

void Bat::update(const float& _dt)
{
	this->animationComponent->play("BAT_IDLE_LEFT", _dt);
}

Rat::Rat(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float attack_power, int _defense, int _initiative)
	: Enemy(_x, _y, texture_sheet, _name, _hp, attack_power, _defense, _initiative)
{
	this->animationComponent->addAnimation("RAT_IDLE_LEFT", 40.f, 0, 0, 3, 0, 40, 40);
}

Rat::~Rat()
{

}

void Rat::update(const float& _dt)
{
	this->animationComponent->play("RAT_IDLE_LEFT", _dt);
}
