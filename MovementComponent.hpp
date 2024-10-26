#pragma once

#include "Settings.hpp"

enum class LookingDirection
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

	const LookingDirection& getLookingDirection() const;

	const bool& isIdle() const;

	const bool& isIdle(const LookingDirection& look_direction) const;

	const bool& isMoving() const;

	const bool& isMoving(const LookingDirection& look_direction) const;

	void setLookingDirection(LookingDirection _l);

	void move(const float dir_x, const float dir_y, const float& _dt);

	void update(const float& _dt);

	//Funciones usadas en la limitacion del mapa 

	float getXPos(sf::Sprite* spr);

	float getYPos(sf::Sprite* spr);

	void setXPos(float _x, sf::Sprite* sprite);

	void setYPos(float _y, sf::Sprite* sprite);

	void setStage(CurrentStage _c);

	void setMainStageLimits(sf::Sprite* spr, float& lastx, float& lasty);

private:
	sf::Sprite& sprite;
	float maxVelocity;
	float acceleration;
	float deceleration;
	LookingDirection lookingDirection;
	sf::Vector2f velocity;
	CurrentStage currentStage = CurrentStage::MainStage;

};

