#pragma once

#include "State.hpp"
class GameState :
    public State
{
public:
    GameState(sf::RenderWindow* _window, std::map<std::string, sf::Keyboard::Key>* _supportedKeys);
    virtual ~GameState();

    void endState();

    void updateInput(const float& _dt);
    void update(const float& _dt);
    void render(sf::RenderTarget* target = nullptr);

private:
    Entity player;

    void initKeybinds();
};

