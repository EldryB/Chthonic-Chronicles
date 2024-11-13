#include "Player.hpp"

Player::Player(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float _attackPower, int _defense, int _initiative)
	: Fighter(_x, _y, texture_sheet, _name, _hp, _attackPower, _defense, _initiative)
{
	this->jobs = new Jobs();
	this->resources = new Resources();

	this->createMovementComponent(150.f, 10.f, 5.f);
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

Player::~Player()
{

}

std::vector<Item*>* Player::getInventory() const
{
	return this->inventory;
}

Jobs* Player::getJobs() const
{
	return this->jobs;
}

Resources* Player::getResources() const
{
	return this->resources;
}

Weapon* Player::getWeapon() const
{
	return this->weapon;
}

Armor* Player::getArmor() const
{
	return this->armor;
}

void Player::setWeapon(Weapon* _weapon)
{
	this->weapon = _weapon;
}

void Player::setArmor(Armor* _armor)
{
	this->armor = _armor;
}

void Player::update(const float& _dt)
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

void Player::addItem(Item* _item)
{
	this->inventory->push_back(_item);
}