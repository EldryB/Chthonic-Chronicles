#include "MovementComponent.hpp"
#include "GameState.hpp"

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

	sf::Sprite* spr = &this->sprite;
	if (this->stages == CurrentStage::MainStage)
	{
		this->setMainStageLimits(spr, lastX, lastY);
	}
	else if (this->stages == CurrentStage::Lvl1R1)
	{
		this->setDefaultLimits(spr, lastX, lastY);
	}

	this->setLvl1Limits(spr, lastX, lastY);
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

void MovementComponent::setLvl1Limits(sf::Sprite* spr, float& lastx, float& lasty)
{
	if(stages == CurrentStage::Lvl1R1)
	{
		if (getXPos(spr) < 50 && (getYPos(spr) < 328 || getYPos(spr) > 416))
		{
			spr->setPosition(lastx, lasty);
		}

		if (getYPos(spr) < 183 || getYPos(spr) > 509)
		{
			spr->setPosition(lastx, lasty);
		}
	}

	else if (stages == CurrentStage::Lvl1R2)
	{
		if (getXPos(spr) > 718 && getXPos(spr) < 941 && (getYPos(spr) < 321 || getYPos(spr) > 414) )
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 660 && getXPos(spr) <= 718 && (getYPos(spr) < 277 || getYPos(spr) > 414))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 600 && getXPos(spr) <= 660 && (getYPos(spr) < 229 || getYPos(spr) > 461))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 430 && getXPos(spr) <= 600 && (getYPos(spr) < 179 || getYPos(spr) > 508))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 335 && getXPos(spr) <= 430 && (getYPos(spr) > 508))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 160 && getXPos(spr) <= 335 && (getYPos(spr) < 179 || getYPos(spr) > 508))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 99 && getXPos(spr) <= 160 && (getYPos(spr) < 229 || getYPos(spr) > 461))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 43 && getXPos(spr) <= 99 && (getYPos(spr) < 277 || getYPos(spr) > 414))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) <= 43)
		{
			spr->setPosition(lastx, lasty);
		}
	}

	else if (stages == CurrentStage::Lvl1R3)
	{
		if (getXPos(spr) <= 41)
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 41 && getXPos(spr) <= 186 && (getYPos(spr) < 154 || getYPos(spr) > 425))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 186 && getXPos(spr) <= 335 && (getYPos(spr) > 425))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 335 && getXPos(spr) <= 430 && (getYPos(spr) < 154))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 430 && getXPos(spr) <= 770 && (getYPos(spr) < 154 || getYPos(spr) > 425))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 770 && (getYPos(spr) < 226 || getYPos(spr) > 331))
		{
			spr->setPosition(lastx, lasty);
		}
	}

	else if (stages == CurrentStage::Lvl1R4)
	{
		if (getXPos(spr) > 48 && getXPos(spr) <= 91 && (getYPos(spr) < 226 || getYPos(spr) > 331))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 91 && getXPos(spr) <= 178 && (getYPos(spr) < 248 || getYPos(spr) > 422))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 178 && getXPos(spr) <= 602 && (getYPos(spr) < 341 || getYPos(spr) > 422))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 602 && getXPos(spr) <= 684 && (getYPos(spr) < 295 || getYPos(spr) > 422))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 684 && getXPos(spr) <= 900 && (getYPos(spr) < 295 || getYPos(spr) > 375))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) >  900)
		{
			spr->setPosition(lastx, lasty);
		}
	}
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

