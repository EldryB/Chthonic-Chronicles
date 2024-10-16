#pragma once

#include "Settings.hpp"

enum class LookingDirections
{
	Left,
	Right,
	Up,
	Down
};

class MovementComponent
{
public:
	MovementComponent(sf::Sprite& _sprite, 
		float _maxVelocity, float _aceleration, float _deceleration);

	virtual ~MovementComponent();

	const sf::Vector2f& getVelocity() const;

	const LookingDirections& getLookingDirection() const;

	const bool& isIdle() const;

	const bool& isIdle(const LookingDirections& _lookDirection) const;

	const bool& isMovingLeft() const;

	const bool& isMovingRight() const;

	const bool& isMovingUp() const;

	const bool& isMovingDown() const;

	void move(const float dir_x, const float dir_y, const float& _dt);

	void update(const float& _dt);

	//Funciones usadas en la limitacion del mapa 

	float getXPos(sf::Sprite* spr);

	float getYPos(sf::Sprite* spr);

	void setXPos(float _x, sf::Sprite* sprite);

	void setYPos(float _y, sf::Sprite* sprite);

	void setMainStageLimits(sf::Sprite* spr, float& lastx, float& lasty);

private:
	sf::Sprite& sprite;
	float maxVelocity;
	float acceleration;
	float deceleration;
	LookingDirections lookingDirection;
	sf::Vector2f velocity;

};

