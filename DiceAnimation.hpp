#pragma once
#include <SFML/Graphics.hpp>
#include "Dice.hpp"

class DiceAnimation
{
public:
    DiceAnimation();

    void loadSprite(const std::string& textureFile);
    void rollAnimation(int sides);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    bool isRolling() const;

private:
    Dice dice;
    sf::Texture texture;
    sf::Sprite sprite;
    float animationTime;
    float elapsedTime;
    int finalValue; 
    bool rolling;

    void setSpriteFace(int value);
};
