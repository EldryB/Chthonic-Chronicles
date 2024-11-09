#include "Enemy.hpp"

Enemy::Enemy(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float _attackPower, int _defense, int _initiative)
	: Fighter (_x, _y, texture_sheet, _name, _hp, _attackPower, _defense, _initiative)
{
	this->setTexture(texture_sheet);
	
	this->createAnimationComponent(texture_sheet);
	this->animationComponent->addAnimation("RAT_IDLE_LEFT", 40.f, 0, 0, 3, 0, 40, 40);
	this->animationComponent->addAnimation("SKELETON_IDLE_LEFT", 40.f, 4, 0, 7, 0, 40, 40);
	this->animationComponent->addAnimation("BAT_IDLE_LEFT", 40.f, 8, 0, 11, 0, 40, 40);
	this->animationComponent->addAnimation("SLIME_IDLE_LEFT", 40.f, 12, 0, 15, 0, 40, 40);
}

Enemy::~Enemy()
{

}

Item* Enemy::dropItem()
{
	Dice dice;
	int index = dice.roll(2);

	return this->items[index - 1];
}

void Enemy::update(const float& _dt)
{
	this->animationComponent->play("SLIME_IDLE_LEFT", _dt);
}


