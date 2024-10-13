#include "Fighter.hpp"

void Fighter::initVariables()
{

}

void Fighter::initComponents()
{
	this->createMovementComponent(120.5f);
}

Fighter::Fighter(float _x, float _y, sf::Texture* _texture, std::string _name)
	: Entity(_x, _y, _texture, _name)
{
	this->initVariables();
	this->initComponents();
}

Fighter::~Fighter()
{

}
