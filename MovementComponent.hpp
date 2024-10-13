#pragma once

#include "Settings.hpp"

class MovementComponent
{
public:
	MovementComponent(sf::Sprite& _sprite, float _maxVelocity);

	virtual ~MovementComponent();

	const sf::Vector2f& getVelocity() const;

	void move(const float dir_x, const float dir_y, const float& _dt);

	void update(const float& dt);

private:
	sf::Sprite& sprite;
	float maxVelocity;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f deceleration;
};

