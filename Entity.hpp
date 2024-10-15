#pragma once

#include "MovementComponent.hpp"
#include "AnimationComponent.hpp"

class Entity
{
public:
	Entity();

	Entity(float _x, float _y, sf::Texture& _texture, std::string _name) noexcept;

	Entity(const Entity&) = delete;

	Entity& operator = (Entity&) = delete;

	virtual ~Entity();

	void createMovementComponent(const float _maxVelocity);

	void createAnimationComponent(sf::Texture& texture_sheet);

	sf::Sprite* getSprite() noexcept;

	void setTexture(const sf::Texture& _texture);

	void setSprite(sf::Sprite* sprite);

	virtual void setPosition(const float _x, const float _y);

	virtual void setName(std::string _name);

	virtual void move(const float dir_x, const float dir_y, const float& _dt);

	virtual void update(const float& _dt);

	virtual void render(sf::RenderTarget* target);

	virtual void animate(float& timeSinceLastUpdate, float& timeBetweenUpdates, std::vector<sf::Texture>& Myvector, int& currentFrame);

private:
	void initVariables();

protected:
	sf::Sprite* sprite = new sf::Sprite();

	sf::Vector2f position;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

	std::string name;
};


