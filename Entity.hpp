#pragma once

#include "MovementComponent.hpp"

class Entity
{
public:
	Entity();

	Entity(float _x, float _y, sf::Texture* _texture, std::string _name) noexcept;

	Entity(const Entity&) = delete;

	Entity& operator = (Entity&) = delete;

	virtual ~Entity();

	virtual void createMovementComponent(const float _maxVelocity);

	sf::Sprite* getSprite() noexcept;

	virtual void setTexture(const sf::Texture& _texture);
	
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
	sf::Sprite* sprite = new sf::Sprite();
	
	sf::Vector2f position;
	MovementComponent* movementComponent;
 
	std::string name;
};


