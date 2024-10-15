#pragma once

#include "State.hpp"
#include "Button.hpp"
#include "JsonManagement.hpp"

using json = nlohmann::json;

class MenuState :
    public State
{
public:
    MenuState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Fighter* _p);
    virtual ~MenuState();

    void updateInput(const float& _dt);

    void updateButtons();

    void update(const float& _dt);

    void renderButtons(sf::RenderTarget* target = nullptr);

    void render(sf::RenderTarget* target = nullptr);

private:
    sf::Font font;
    std::unordered_map<std::string, Button*> buttons;
    Fighter* player;
    JsonManagement dataManagement;

    void initVariables();

    void initTextures();

    void initBackground();

    void initFonts();

    void initKeybinds();

    void initButtons();
};
