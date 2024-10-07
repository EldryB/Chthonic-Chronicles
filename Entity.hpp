#pragma once

#include "Settings.hpp"

class Entity
{
public:
	Entity();

	Entity(float _x, float _y, float _width, float _height) noexcept;

	Entity(float _x, float _y, float _width, float _height, sf::Sprite _sprite) noexcept;

	Entity(const Entity&) = delete;

	Entity& operator = (Entity&) = delete;

	virtual ~Entity();

	sf::Sprite get_sprite() noexcept;

	void setName(std::string _name);

	virtual void move(const float& _dt, const float dir_x, const float dir_y);

	virtual void update(const float& _dt);

	virtual void render(sf::RenderTarget* target);

protected:
	float x;
	float y;
	float width;
	float height;
	float movementSpeed;
	sf::Texture texture;
	sf::Sprite sprite;
	std::string name;
};


