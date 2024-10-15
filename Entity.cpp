#include "Entity.hpp"

void Entity::initVariables()
{
	this->position.x = 0.f;
	this->position.y = 0.f;
	this->movementComponent = NULL;
	this->animationComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::Entity(float _x, float _y, sf::Texture& _texture, std::string _name) noexcept
	: position{ _x, _y }, name{ _name }
{
	this->setTexture(_texture);
	this->sprite->setPosition(this->position.x, this->position.y);
}

Entity::~Entity()
{
	delete this->movementComponent;
	delete this->animationComponent;
}

void Entity::createMovementComponent(const float _maxVelocity)
{
	this->movementComponent = new MovementComponent(*this->sprite, _maxVelocity);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(*this->sprite, texture_sheet);
}

sf::Sprite* Entity::getSprite() noexcept
{
	return this->sprite;
}

void Entity::setTexture(const sf::Texture& _texture)
{
	sprite->setTexture(_texture);
}

void Entity::setSprite(sf::Sprite* _sprite)
{
	this->sprite = _sprite;
}

void Entity::setName(std::string _name)
{
	this->name = _name;
}

void Entity::setPosition(const float _x, const float _y)
{
	this->sprite->setPosition(_x, _y);
}

void Entity::move(const float dir_x, const float dir_y, const float& _dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, _dt);
	}
}

void Entity::update(const float& _dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->update(_dt);
	}
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(*this->sprite);
}

void Entity::animate(float& timeSinceLastUpdate, float& timeBetweenUpdates, std::vector<sf::Texture>& Myvector, int& currentFrame)
{
	if (timeSinceLastUpdate >= timeBetweenUpdates)
	{
		timeSinceLastUpdate = 0.0f;
		currentFrame = (currentFrame + 1) % Myvector.size();
		this->sprite->setTexture(Myvector[currentFrame]);
	}
}


