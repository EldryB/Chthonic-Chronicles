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

	this->createMovementComponent(120.5f, 10.f, 5.f);
	this->createAnimationComponent(texture_sheet);
	
	this->animationComponent->addAnimation("IDLE_LEFT", 40.f, 0, 0, 1, 0, 46, 46);
	this->animationComponent->addAnimation("WALK_LEFT", 10.f, 2, 0, 5, 0, 46, 46);
	this->animationComponent->addAnimation("IDLE_RIGHT", 40.f, 6, 0, 7, 0, 46, 46);
	this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 8, 0, 11, 0, 46, 46);
	this->animationComponent->addAnimation("IDLE_UP", 40.f, 12, 0, 12, 0, 46, 46);
	this->animationComponent->addAnimation("WALK_UP", 10.f, 13, 0, 16, 0, 46, 46);
	this->animationComponent->addAnimation("IDLE_DOWN", 40.f, 17, 0, 18, 0, 46, 46);
	this->animationComponent->addAnimation("WALK_DOWN", 10.f, 19, 0, 22, 0, 46, 46);
}

Fighter::~Fighter()
{

}

float Fighter::getHp() const
{
	return this->hp;
}

float Fighter::getDamage() const
{
	return this->attackPower;
}

void Fighter::setHp(float _hp)
{
	this->hp = _hp;
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

}

void Fighter::takeDamage(float _attackPower)
{
	float takeDamage = _attackPower * (100 / (100 + this->defense));
	this->hp -= takeDamage;
}

bool Fighter::isAlive() const
{
	return this->hp > 0;
}

void Fighter::update(const float& _dt)
{
	this->movementComponent->update(_dt);

	if (this->movementComponent->isIdle(LookingDirection::Left))
	{
		this->animationComponent->play("IDLE_LEFT", _dt);
	}
	else if (this->movementComponent->isIdle(LookingDirection::Right))
	{
		this->animationComponent->play("IDLE_RIGHT", _dt);
	}
	else if (this->movementComponent->isIdle(LookingDirection::Up))
	{
		this->animationComponent->play("IDLE_UP", _dt);
	}
	else if (this->movementComponent->isIdle(LookingDirection::Down))
	{
		this->animationComponent->play("IDLE_DOWN", _dt);
	}
	else if (this->movementComponent->isMoving(LookingDirection::Left))
	{
		this->animationComponent->play("WALK_LEFT", _dt);
	}
	else if (this->movementComponent->isMoving(LookingDirection::Right))
	{
		this->animationComponent->play("WALK_RIGHT", _dt);
	}
	else if (this->movementComponent->isMoving(LookingDirection::Up))
	{
		this->animationComponent->play("WALK_UP", _dt);
	}
	else if (this->movementComponent->isMoving(LookingDirection::Down))
	{
		this->animationComponent->play("WALK_DOWN", _dt);
	}
}
