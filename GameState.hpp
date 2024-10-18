#pragma once

#include "MenuState.hpp"
#include "FightState.hpp"

class GameState :
    public State
{
public:
    GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states);

    GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Fighter* _p);
    
    virtual ~GameState();
    
    void updateInput(const float& _dt);

    void update(const float& _dt);

    void render(sf::RenderTarget* target = nullptr);

private:
    Fighter* player;
    int currentFrame;
    float timeSinceLastUpdate;
    float timeBetweenUpdates;
    sf::Font font;
    sf::Text text;
    sf::Text message;

    void initVariables();

    void initKeybinds();

    void initTextures();

    void initFighters();

    void initBackground();

    void initFonts();
};

