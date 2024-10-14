#include "Fighter.hpp"

void Fighter::initVariables()
{

}

void Fighter::initComponents()
{
	this->createMovementComponent(120.5f);
}

Fighter::Fighter(float _x, float _y, sf::Texture& _texture, std::string _name)
{
	this->initVariables();
	this->initComponents();

	this->setTexture(_texture);
	this->setPosition(_x, _y);
	this->name = _name;
}

Fighter::~Fighter()
{

}
