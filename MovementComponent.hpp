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
	MovementComponent(sf::Sprite& _sprite, float _maxVelocity);

	virtual ~MovementComponent();

	const sf::Vector2f& getVelocity() const;

	const LookingDirections& getLookingDirection() const;

	void move(const float dir_x, const float dir_y, const float& _dt);

	void update(const float& _dt);

private:
	sf::Sprite& sprite;
	float maxVelocity;
	LookingDirections lookingDirection;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f deceleration;
};

