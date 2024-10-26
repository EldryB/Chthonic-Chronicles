#include "JobMenuState.hpp"

void JobMenuState::initVariables()
{
    this->keyPressTimer = 0.f;
    this->keyPressDelay = 1.f;
    this->keyCode = " ";
}

void JobMenuState::initKeybinds()
{
    this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
    this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
    this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
    this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
    this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
    this->keybinds["ACTION"] = this->supportedKeys->at("E");
    this->keybinds["Q"] = this->supportedKeys->at("Q");

}

void JobMenuState::initFonts()
{
    if (!this->font.loadFromFile("assets/fonts/font.ttf"))
    {
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_FONT";
    }

    this->title.setFont(font);
    this->title.setString("Settlement Management");
    this->title.setCharacterSize(36);
    this->title.setFillColor(sf::Color::Black);
    this->title.setPosition(100, 20);

    this->villagersAvailable.setFont(font);
    this->villagersAvailable.setCharacterSize(24);
    this->villagersAvailable.setFillColor(sf::Color::Black);
    this->villagersAvailable.setPosition(100, 80);
}


JobMenuState::JobMenuState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Jobs& jobs, Resources& resources, Fighter* _p)
    : jobs(jobs), resources(resources) ,State(_window, _supportedKeys, _states)
{
    this->initKeybinds();
    this->initVariables();
    this->initFonts();

    // Inicializa las listas de trabajos y recursos
    this->updateJobList();
    this->updateResourceList();

    // Botón para recolección de recursos
    this->collectButton.setSize(sf::Vector2f(150, 50));
    this->collectButton.setPosition(800, 550);
    this->collectButton.setFillColor(sf::Color(192, 192, 192));

    // Botón para desbloquear trabajos
    this->unlockButton.setSize(sf::Vector2f(150, 50));
    this->unlockButton.setPosition(100, 550);
    this->unlockButton.setFillColor(sf::Color(192, 192, 192));
    
    this->player = _p;

}

JobMenuState::~JobMenuState()
{

}

void JobMenuState::updateJobList()
{
    this->jobTexts.clear();
    this->addButtons.clear();
    this->subtractButtons.clear();

    for (int i = 0; i < static_cast<int>(JobTypes::count); ++i)
    {
        // Texto para los trabajos
        sf::Text jobText;
        jobText.setFont(font);
        jobText.setString(jobs.getJobName(static_cast<JobTypes>(i)));
        jobText.setCharacterSize(20);
        jobText.setFillColor(sf::Color::Black);
        jobText.setPosition(100, 120 + i * 40);
        jobTexts.push_back(jobText);

        // Botón de restar aldeanos
        sf::RectangleShape subtractButton;
        subtractButton.setSize(sf::Vector2f(30, 30));
        subtractButton.setPosition(300, 120 + i * 40);
        subtractButton.setFillColor(sf::Color(192, 192, 192));
        subtractButtons.push_back(subtractButton);

        // Botón de sumar aldeanos
        sf::RectangleShape addButton;
        addButton.setSize(sf::Vector2f(30, 30));
        addButton.setPosition(400, 120 + i * 40);
        addButton.setFillColor(sf::Color(192, 192, 192));
        addButtons.push_back(addButton);
    }
}

void JobMenuState::updateResourceList()
{
    this->resourceTexts.clear();
    this->amountTexts.clear();

    for (int i = 0; i < static_cast<int>(ResourceTypes::count); ++i)
    {
        // Texto para los recursos
        sf::Text resourceText;
        resourceText.setFont(font);
        resourceText.setString(resources.getResourceName(static_cast<ResourceTypes>(i)));
        resourceText.setCharacterSize(20);
        resourceText.setFillColor(sf::Color::Black);
        resourceText.setPosition(500, 120 + i * 40);
        resourceTexts.push_back(resourceText);

        // Texto para la cantidad de recursos
        sf::Text amountText;
        amountText.setFont(font);
        amountText.setString(std::to_string(resources.getResourceAmount(static_cast<ResourceTypes>(i))));
        amountText.setCharacterSize(20);
        amountText.setFillColor(sf::Color::Black);
        amountText.setPosition(650, 120 + i * 40);
        amountTexts.push_back(amountText);
    }
}

void JobMenuState::handleInput(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition();
        handleMouseClick(mousePos);
    }
}

void JobMenuState::handleMouseClick(sf::Vector2i mousePos)
{
    // Interactuar con los botones de aldeanos
    for (int i = 0; i < addButtons.size(); ++i)
    {
        if (addButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            this->jobs.assignVillagers(static_cast<JobTypes>(i));
            updateJobList();
        }
        else if (subtractButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            this->jobs.removeVillagers(static_cast<JobTypes>(i));
            updateJobList();
        }
    }

    // Interacción con el botón de recolectar recursos
    if (collectButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        this->jobs.collectResources(resources);
        updateResourceList();
    }

    // Interacción con el botón de desbloquear trabajos
    if (unlockButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        for (int i = 0; i < static_cast<int>(JobTypes::count); ++i)
        {
            if (this->jobs.getJobAmount(static_cast<JobTypes>(i)) == -1)
            {
                this->jobs.unlockJob(static_cast<JobTypes>(i));
                updateJobList();
                break;
            }
        }
    }
}

void JobMenuState::updateInput(const float& _dt)
{
    this->keyPressTimer += _dt;
    if (sf::Keyboard::isKeyPressed(this->keybinds.at("CLOSE")))
    {
        this->keyCode = "CLOSE";
    }
    else
    {
        if (keyCode == "CLOSE")
        {
            keyCode = " ";
            this->states->push(new MenuState(this->window, this->supportedKeys, this->states, this->player));
            this->keyPressTimer = 0.f;
        }
    }
   
    if (sf::Keyboard::isKeyPressed(this->keybinds.at("Q")))
    {
        this->keyCode = "Q";
    }
    else
    {
        if (keyCode == "Q")
        {
            keyCode = " ";
            this->states->pop();
            this->keyPressTimer = 0.f;
        }
    }
    
}

void JobMenuState::update(const float& _dt)
{
    this->updateMousePositions();
    this->updateInput(_dt);
}

void JobMenuState::render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = this->window;
    }

    target->draw(this->title);
    target->draw(this->villagersAvailable);

    // Dibujar trabajos y aldeanos
    for (const auto& jobText : jobTexts)
    {
        target->draw(jobText);
    }

    for (const auto& subtractButton : subtractButtons)
    {
        target->draw(subtractButton);
    }

    for (const auto& addButton : addButtons)
    {
        target->draw(addButton);
    }

    // Dibujar recursos
    for (const auto& resourceText : resourceTexts)
    {
        target->draw(resourceText);
    }

    for (const auto& amountText : amountTexts)
    {
        target->draw(amountText);
    }

    // Dibujar botones
    target->draw(this->collectButton);
    target->draw(this->unlockButton);
}
