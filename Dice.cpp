#include "Dice.hpp"

void Dice::initVariables()
{
    this->animationComponent = NULL;
    this->animationTime = 2.0f;
    this->elapsedTime = 0.0f;
    this->rolling = false;
}

void Dice::setSpriteFace(int face)
{
    this->sprite->setTextureRect(sf::IntRect((face - 1) * 32, 0, 32, 32));
}

Dice::Dice(int _sides)
    : sides(_sides)
{
    std::random_device random;
    this->generator.seed(random());
}

Dice::Dice(sf::Texture& texture_sheet, int _sides)
    : sides(_sides)
{
    this->initVariables();

    std::random_device random;
    generator.seed(random());

    this->createAnimationComponent(texture_sheet);

    for (int i = 0; i < 20; ++i) 
    {
        animationComponent->addAnimation("FACE" + std::to_string(i + 1), 0.1f, i, 0, 19, 0, 32, 32);
    }
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

void Dice::setPosition(float _x, float _y)
{
    this->sprite->setPosition(_x, _y);
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

int Dice::getFace()
{
    std::uniform_int_distribution<int> distribution(1, this->sides);
    return distribution(generator);
}

void Dice::roll()
{
    this->finalFace = this->getFace();
    this->rolling = true;
    this->elapsedTime = 0.0f;
}

bool Dice::isRolling() const
{
    return this->rolling;
}

void Dice::update(const float& _dt)
{
    if (!rolling)
    {
        return;
    }

    this->elapsedTime += _dt;

    if (this->elapsedTime >= this->animationTime)
    {
        this->rolling = false;
        this->setSpriteFace(this->finalFace);
    }
    else
    {
        int randomFace = this->getFace();
        this->animationComponent->play("FACE" + std::to_string(randomFace - 1), _dt);
    }
}

void Dice::render(sf::RenderTarget* target)
{
    target->draw(*this->sprite);
}



