#pragma once

#include "MenuState.hpp"
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
    Fighter* player;
    MainAnimation animationFighter;
    int currentFrame;
    float timeSinceLastUpdate;
    float timeBetweenUpdates;
    sf::Font font;
    sf::Text text;

    void initVariables();

    void initKeybinds();

    void initTextures();

    void initFighters();

    void initBackground();

    void initFonts();

    void initFighterFrames();

    void setMainStageLimits(sf::Sprite& spr);
};

