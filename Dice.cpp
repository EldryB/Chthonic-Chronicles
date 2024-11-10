#include "Dice.hpp"

void Dice::initVariables()
{
    this->animationComponent = NULL;
    this->animationTime = 2.0f;
    this->elapsedTime = 0.0f;
    this->rolling = false;
}

Dice::Dice(sf::Texture& texture_sheet, int _sides)
    : sides(_sides)
{
    this->initVariables();

    std::random_device random;
    generator.seed(random());

    this->createAnimationComponent(texture_sheet);
}

void Dice::createAnimationComponent(sf::Texture& texture_sheet)
{
    this->animationComponent = new AnimationComponent(*this->sprite, texture_sheet);
}

sf::Sprite* Dice::getSprite() const
{
    return this->sprite;
}

int Dice::getSides() const
{
    return this->sides;
}

void Dice::setTexture(const sf::Texture& _texture)
{
    this->sprite->setTexture(_texture);
}

void Dice::setSprite(sf::Sprite* _sprite)
{
    this->sprite = _sprite;
}

void Dice::setSides(int _sides)
{
    this->sides = _sides;
}

void Dice::update(const float& _dt)
{

}

void Dice::render(sf::RenderTarget* target)
{
    target->draw(*this->sprite);
}



//int Dice::roll(int sides)
//{
//    std::uniform_int_distribution<int> distribution(1, sides);
//    return distribution(generator);
//}


