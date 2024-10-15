#include "MovementComponent.hpp"

MovementComponent::MovementComponent(sf::Sprite& _sprite, float _maxVelocity)
	: sprite{_sprite}, maxVelocity{_maxVelocity}
{
	
}

MovementComponent::~MovementComponent()
{

}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const LookingDirections& MovementComponent::getLookingDirection() const
{
	return this->lookingDirection;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& _dt)
{
	this->velocity.x = this->maxVelocity * dir_x;
	this->velocity.y = this->maxVelocity * dir_y;

	this->sprite.move(this->velocity * _dt);
}

void MovementComponent::update(const float& _dt)
{
	/*if (this->getVelocity().x < 0.f)
	{
		this->lookingDirection = LookingDirections::Left;
	}
	else if (this->getVelocity().x > 0.f)
	{
		this->lookingDirection = LookingDirections::Right;
	}
	if (this->getVelocity().y < 0.f)
	{
		this->lookingDirection = LookingDirections::Up;
	}
	else if (this->getVelocity().y > 0.f)
	{
		this->lookingDirection = LookingDirections::Down;
	}*/

	
}
