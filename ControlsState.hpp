#pragma once

#include "State.hpp"

class ControlsState :
    public State
{
public:
    ControlsState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states);

    virtual ~ControlsState();

    sf::Text createControlText(const std::string& text, float _x, float _y);

    void updateInput(const float& _dt);

    void update(const float& _dt);

    void render(sf::RenderTarget* target = nullptr);

private:
    sf::Font font;

    sf::Text title;

    sf::Text message;

    std::vector<sf::Text> controls;

    void initVariables();

    void initTextures();

    void initBackground();

    void initFonts();

    void initKeybinds();

    void initControlList();
};

