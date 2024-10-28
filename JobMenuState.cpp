#include "JobMenuState.hpp"

void JobMenuState::initVariables()
{
    this->keyCode = " ";
}

void JobMenuState::initTextures()
{
    if (!this->textures["Background"].loadFromFile("assets/textures/Backgrounds/jobMenu.jpg"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_BACKGROUND_TEXTURE!";
    }

    if (!this->textures["AddButton"].loadFromFile("assets/textures/addButton.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_ADD_BUTTON_TEXTURE!";
    }

    if (!this->textures["AddButtonHover"].loadFromFile("assets/textures/addButtonHover.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_ADD_BUTTON_TEXTURE!";
    }

    if (!this->textures["SubstractButton"].loadFromFile("assets/textures/substractButton.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_SUBSTRACT_BUTTON_TEXTURE!";
    }

    if (!this->textures["MenuButtonIdle"].loadFromFile("assets/textures/MenuButtonIdle.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_MENU_BUTTON_IDLE_TEXTURE!";
    }

    if (!this->textures["MenuButtonHover"].loadFromFile("assets/textures/MenuButtonHover.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_MENU_BUTTON_HOVER_TEXTURE!";
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
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_FONT";
    }

    this->title.setFont(this->font);
    this->title.setString("Settlement Management");
    this->title.setCharacterSize(36);
    this->title.setFillColor(sf::Color(206, 185, 141));
    this->title.setPosition(100, 30);

    this->villagersAvailable.setFont(this->font);
    this->villagersAvailable.setCharacterSize(24);
    this->villagersAvailable.setFillColor(sf::Color(206, 185, 141));
    this->villagersAvailable.setPosition(500, 80);
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

void JobMenuState::initButtons()
{
    this->buttons["COLLECT"] = new Button(800.f, 450.f, this->textures["MenuButtonIdle"], &this->font, "COLECT");
    this->buttons["UNLOCK"] = new Button(100.f, 450.f, this->textures["MenuButtonIdle"], &this->font, "UNLOCK");
     
    for (int i = 0; i < static_cast<int>(JobTypes::count); ++i)
    {
        this->addButtons.push_back(new Button(300.f, 55.f + i * 40, this->textures["AddButton"], &this->font, ""));
        this->substractButtons.push_back(new Button(340.f, 55.f + i * 40, this->textures["SubstractButton"], &this->font, ""));
    }
}

JobMenuState::JobMenuState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Jobs& jobs, Resources& resources, Fighter* _p)
    : jobs(jobs), resources(resources) ,State(_window, _supportedKeys, _states)
{
    this->initVariables();
    this->initTextures();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
    this->initJobList();
    this->initResourceList();
    this->player = _p;
}

JobMenuState::~JobMenuState()
{
    for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }

    for (auto& button : this->addButtons) 
    {
        delete button;
    }
    this->addButtons.clear();

    for (auto& button : this->substractButtons) 
    {
        delete button;
    }
    this->substractButtons.clear();
}

void JobMenuState::initJobList()
{
    this->jobTexts.clear();

    for (int i = 0; i < static_cast<int>(JobTypes::count); ++i)
    {
        sf::Text jobText;
        jobText.setFont(font);
        jobText.setString(jobs.getJobName(static_cast<JobTypes>(i)));
        jobText.setCharacterSize(20);
        jobText.setFillColor(sf::Color(206, 185, 141));
        jobText.setPosition(100.f, 70.f + i * 40);
        jobTexts.push_back(jobText);
    }
}

void JobMenuState::initResourceList()
{
    this->resourceTexts.clear();
    this->amountTexts.clear();

    for (int i = 0; i < static_cast<int>(ResourceTypes::count); ++i)
    {
        sf::Text resourceText;
        resourceText.setFont(font);
        resourceText.setString(resources.getResourceName(static_cast<ResourceTypes>(i)));
        resourceText.setCharacterSize(20);
        resourceText.setFillColor(sf::Color(206, 185, 141));
        resourceText.setPosition(800.f, 70.f + i * 40);
        resourceTexts.push_back(resourceText);

        sf::Text amountText;
        amountText.setFont(font);
        amountText.setString(std::to_string(resources.getResourceAmount(static_cast<ResourceTypes>(i))));
        amountText.setCharacterSize(20);
        amountText.setFillColor(sf::Color(206, 185, 141));
        amountText.setPosition(950.f, 70.f + i * 40);
        amountTexts.push_back(amountText);
    }
}

//void JobMenuState::handleInput(sf::Event event)
//{
//    if (event.type == sf::Event::MouseButtonPressed)
//    {
//        sf::Vector2i mousePos = sf::Mouse::getPosition();
//        handleMouseClick(mousePos);
//    }
//}
//
//void JobMenuState::handleMouseClick(sf::Vector2i mousePos)
//{
//    // Interactuar con los botones de aldeanos
//    for (int i = 0; i < addButtons.size(); ++i)
//    {
//        if (addButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
//        {
//            this->jobs.assignVillagers(static_cast<JobTypes>(i));
//            updateJobList();
//        }
//        else if (subtractButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
//        {
//            this->jobs.removeVillagers(static_cast<JobTypes>(i));
//            updateJobList();
//        }
//    }
//
//    // Interacción con el botón de recolectar recursos
//    if (collectButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
//    {
//        this->jobs.collectResources(resources);
//        updateResourceList();
//    }
//
//    // Interacción con el botón de desbloquear trabajos
//    if (unlockButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
//    {
//        for (int i = 0; i < static_cast<int>(JobTypes::count); ++i)
//        {
//            if (this->jobs.getJobAmount(static_cast<JobTypes>(i)) == -1)
//            {
//                this->jobs.unlockJob(static_cast<JobTypes>(i));
//                updateJobList();
//                break;
//            }
//        }
//    }
//}

void JobMenuState::updateInput(const float& _dt)
{   
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
        }
    }
    
}

void JobMenuState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->setTextCharacterSize(27);
        it.second->update(this->mousePosView);

        if (it.second->getButtonState() == ButtonState::Idle)
        {
            it.second->setTexture(this->textures["MenuButtonIdle"]);
            it.second->setTextFillColor(sf::Color(21, 26, 38));
        }

        if (it.second->getButtonState() == ButtonState::Hover)
        {
            it.second->setTexture(this->textures["MenuButtonHover"]);
            it.second->setTextFillColor(sf::Color(96, 60, 3));
        }
    }

    if (this->buttons["COLLECT"]->getButtonState() == ButtonState::Pressed)
    {
        this->jobs.collectResources(resources);
        this->initResourceList();
    }

    if (this->buttons["UNLOCK"]->getButtonState() == ButtonState::Pressed)
    {
        for (int i = 0; i < static_cast<int>(JobTypes::count); ++i)
        {
            if (this->jobs.getJobAmount(static_cast<JobTypes>(i)) == -1)
            {
                this->jobs.unlockJob(static_cast<JobTypes>(i));
                this->initJobList();
                break;
            }
        }
    }

    for (size_t i = 0; i < this->addButtons.size(); ++i)
    {
        this->addButtons[i]->update(this->mousePosView);
        this->substractButtons[i]->update(this->mousePosView);
        
        if (this->addButtons[i]->getButtonState() == ButtonState::Idle)
        {
            this->addButtons[i]->setTexture(this->textures["AddButton"]);
        }

        if (this->addButtons[i]->getButtonState() == ButtonState::Hover)
        {
            this->addButtons[i]->setTexture(this->textures["AddButtonHover"]);
        }

        if (this->substractButtons[i]->getButtonState() == ButtonState::Idle || this->substractButtons[i]->getButtonState() == ButtonState::Hover)
        {
            this->substractButtons[i]->setTexture(this->textures["SubstractButton"]);
        }

        if (this->addButtons[i]->getButtonState() == ButtonState::Pressed)
        {
            this->jobs.assignVillagers(static_cast<JobTypes>(i));
            this->initJobList();
        }
        else if (this->substractButtons[i]->getButtonState() == ButtonState::Pressed)
        {
            this->jobs.removeVillagers(static_cast<JobTypes>(i));
            this->initJobList();
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

    for (size_t i = 0; i < this->addButtons.size(); ++i)
    {
        this->addButtons[i]->render(target);
        this->substractButtons[i]->render(target);
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

    target->draw(this->title);
    target->draw(this->villagersAvailable);

    for (const auto& jobText : jobTexts)
    {
        target->draw(jobText);
    }

    for (const auto& resourceText : resourceTexts)
    {
        target->draw(resourceText);
    }

    for (const auto& amountText : amountTexts)
    {
        target->draw(amountText);
    }
}
