#include "Fighter.hpp"

void Fighter::initVariables()
{

}

void Fighter::initComponents()
{

}

Fighter::Fighter(float _x, float _y, sf::Texture& texture_sheet, std::string _name)
{


	this->setPosition(_x, _y);
	this->name = _name;

	this->createMovementComponent(120.5f, 10.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	//Faltan los idles
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
