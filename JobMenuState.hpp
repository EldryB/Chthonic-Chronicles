#pragma once

#include "State.hpp"
#include "Jobs.hpp"
#include"MenuState.hpp"

class JobMenuState :
    public State
{
public:
    JobMenuState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Jobs& jobs, Resources& resources, Fighter* _p);

    void handleInput(sf::Event event);

    virtual ~JobMenuState();

    void updateInput(const float& _dt);

    void update(const float& _dt);

    void render(sf::RenderTarget* target = nullptr);

private:
    Jobs& jobs;
    Resources& resources;
    sf::Font font;
    Fighter* player;
    std::string keyCode{""};

    sf::Text title;
    sf::Text villagersAvailable;  // Texto para aldeanos disponibles
    std::vector<sf::Text> jobTexts;  // Texto de trabajos
    std::vector<sf::Text> resourceTexts;  // Texto de recursos
    std::vector<sf::Text> amountTexts;  // Cantidades de recursos

    std::vector<sf::RectangleShape> addButtons;  // Botones para sumar aldeanos
    std::vector<sf::RectangleShape> subtractButtons;  // Botones para restar aldeanos

    sf::RectangleShape collectButton;  // Botón de recolección
    sf::RectangleShape unlockButton;  // Botón para desbloquear trabajos

    void initKeybinds();

    void initVariables();

    void initFonts();

    void updateJobList();

    void updateResourceList();

    void handleMouseClick(sf::Vector2i mousePos);
};

