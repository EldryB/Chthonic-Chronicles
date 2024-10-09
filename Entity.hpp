#pragma once

#include "Settings.hpp"

class Entity
{
public:
	Entity();

	Entity(float _x, float _y, float _width, float _height) noexcept;

	Entity(float _x, float _y, float _width, float _height, sf::Texture _texture, std::string _name) noexcept;

	Entity(const Entity&) = delete;

	Entity& operator = (Entity&) = delete;

	virtual ~Entity();

	sf::Sprite get_sprite() noexcept;

	void setPosition(float _x, float _y);
	
	void setName(std::string _name);

	virtual void move(const float& _dt, const float dir_x, const float dir_y);

	virtual void update(const float& _dt);

	virtual void render(sf::RenderTarget* target);

	virtual void animation(float& timeSinceLastUpdate, float& timeBetweenUpdates, std::vector<sf::Texture>& Myvector, int& currentFrame);

	void setSprite(sf::Sprite& sprite);

protected:
	float x;
	float y;
	float width;
	float height;
	float movementSpeed;
	sf::Texture texture; //Change to pointer
	sf::Sprite sprite; //Maybe change to pointer
	std::string name;
};


