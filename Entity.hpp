#pragma once

#include "Settings.hpp"

class Entity
{
public:
	Entity();

	Entity(float _x, float _y, sf::Texture* _texture, std::string _name) noexcept;

	Entity(const Entity&) = delete;

	Entity& operator = (Entity&) = delete;

	virtual ~Entity();

	virtual sf::Sprite* getSprite() noexcept;

	virtual void setSprite(sf::Texture* _texture);
	
	virtual void setSprite(sf::Sprite* sprite);

	virtual void setPosition(const float _x, const float _y);
	
	virtual void setName(std::string _name);

	virtual void move(const float& _dt, const float dir_x, const float dir_y);

	virtual void update(const float& _dt);

	virtual void render(sf::RenderTarget* target);

	virtual void animate(float& timeSinceLastUpdate, float& timeBetweenUpdates, std::vector<sf::Texture>& Myvector, int& currentFrame);

private:
	void initVariables();

protected:
	sf::Texture* texture;
	sf::Sprite* sprite;
	
	float x;
	float y;
	float movementSpeed;
 
	std::string name;
};


