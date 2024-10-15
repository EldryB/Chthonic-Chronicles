#include "Fighter.hpp"

void Fighter::initVariables()
{

}

void Fighter::initComponents()
{

}

Fighter::Fighter(float _x, float _y, sf::Texture& texture_sheet, std::string _name)
{
	this->initVariables();

	this->setPosition(_x, _y);
	this->name = _name;

	this->createMovementComponent(120.5f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("LEFT", 10.f, 1, 0, 3, 0, 58, 50);
}

Fighter::~Fighter()
{

}

void Fighter::update(const float& _dt)
{
	this->movementComponent->update(_dt);

	this->animationComponent->play("LEFT", _dt);
}
