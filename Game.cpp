#include "Game.hpp"
#include <SFML/Audio.hpp>

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT), "Chthonic Chronicles", sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar);
}

void Game::initKeys()
{
    this->supportedKeys["Escape"] = sf::Keyboard::Escape;
    this->supportedKeys["A"] = sf::Keyboard::A;
    this->supportedKeys["D"] = sf::Keyboard::D;
    this->supportedKeys["W"] = sf::Keyboard::W;
    this->supportedKeys["S"] = sf::Keyboard::S;
    this->supportedKeys["Left"] = sf::Keyboard::Left;
    this->supportedKeys["Right"] = sf::Keyboard::Right;
    this->supportedKeys["Up"] = sf::Keyboard::Up;
    this->supportedKeys["Down"] = sf::Keyboard::Down;
    this->supportedKeys["Enter"] = sf::Keyboard::Enter;
    this->supportedKeys["Z"] = sf::Keyboard::Z;
    this->supportedKeys["E"] = sf::Keyboard::E;
    this->supportedKeys["Q"] = sf::Keyboard::Q;
    this->supportedKeys["C"] = sf::Keyboard::C;
    this->supportedKeys["I"] = sf::Keyboard::I;
}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

Game::Game()
{
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Game::~Game()
{
    delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

void Game::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
        {
            this->window->close();
        }
    }
}

void Game::update()
{
    this->updateSFMLEvents();

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else
    {
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear();

    if (!this->states.empty())
    {
        this->states.top()->render();
    }

    this->window->display();
}

void Game::run()
{
    sf::Music music;
    if (!music.openFromFile("assets/music.ogg"))
    {
        std::cerr << "Error al cargar el archivo de música." << std::endl;
        return;
    }
    music.setVolume(50);  // Volumen (0-100)
    music.setLoop(true);
    music.play();

    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
        if (music.getStatus() == sf::Music::Playing)
        {

            //sf::sleep(sf::milliseconds(100)); // Evitar que el programa consuma demasiados recursos
        }
    }
}
