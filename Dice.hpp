#pragma once
#include "AnimationComponent.hpp"

class Dice
{
public:
    Dice(int _sides);
    
    Dice(sf::Texture& texture_sheet, int _sides);

    void createAnimationComponent(sf::Texture& texture_sheet);

    sf::Sprite* getSprite() const;

    int getSides() const;

    void setTexture(const sf::Texture& _texture);

    void setSprite(sf::Sprite* _sprite);

    void setSides(int _sides);

    int getFace();
    
    void roll();

    bool isRolling() const;

    void update(const float& _dt);

    void render(sf::RenderTarget* target);

private:
    std::mt19937 generator;
    AnimationComponent* animationComponent;
    sf::Sprite* sprite = new sf::Sprite();
    int sides;
    float animationTime;
    float elapsedTime;
    int finalFace;
    bool rolling;

    void initVariables();
    
    void setSpriteFace(int face);
};