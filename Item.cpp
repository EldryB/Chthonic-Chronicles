#include "Item.hpp"

void Item::initVariables()
{

}

Item::Item(sf::Texture& _texture, std::string _name, std::string _description, sf::IntRect icon_rect)
    : name(_name), description(_description)
{
    this->setTexture(_texture);
    this->setIconRect(icon_rect);
}

Item::~Item()
{
    
}

sf::Texture Item::getTexture() const
{
    return *this->sprite->getTexture();
}

sf::Sprite* Item::getSprite() const
{
    return this->sprite;
}

std::string Item::getName() const
{
    return this->name;
}

std::string Item::getDescription() const
{
    return this->description;
}

void Item::setTexture(const sf::Texture& _texture)
{
    this->sprite->setTexture(_texture);
}

void Item::setSprite(sf::Sprite* _sprite)
{
    this->sprite = _sprite;
}

void Item::setPosition(float _x, float _y)
{
    this->sprite->setPosition(_x, _y);
}

void Item::setName(std::string _name)
{
    this->name = _name;
}

void Item::setDescription(std::string _description)
{
    this->description = _description;
}

void Item::setIconRect(sf::IntRect icon_rect)
{
    this->sprite->setTextureRect(icon_rect);
}

void Item::use()
{

}

void Item::render(sf::RenderTarget* target)
{
    target->draw(*this->sprite);
}




