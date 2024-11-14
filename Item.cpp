#include "Item.hpp"

Item::Item(sf::Texture& _texture, std::string _name, std::string _description, int _price)
    : name(_name), description(_description)
{
    this->price = _price;
    this->setTexture(_texture);
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

void Item::move(const float dir_x, const float dir_y, const float& _dt)
{
    this->sprite->move(dir_x * _dt, dir_y * _dt);
}

int Item::getPrice()
{
    return this->price;
}

void Item::use(Fighter* target)
{

}

void Item::render(sf::RenderTarget* target)
{
    target->draw(*this->sprite);
}

bool Item::isEquipped() const
{
    return false;
}

bool Item::isPLayerNear(sf::Sprite _p)
{
    float num1 = (_p.getPosition().x + _p.getGlobalBounds().width / 2);
    float num2 = this->sprite->getPosition().x + this->sprite->getGlobalBounds().width / 2;
    float num3 = (_p.getPosition().y + _p.getGlobalBounds().height / 2);
    float num4 = this->sprite->getPosition().y + this->sprite->getGlobalBounds().height / 2;

   bool check = ((num1 - num2) < 5 && (num3 - num4) < 5) ||
        ((num2 - num1) < 5 && (num3 - num4) < 5) ||
        ((num1 - num2) < 5 && (num4 - num3) < 5) ||
        ((num2 - num1) < 5 && (num4 - num3) < 5);
    return check;
}
