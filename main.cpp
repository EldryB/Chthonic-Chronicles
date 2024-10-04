#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<iostream>
#include <vector>

#include <settings.hpp>
#include <char.hpp>
#include <animation.hpp>
#include <stateStack.hpp>
#include <stage.hpp>

int main()
{
    sf::RenderWindow window{ sf::VideoMode{Settings::WINDOW_WIDTH,Settings::WINDOW_HEIGHT} , "Demo", sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar };//Ventana
    
    sf::RenderTexture render_texture{};
    render_texture.create(Settings::VIRTUAL_WIDTH, Settings::VIRTUAL_HEIGHT);

    //Escala de sprite
    sf::Vector2f scale_factors
    {
        float(Settings::WINDOW_WIDTH) / float(Settings::VIRTUAL_WIDTH),
        float(Settings::WINDOW_HEIGHT) / float(Settings::VIRTUAL_HEIGHT)
    };
    sf::Sprite render_sprite{ render_texture.getTexture() };//Asignacion de la textura a un sprite
    render_sprite.setScale(scale_factors);



    StateStack allStages{};

    sf::Texture background;

    background.loadFromFile("assets/textures/mainStage.png");
    std::shared_ptr<Stage> mainStage = std::make_shared<Stage>(Settings::VIRTUAL_WIDTH, Settings::VIRTUAL_HEIGHT, sf::Sprite{ background });
    allStages.pushStage(mainStage);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        render_texture.clear(sf::Color::Black);
        render_texture.draw(allStages.getCurrentStage()->get_sprite());
        render_texture.display();

        window.draw(render_sprite);
        window.display();
    }

    return 0;
}