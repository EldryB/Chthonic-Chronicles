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

	this->createMovementComponent(120.5f, 10.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 0, 3, 0, 46, 46);
	this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 4, 0, 7, 0, 46, 46);
	this->animationComponent->addAnimation("WALK_UP", 10.f, 8, 0, 11, 0, 46, 46);
	this->animationComponent->addAnimation("WALK_DOWN", 10.f, 12, 0, 15, 0, 46, 46);
}

Fighter::~Fighter()
{

}

void Fighter::update(const float& _dt)
{
	this->movementComponent->update(_dt);

	switch (this->movementComponent->getLookingDirection())
	{
	case LookingDirections::Left:
		this->animationComponent->play("WALK_LEFT", _dt);

	case LookingDirections::Right:
		this->animationComponent->play("WALK_RIGHT", _dt);

	case LookingDirections::Up:
		this->animationComponent->play("WALK_UP", _dt);

	case LookingDirections::Down:
		this->animationComponent->play("WALK_UP", _dt);

	default:
		break;
	}

	/*this->animationComponent->play("WALK_RIGHT", _dt);*/
}
