#pragma once

#include "MenuState.hpp"

class GameState :
    public State
{
public:
    GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states);

    GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Fighter* _p);
    
    virtual ~GameState();

    static float getXPos(sf::Sprite* spr);

    static float getYPos(sf::Sprite* spr);

    static void setXPos(float _x, sf::Sprite* sprite);

    static void setYPos(float _y, sf::Sprite* sprite);
    
    void updateInput(const float& _dt);

    void update(const float& _dt);

    void render(sf::RenderTarget* target = nullptr);

    static void setMainStageLimits(sf::Sprite* spr, float& lastx, float& lasty);

private:
    Fighter* player;
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
};

