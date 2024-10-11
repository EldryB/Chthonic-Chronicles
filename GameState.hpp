#pragma once

#include "State.hpp"
#include "Animation.hpp"
class GameState :
    public State
{
public:
    GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states);
    virtual ~GameState();

    float getXPos(sf::Sprite spr);
    float getYPos(sf::Sprite spr);
    void setXPos(float _x, sf::Sprite& sprite);
    void setYPos(float _y, sf::Sprite& sprite);
    
    void updateInput(const float& _dt);
    void update(const float& _dt);
    void render(sf::RenderTarget* target = nullptr);

private:
    Entity player;
    MainAnimation animationEntity;
    int currentFrame;
    float timeSinceLastUpdate;
    float timeBetweenUpdates;
    sf::Font font;
    sf::Text text;

    void initVariables();
    void initKeybinds();
    void initTextures();
    void initBackground();
    void initFonts();
    void initCharacterFrames();
    void setMainStageLimits(sf::Sprite& spr);
};

