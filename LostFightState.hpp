#pragma once

#include "MenuState.hpp"

class LostFightState :
    public State
{
public:
    LostFightState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Fighter* _p);

    virtual ~LostFightState();

    void updateInput(const float& _dt);

    void updateButtons();

    void update(const float& _dt);

    void renderButtons(sf::RenderTarget* target = nullptr);

    void render(sf::RenderTarget* target = nullptr);

private:
    Fighter* player;
    std::unordered_map<std::string, Button*> buttons;
    int selectedButtonIndex;

    void initVariables();

    void initTextures();

    void initBackground();

    void initFonts();

    void initKeybinds();

    void initButtons();
};

