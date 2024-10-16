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
	this->setMainStageLimits(spr, lastX, lastY);
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

void MovementComponent::setMainStageLimits(sf::Sprite* sprite, float& lastx, float& lasty)
{
	if (getXPos(sprite) < 170)
	{
		sprite->setPosition(lastx, lasty);
	}
	if (getXPos(sprite) > 170 && getXPos(sprite) < 307 && getYPos(sprite) > 399)
	{
		sprite->setPosition(lastx, lasty);
	}
	if (getXPos(sprite) >= 170 && getXPos(sprite) < 300)
	{
		if (getYPos(sprite) < 360)
		{
			sprite->setPosition(lastx, lasty);
		}

		else if (getYPos(sprite) > 430)
		{
			sprite->setPosition(lastx, lasty);
		}
	}
	if (getXPos(sprite) >= 369 && getXPos(sprite) < 700)
	{


		if (getYPos(sprite) > 370)
		{
			sprite->setPosition(lastx, lasty);
		}
	}

	if (getXPos(sprite) >= 300 && getXPos(sprite) <= 370)
	{
		int marca = 300;
		int marca_y = 430;
		if (getXPos(sprite) < 351)
		{
			if (getYPos(sprite) < 350)
			{
				sprite->setPosition(lastx, lasty);
			}
		}
		//Parte de abajo con movilidad escalera
		if (getXPos(sprite) >= marca + 0 && getXPos(sprite) < marca + 5)
		{
			if (getYPos(sprite) > marca_y - 5)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 5 && getXPos(sprite) < marca + 10)
		{
			if (getYPos(sprite) > marca_y - 10)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 10 && getXPos(sprite) < marca + 15)
		{
			if (getYPos(sprite) > marca_y - 15)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 15 && getXPos(sprite) < marca + 20)
		{
			if (getYPos(sprite) > marca_y - 20)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 20 && getXPos(sprite) < marca + 25)
		{
			if (getYPos(sprite) > marca_y - 25)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 25 && getXPos(sprite) < marca + 30)
		{
			if (getYPos(sprite) > marca_y - 30)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 30 && getXPos(sprite) < marca + 35)
		{
			if (getYPos(sprite) > marca_y - 35)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 35 && getXPos(sprite) < marca + 40)
		{
			if (getYPos(sprite) > marca_y - 40)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 40 && getXPos(sprite) < marca + 45)
		{
			if (getYPos(sprite) > marca_y - 45)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 45 && getXPos(sprite) < marca + 50)
		{
			if (getYPos(sprite) > marca_y - 50)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 50 && getXPos(sprite) < marca + 55)
		{
			if (getYPos(sprite) > marca_y - 55)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 55 && getXPos(sprite) <= marca + 75)
		{
			if (getYPos(sprite) > marca_y - 60)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

	}

	if (getXPos(sprite) > 370 && getXPos(sprite) < 640)
	{
		if (getYPos(sprite) > 530)
		{
			sprite->setPosition(lastx, lasty);
		}
		//Parte de arriba del puente
		if (getXPos(sprite) >= 460 && getXPos(sprite) < 585)
		{
			{
				if (getYPos(sprite) > 370)
				{
					sprite->setPosition(lastx, lasty);
				}
				int marca = 460;
				int marca_y = 335;
				if (getXPos(sprite) >= marca + 0 && getXPos(sprite) < marca + 5)
				{
					if (getYPos(sprite) < marca_y - 5)
					{
						sprite->setPosition(lastx, lasty);
					}
				}

				else if (getXPos(sprite) >= marca + 5 && getXPos(sprite) < marca + 10)
				{
					if (getYPos(sprite) < marca_y - 10)
					{
						sprite->setPosition(lastx, lasty);
					}
				}
				else if (getXPos(sprite) >= marca + 10 && getXPos(sprite) < marca + 15)
				{
					if (getYPos(sprite) < marca_y - 15)
					{
						sprite->setPosition(lastx, lasty);
					}
				}
				else if (getXPos(sprite) >= marca + 15 && getXPos(sprite) < marca + 20)
				{
					if (getYPos(sprite) < marca_y - 20)
					{
						sprite->setPosition(lastx, lasty);
					}
				}
				else if (getXPos(sprite) >= marca + 20 && getXPos(sprite) < marca + 25)
				{
					if (getYPos(sprite) < marca_y - 25)
					{
						sprite->setPosition(lastx, lasty);
					}
				}
				else if (getXPos(sprite) >= marca + 25 && getXPos(sprite) < marca + 30)
				{
					if (getYPos(sprite) < marca_y - 30)
					{
						sprite->setPosition(lastx, lasty);
					}
				}
				else
				{
					if (getYPos(sprite) < marca_y - 35)
					{
						sprite->setPosition(lastx, lasty);
					}
				}
			}
		}

		else if (getXPos(sprite) >= 585 && getXPos(sprite) < 620)
		{
			int marca = 585;
			int marca_y = 335;

			if (getYPos(sprite) > 370)
			{
				sprite->setPosition(lastx, lasty);
			}

			if (getXPos(sprite) >= marca + 0 && getXPos(sprite) < marca + 5)
			{
				if (getYPos(sprite) < marca_y - 35)
				{
					sprite->setPosition(lastx, lasty);
				}
			}

			else if (getXPos(sprite) >= marca + 5 && getXPos(sprite) < marca + 10)
			{
				if (getYPos(sprite) < marca_y - 35 + 10)
				{
					sprite->setPosition(lastx, lasty);
				}
			}

			else if (getXPos(sprite) >= marca + 10 && getXPos(sprite) < marca + 15)
			{
				if (getYPos(sprite) < marca_y - 35 + 15)
				{
					sprite->setPosition(lastx, lasty);
				}
			}

			else if (getXPos(sprite) >= marca + 15 && getXPos(sprite) < marca + 20)
			{
				if (getYPos(sprite) < marca_y - 35 + 20)
				{
					sprite->setPosition(lastx, lasty);
				}
			}

			else if (getXPos(sprite) >= marca + 20 && getXPos(sprite) < marca + 25)
			{
				if (getYPos(sprite) < marca_y - 35 + 25)
				{
					sprite->setPosition(lastx, lasty);
				}
			}

			else if (getXPos(sprite) >= marca + 25 && getXPos(sprite) < marca + 30)
			{
				if (getYPos(sprite) < marca_y - 35 + 30)
				{
					sprite->setPosition(lastx, lasty);
				}
			}

			else if (getXPos(sprite) >= marca + 30 && getXPos(sprite) < marca + 35)
			{
				if (getYPos(sprite) < marca_y - 35 + 35)
				{
					sprite->setPosition(lastx, lasty);
				}
			}
		}


		else
		{
			if (getXPos(sprite) > 400)
			{
				if (getYPos(sprite) < 340)
				{
					sprite->setPosition(lastx, lasty);
				}
			}
			else if (getYPos(sprite) > 370)
			{
				sprite->setPosition(lastx, lasty);
			}
		}
	}

	if (getXPos(sprite) >= 330 && getXPos(sprite) <= 400 && getYPos(sprite) < 260)
	{
		sprite->setPosition(lastx, lasty);
	}

	if (getXPos(sprite) > 640 && getXPos(sprite) < 660)
	{
		if (getYPos(sprite) < 340)
		{
			sprite->setPosition(lastx, lasty);
		}
		if (getYPos(sprite) > 370)
		{
			sprite->setPosition(lastx, lasty);
		}
	}

	if (getXPos(sprite) >= 660)
	{
		if (getYPos(sprite) < 323)
		{
			sprite->setPosition(lastx, lasty);
		}
	}

	if (getXPos(sprite) > 860 && (getYPos(sprite) > 322 && getYPos(sprite) <= 331))
	{
		if (getXPos(sprite) > 934)
		{
			sprite->setPosition(lastx, lasty);
		}
	}

	if (getXPos(sprite) > 830 && (getYPos(sprite) > 350 && getYPos(sprite) <= 380))
	{
		sprite->setPosition(lastx, lasty);
	}

	if (getXPos(sprite) >= 710 && (getYPos(sprite) >= 330 && getYPos(sprite) <= 350))
	{
		sprite->setPosition(lastx, lasty);
	}

	if (getXPos(sprite) >= 660 && getXPos(sprite) <= 830 && (getYPos(sprite) > 370))
	{
		sprite->setPosition(lastx, lasty);
	}


}

