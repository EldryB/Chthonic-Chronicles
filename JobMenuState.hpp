#pragma once
#include <SFML/Graphics.hpp>
#include "Jobs.hpp"
#include "Resources.hpp"

class JobMenuState
{
public:
    JobMenuState(Jobs& jobs, Resources& resources, sf::Font& font);

    void handleInput(sf::Event event);
    void update();
    void render(sf::RenderWindow& window);

private:
    Jobs& jobs;
    Resources& resources;
    sf::Font& font;

    sf::Text title;
    sf::Text villagersAvailable;  // Texto para aldeanos disponibles
    std::vector<sf::Text> jobTexts;  // Texto de trabajos
    std::vector<sf::Text> resourceTexts;  // Texto de recursos
    std::vector<sf::Text> amountTexts;  // Cantidades de recursos

    std::vector<sf::RectangleShape> addButtons;  // Botones para sumar aldeanos
    std::vector<sf::RectangleShape> subtractButtons;  // Botones para restar aldeanos

    sf::RectangleShape collectButton;  // Botón de recolección
    sf::RectangleShape unlockButton;  // Botón para desbloquear trabajos

    void updateJobList();
    void updateResourceList();
    void handleMouseClick(sf::Vector2i mousePos);
};
