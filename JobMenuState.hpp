#pragma once

#include "State.hpp"
#include "Button.hpp"
#include "JsonManagement.hpp"

class JobMenuState : public State
{
public:
    JobMenuState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states);
    virtual ~JobMenuState();

    void updateInput(const float& _dt);
    void updateButtons();
    void update(const float& _dt);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);

private:
    sf::Font font;
    std::unordered_map<std::string, Button*> buttons;

    // Métodos de inicialización
    void initVariables();
    void initTextures();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
};
