#include "JobMenuState.hpp"

void JobMenuState::initVariables()
{
    // Inicializa variables necesarias
}

void JobMenuState::initTextures()
{
    if (!this->textures["Background"].loadFromFile("assets/textures/Backgrounds/job_menu.png"))
    {
        throw "ERROR::JOB_MENU_STATE::COULD_NOT_LOAD_BACKGROUND_TEXTURE!";
    }
}

void JobMenuState::initBackground()
{
    this->background.setTexture(this->textures["Background"]);
}

void JobMenuState::initFonts()
{
    if (!this->font.loadFromFile("assets/fonts/font.ttf"))
    {
        throw "ERROR::JOB_MENU_STATE::COULD_NOT_LOAD_FONT";
    }
}

void JobMenuState::initKeybinds()
{
    this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
}

void JobMenuState::initButtons()
{
    this->buttons["BACK"] = new Button(100.f, 400.f, this->textures["MenuButtonIdle"], &this->font, "Back");
}

JobMenuState::JobMenuState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states)
    : State(_window, _supportedKeys, _states)
{
    this->initVariables();
    this->initTextures();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

JobMenuState::~JobMenuState()
{
    for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

void JobMenuState::updateInput(const float& _dt)
{
    if (sf::Keyboard::isKeyPressed(this->keybinds.at("CLOSE")))
    {
        this->endState();
    }
}

void JobMenuState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);

        if (it.second->isPressed())
        {
            if (it.first == "BACK")
            {
                this->endState();
            }
        }
    }
}

void JobMenuState::update(const float& _dt)
{
    this->updateMousePositions();
    this->updateInput(_dt);
    this->updateButtons();
}

void JobMenuState::renderButtons(sf::RenderTarget* target)
{
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}

void JobMenuState::render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = this->window;
    }
    target->draw(this->background);
    this->renderButtons(target);
}
