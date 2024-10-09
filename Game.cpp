#include "Game.hpp"
#include "Animation.hpp"

//Static functions

//Initializer functions
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

void Game::endApplication()
{
    std::cout << "Ending Application" << "\n";
}

void Game::updateDt()
{
    //Update the dt variable with the time it takes to update and render one frame.

    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
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
        this->endApplication();
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear();

    //render items
    if (!this->states.empty())
    {
        this->states.top()->render();
    }

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}
