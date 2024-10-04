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

void fun_animation(float& timeSinceLastUpdate, float& timeBetweenUpdates, std::vector<sf::Texture>& Myvector, int& currentFrame, Character& chara)
{
    if (timeSinceLastUpdate >= timeBetweenUpdates)
    {
        timeSinceLastUpdate = 0.0f;
        currentFrame = (currentFrame + 1) % Myvector.size();
        chara.setTexture(Myvector[currentFrame]);
    }
}


int main()
{
    sf::Clock clock;
    Animation MyAnimation; //Estructura que guarda los frames del personaje principal
    Attack_animation animation_monster1; //Estructura que guarda los frames del monstruo 1

    Settings::init(animation_monster1.AttackAnimation);//Inicializacion de texturas
    Settings::load_frames(MyAnimation.RightAnimation, MyAnimation.LeftAnimation, MyAnimation.FrontAnimation, MyAnimation.BackAnimation);//Cargado de frames

    int currentFrame = 0;
    float timeSinceLastUpdate = 0.0f;
    float timeBetweenUpdates = 0.01f; //Ajustar la velocidad de la animación

    Look look;// enum que me indica hacia donde estoy mirando

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

    //fondos
    sf::Texture background;

    background.loadFromFile("assets/textures/mainStage.png");
    std::shared_ptr<Stage> mainStage = std::make_shared<Stage>(Settings::VIRTUAL_WIDTH, Settings::VIRTUAL_HEIGHT, sf::Sprite{ background });
    allStages.pushStage(mainStage);

    Current_stage My_current_stage = Current_stage::MainStage;
    
    
    //personajes
    Character character
    {
        321.0f, 270.0f, Settings::CHARACTER_WIDTH, Settings::CHARACTER_HEIGHT
    };





    float speed = 120.5f;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Obtener el tiempo transcurrido desde el último frame
        float deltaTime = clock.restart().asSeconds();
        timeSinceLastUpdate += deltaTime;


        // Movimiento del sprite basado en las teclas presionadas
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
        {

            float x = float((-1.0) * (speed) * (deltaTime));
            float y = 0.0;
            character.move(x, y, My_current_stage);
            fun_animation(timeSinceLastUpdate, timeBetweenUpdates, MyAnimation.LeftAnimation, currentFrame, character);

            look = Look::look_left;

        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
        {

            float x = float((1.0) * (speed) * (deltaTime));
            float y = 0.0;
            character.move(x, y, My_current_stage);
            fun_animation(timeSinceLastUpdate, timeBetweenUpdates, MyAnimation.RightAnimation, currentFrame, character);

            look = Look::look_right;
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
        {

            float x = 0.0;
            float y = float((-1.0) * (speed) * (deltaTime));
            character.move(x, y, My_current_stage);
            fun_animation(timeSinceLastUpdate, timeBetweenUpdates, MyAnimation.BackAnimation, currentFrame, character);

            look = Look::look_up;


        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
        {

            float x = 0.0;
            float y = float((1.0) * (speed) * (deltaTime));
            character.move(x, y, My_current_stage);
            fun_animation(timeSinceLastUpdate, timeBetweenUpdates, MyAnimation.FrontAnimation, currentFrame, character);

            look = Look::look_down;
        }





        //renderizado
        render_texture.clear(sf::Color::Black);
        render_texture.draw(allStages.getCurrentStage()->get_sprite());
        character.render(render_texture);
        render_texture.display();

        window.draw(render_sprite);
        window.display();
    }

    return 0;
}