#include "MovementComponent.hpp"
#include "GameState.hpp"

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

const LookingDirections& MovementComponent::getLookingDirection() const
{
	return this->lookingDirection;
}

const bool& MovementComponent::isIdle() const
{
	if (this->velocity.x == 0.f && this->velocity.y == 0.f)
	{
		return true;
	}
	return false;
}

const bool& MovementComponent::isIdle(const LookingDirections& look_direction) const
{
	return this->isIdle() && this->getLookingDirection() == look_direction;
}

const bool& MovementComponent::isMovingLeft() const
{
	if (this->velocity.x < 0.f)
	{
		return true;
	}
	return false;
}

const bool& MovementComponent::isMovingRight() const
{
	if (this->velocity.x > 0.f)
	{
		return true;
	}
	return false;
}

const bool& MovementComponent::isMovingUp() const
{
	if (this->velocity.y < 0.f)
	{
		return true;
	}
	return false;
}

const bool& MovementComponent::isMovingDown() const
{
	if (this->velocity.y > 0.f)
	{
		return true;
	}
	return false;
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
		this->lookingDirection = LookingDirections::Left;

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
		this->lookingDirection = LookingDirections::Right;

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
		this->lookingDirection = LookingDirections::Down;

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
		this->lookingDirection = LookingDirections::Up;
		
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
	float lastX = this->sprite.getPosition().x;
	float lastY = this->sprite.getPosition().y;
	this->sprite.move(this->velocity * _dt);

	sf::Sprite* spr = &this->sprite;
	GameState::setMainStageLimits(spr, lastX, lastY);
	this->sprite = *spr;
}
