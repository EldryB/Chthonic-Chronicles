#include "Entity.hpp"

Entity::Entity()
{
	this->x = 321.f;
	this->y = 270.f;
	this->width = Settings::ENTITY_WIDTH;
	this->height = Settings::ENTITY_HEIGHT;
	this->texture.loadFromFile("assets/textures/right2.png");
	this->sprite.setTexture(texture);
	this->setName(" ");
	this->sprite.setPosition(x, y);
	this->movementSpeed = Settings::MOVEMENT_SPEED;
}

Entity::Entity(float _x, float _y, float _width, float _height) noexcept
	: x{ _x }, y{ _y }, width{ _width }, height{ _height }
{
	this->texture.loadFromFile("assets/textures/right2.png");
	this->sprite.setTexture(texture);
	this->setName(" ");
	this->sprite.setPosition(x, y);
	this->movementSpeed = Settings::MOVEMENT_SPEED;
}

Entity::Entity(float _x, float _y, float _width, float _height, sf::Sprite _sprite) noexcept
	: x{ _x }, y{ _y }, width{ _width }, height{ _height }, sprite{ _sprite }
{
	this->sprite.setPosition(x, y);
	this->movementSpeed = Settings::MOVEMENT_SPEED;
}

Entity::~Entity()
{

}

sf::Sprite Entity::get_sprite() noexcept
{
	return this->sprite;
}

void Entity::setName(std::string _name)
{
	this->name = _name;
}

void Entity::move(const float& _dt, const float dir_x, const float dir_y)
{
	this->sprite.move(dir_x * this->movementSpeed * _dt, dir_y * this->movementSpeed * _dt);
}

void Entity::update(const float& _dt)
{

}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

void Entity::animation(float& timeSinceLastUpdate, float& timeBetweenUpdates, std::vector<sf::Texture>& Myvector, int& currentFrame)
{
	if (timeSinceLastUpdate >= timeBetweenUpdates)
	{
		timeSinceLastUpdate = 0.0f;
		currentFrame = (currentFrame + 1) % Myvector.size();
		this->sprite.setTexture(Myvector[currentFrame]);
	}
}
