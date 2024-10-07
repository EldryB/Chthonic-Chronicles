#pragma once

#include "GameState.hpp"

class MainMenuState :
    public State
{
public:
    MainMenuState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys);
    virtual ~MainMenuState();

    void endState();

    void updateInput(const float& _dt);
    void update(const float& _dt);
    void render(sf::RenderTarget* target = nullptr);

private:
    sf::Sprite background;
    sf::Texture texture;

    void initKeybinds();
};

