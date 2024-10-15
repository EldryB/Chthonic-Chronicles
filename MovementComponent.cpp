#include "MovementComponent.hpp"

MovementComponent::MovementComponent(sf::Sprite& _sprite, 
	float _maxVelocity, float _aceleration, float _deceleration)
	: sprite{_sprite}, 
	maxVelocity{_maxVelocity}, acceleration{_aceleration}, deceleration{_deceleration}
{
	
}

MovementComponent::~MovementComponent()
{

}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const LookingDirections& MovementComponent::getLookingDirection() 
{
	if (this->getVelocity().x < 0.f)
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
	}

	return this->lookingDirection;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& _dt)
{
	this->velocity.x += this->acceleration * dir_x;
	this->velocity.y += this->acceleration * dir_y;
}

void MovementComponent::update(const float& _dt)
{
	if (this->velocity.x < 0.f)
	{
		if (this->velocity.x < -this->maxVelocity)
		{
			this->velocity.x = -this->maxVelocity;
		}
		
		this->velocity.x += this->deceleration;
		if (this->velocity.x > 0.f)
		{
			this->velocity.x = 0.f;
		}
	}
	else if (this->velocity.x > 0.f)
	{
		if (this->velocity.x > this->maxVelocity)
		{
			this->velocity.x = this->maxVelocity;
		}
		
		this->velocity.x -= this->deceleration;
		if (this->velocity.x < 0.f)
		{
			this->velocity.x = 0.f;
		}
	}
	
	if (this->velocity.y > 0.f)
	{
		if (this->velocity.y > this->maxVelocity)
		{
			this->velocity.y = this->maxVelocity;
		}

		this->velocity.y -= this->deceleration;
		if (this->velocity.y < 0.f)
		{
			this->velocity.y = 0.f;
		}
	}
	else if (this->velocity.y < 0.f)
	{
		if (this->velocity.y < -this->maxVelocity)
		{
			this->velocity.y = -this->maxVelocity;
		}

		this->velocity.y += this->deceleration;
		if (this->velocity.y > 0.f)
		{
			this->velocity.y = 0.f;
		}
	}

	this->sprite.move(this->velocity * _dt);
}
