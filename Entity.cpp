#include "Entity.hpp"

void Entity::initVariables()
{
	this->sprite = NULL;
	this->x = 0.f;
	this->y = 0.f;
	this->movementSpeed = 0.f;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::Entity(float _x, float _y, sf::Texture* _texture, std::string _name) noexcept
	: x{ _x }, y{ _y }, texture{ _texture }, name {_name}
{
	this->sprite = new sf::Sprite(*this->texture);
	this->sprite->setPosition(x, y);
	this->movementSpeed = Settings::MOVEMENT_SPEED;
}

Entity::~Entity()
{
	delete this->sprite;
}

sf::Sprite* Entity::getSprite() noexcept
{
	return this->sprite;
}

void Entity::setSprite(sf::Texture* _texture)
{
	this->texture = _texture;
	this->sprite = new sf::Sprite(*this->texture);
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
	if (this->sprite)
	{
		this->sprite->setPosition(_x, _y);
	}
}

void Entity::move(const float& _dt, const float dir_x, const float dir_y)
{
	if (this->sprite)
	{
		this->sprite->move(dir_x * this->movementSpeed * _dt, dir_y * this->movementSpeed * _dt);
	}
}

void Entity::update(const float& _dt)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
	if (this->sprite)
	{
		target->draw(*this->sprite);
	}
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


