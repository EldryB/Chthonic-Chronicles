#pragma once
#include "AnimationComponent.hpp"

class Dice
{
public:
    Dice(sf::Texture& texture_sheet, int _sides);

    void createAnimationComponent(sf::Texture& texture_sheet);

    sf::Sprite* getSprite() const;

    int getSides() const;

    void setTexture(const sf::Texture& _texture);

    void setSprite(sf::Sprite* _sprite);

    void setSides(int _sides);

    void loadSprite(const std::string& textureFile);
    void roll(int _sides, float animationt_time);
    void update(const float& _dt);
    void render(sf::RenderTarget* target);
    bool isRolling() const;

private:
    std::mt19937 generator;
    AnimationComponent* animationComponent;
    sf::Sprite* sprite = new sf::Sprite();
    int sides;
    float animationTime;
    float elapsedTime;
    int finalValue;
    bool rolling;

    void initVariables();
    
    void setSpriteFace(int value);
};