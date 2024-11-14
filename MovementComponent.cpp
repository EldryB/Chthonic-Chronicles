#include "MovementComponent.hpp"
#include "GameState.hpp"
#include "Limit.hpp"

MovementComponent::MovementComponent(sf::Sprite& _sprite, 
	float _maxVelocity, float _aceleration, float _deceleration)
	: sprite{_sprite}, 
	maxVelocity{_maxVelocity}, acceleration{_aceleration}, deceleration{_deceleration}
{
	this->velocity.x = this->velocity.y = 0.f;
	this->stages = (CurrentStage::MainStage);
}

MovementComponent::~MovementComponent()
{

}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const LookingDirection& MovementComponent::getLookingDirection() const
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

const bool& MovementComponent::isIdle(const LookingDirection& look_direction) const
{
	return this->isIdle() && this->getLookingDirection() == look_direction;
}

const bool& MovementComponent::isMoving() const
{
	if (this->velocity.x != 0.f || this->velocity.y != 0.f)
	{
		return true;
	}
	return false;
}

const bool& MovementComponent::isMoving(const LookingDirection& look_direction) const
{
	return this->isMoving() && this->getLookingDirection() == look_direction;
}

void MovementComponent::setLookingDirection(LookingDirection _l)
{
	this->lookingDirection = _l;
}

void MovementComponent::pushStage(CurrentStage _c)
{
	stages = _c;
}

CurrentStage MovementComponent::getStage()
{
	return this->stages;
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
		this->lookingDirection = LookingDirection::Left;

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
		this->lookingDirection = LookingDirection::Right;

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
		this->lookingDirection = LookingDirection::Down;

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
		this->lookingDirection = LookingDirection::Up;
		
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
	bool isInLvl1 = isInLvl1 = (this->stages == CurrentStage::Lvl1R1) || (this->stages == CurrentStage::Lvl1R2) || (this->stages == CurrentStage::Lvl1R3) ||
		(this->stages == CurrentStage::Lvl1R4) || (this->stages == CurrentStage::Lvl1R5) || (this->stages == CurrentStage::Lvl1R6) ||
		(this->stages == CurrentStage::Lvl1R7) || (this->stages == CurrentStage::Lvl1R8);

	sf::Sprite* spr = &this->sprite;
	if (this->stages == CurrentStage::MainStage)
	{
		this->setMainStageLimits(spr, lastX, lastY);
	}
	
	if(isInLvl1)
	{
		this->setLvl1Limits(spr, lastX, lastY);
	}

	if (this->stages == CurrentStage::StoreStage || this->stages == CurrentStage::StoreStage2)
	{
		this->setStoreLimits(spr, lastX, lastY);
	}
	this->setDefaultLimits(spr, lastX, lastY);
	this->sprite = *spr;
}

float MovementComponent::getXPos(sf::Sprite* spr)
{
	return spr->getPosition().x;
}

float MovementComponent::getYPos(sf::Sprite* spr)
{
	return spr->getPosition().y;
}

void MovementComponent::setXPos(float _x, sf::Sprite* sprite)
{
	float _y = sprite->getPosition().y;
	sprite->setPosition(_x, _y);
}
void MovementComponent::setYPos(float _y, sf::Sprite* sprite)
{
	float _x = sprite->getPosition().x;
	sprite->setPosition(_x, _y);
}

void MovementComponent::setDefaultLimits(sf::Sprite* spr, float& lastx, float& lasty)
{
	if (getYPos(spr) < 0 || getYPos(spr) > Settings::WINDOW_HEIGHT - spr->getGlobalBounds().height)
	{
		spr->setPosition(lastx, lasty);
	}

	if (getXPos(spr) < 0 || getXPos(spr) > Settings::WINDOW_WIDTH - spr->getGlobalBounds().width)
	{
		spr->setPosition(lastx, lasty);
	}
}