#include "JobMenuState.hpp"

void JobMenuState::initVariables()
{
    this->currentState = CurrentState::JobMenu;
    this->keyCode = " ";
}

void JobMenuState::initTextures()
{
    if (!this->textures["Background"].loadFromFile("assets/textures/Backgrounds/jobMenu.jpg"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_BACKGROUND_TEXTURE!";
    }

    if (!this->textures["AddButton"].loadFromFile("assets/textures/Buttons/addButton.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_ADD_BUTTON_TEXTURE!";
    }

    if (!this->textures["AddButtonHover"].loadFromFile("assets/textures/Buttons/addButtonHover.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_ADD_BUTTON_TEXTURE!";
    }

    if (!this->textures["SubstractButton"].loadFromFile("assets/textures/Buttons/substractButton.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_SUBSTRACT_BUTTON_TEXTURE!";
    }

    if (!this->textures["SubstractButtonHover"].loadFromFile("assets/textures/Buttons/substractButtonHover.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_SUBSTRACT_BUTTON_TEXTURE!";
    }

    if (!this->textures["CollectButton"].loadFromFile("assets/textures/Buttons/collectButton.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_SUBSTRACT_BUTTON_TEXTURE!";
    }

    if (!this->textures["CollectButtonHover"].loadFromFile("assets/textures/Buttons/collectButtonHover.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_SUBSTRACT_BUTTON_TEXTURE!";
    }

    if (!this->textures["MenuButtonIdle"].loadFromFile("assets/textures/Buttons/MenuButtonIdle.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_MENU_BUTTON_IDLE_TEXTURE!";
    }

    if (!this->textures["MenuButtonHover"].loadFromFile("assets/textures/Buttons/MenuButtonHover.png"))
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

    this->texts["Title"].setFont(this->font);
    this->texts["Title"].setString("Settlement Management");
    this->texts["Title"].setCharacterSize(36);
    this->texts["Title"].setFillColor(sf::Color(206, 185, 141));
    this->texts["Title"].setPosition(100, 30);

    this->backgroundTooltip.setTexture(this->textures["MenuButtonIdle"]);
    this->backgroundTooltip.setPosition(700.f, 450.f);

    this->texts["Tooltip"].setFont(this->font);
    this->texts["Tooltip"].setString(" ");
    this->texts["Tooltip"].setCharacterSize(12);
    this->texts["Tooltip"].setFillColor(sf::Color(21, 26, 38));
    this->texts["Tooltip"].setPosition
    (
        this->backgroundTooltip.getPosition().x + (this->backgroundTooltip.getGlobalBounds().width / 2.f) - (this->texts["Tooltip"].getGlobalBounds().width / 2.f),
        this->backgroundTooltip.getPosition().y + (this->backgroundTooltip.getGlobalBounds().height / 2.f) - (this->texts["Tooltip"].getGlobalBounds().height / 2.f)
    );

    this->texts["ControlsMessage"].setFont(this->font);
    this->texts["ControlsMessage"].setString("Press 'C' to show controls");
    this->texts["ControlsMessage"].setCharacterSize(24);
    this->texts["ControlsMessage"].setFillColor(sf::Color::White);
    this->texts["ControlsMessage"].setPosition((Settings::WINDOW_WIDTH - this->texts["ControlsMessage"].getGlobalBounds().width), 20.f);

    this->texts["AvailableVillagers"].setFont(this->font);
    this->texts["AvailableVillagers"].setCharacterSize(24);
    this->texts["AvailableVillagers"].setFillColor(sf::Color::White);
    this->texts["AvailableVillagers"].setPosition(100, Settings::WINDOW_HEIGHT - 20.f);

    this->texts["CollectTimer"].setFont(this->font);
    this->texts["CollectTimer"].setCharacterSize(24);
    this->texts["CollectTimer"].setFillColor(sf::Color::White);
    this->texts["CollectTimer"].setPosition(Settings::WINDOW_WIDTH / 2, 80.f);
}

void JobMenuState::initKeybinds()
{
    this->keybinds["CLOSE"] = this->supportedKeys->at("Q");
    this->keybinds["CONTROLS"] = this->supportedKeys->at("C");
}

void JobMenuState::initButtons()
{
    this->buttons["UPGRADE"] = new Button(100.f, 450.f, this->textures["MenuButtonIdle"], &this->font, "UPGRADE         ");

    for (int i = 0; i < static_cast<int>(JobTypes::count); ++i)
    {
        this->addButtons.push_back(new Button(300.f, 55.f + i * 40, this->textures["AddButton"], &this->font, ""));
        this->substractButtons.push_back(new Button(340.f, 55.f + i * 40, this->textures["SubstractButton"], &this->font, ""));
        this->collectButtons.push_back(new Button(380.f, 55.f + i * 40, this->textures["CollectButton"], &this->font, ""));
    }
}

JobMenuState::JobMenuState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Player* _p)
    : jobs(_p->getJobs()), resources(_p->getResources()) ,State(_window, _supportedKeys, _states)
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

    for (auto& button : this->collectButtons)
    {
        delete button;
    }
    this->collectButtons.clear();
}

void JobMenuState::initJobList()
{
    this->jobAmount.clear();

    for (int i = 0; i < static_cast<int>(JobTypes::count); ++i)
    {
        sf::Text jobText;
        jobText.setFont(font);
        jobText.setString(jobs->getJobName(static_cast<JobTypes>(i)));
        jobText.setCharacterSize(20);
        jobText.setFillColor(sf::Color(206, 185, 141));
        jobText.setPosition(100.f, 70.f + i * 40);
        this->texts[jobText.getString()] = jobText;

        sf::Text amountText;
        amountText.setFont(font);
        amountText.setString(std::to_string(jobs->getJobAmount(static_cast<JobTypes>(i))));
        amountText.setCharacterSize(20);
        amountText.setFillColor(sf::Color(206, 185, 141));
        amountText.setPosition(450.f, 70.f + i * 40);
        jobAmount.push_back(amountText);
    }
}

void JobMenuState::initResourceList()
{
    this->resourceAmount.clear();

    for (int i = 0; i < static_cast<int>(ResourceTypes::count); ++i)
    {
        sf::Text resourceText;
        resourceText.setFont(font);
        resourceText.setString(resources->getResourceName(static_cast<ResourceTypes>(i)));
        resourceText.setCharacterSize(20);
        resourceText.setFillColor(sf::Color(206, 185, 141));
        resourceText.setPosition(800.f, 70.f + i * 40);
        this->texts[resourceText.getString()] = resourceText;

        sf::Text amountText;
        amountText.setFont(font);
        amountText.setString(std::to_string(resources->getResourceAmount(static_cast<ResourceTypes>(i))));
        amountText.setCharacterSize(20);
        amountText.setFillColor(sf::Color(206, 185, 141));
        amountText.setPosition(950.f, 70.f + i * 40);
        resourceAmount.push_back(amountText);
    }
}

std::string JobMenuState::getTooltipMessage(JobTypes _jobs)
{
    switch (_jobs)
    {
    case JobTypes::coinMaker: return "Coin Maker\nNeeds 1 gold\nProduces 11 coins";

    case JobTypes::farmer: return "Farmer\nNeeds nothing\nProduces 1 wheat";

    case JobTypes::baker: return "Baker\nNeeds 2 wheats\nProduces 1 bread";

    case JobTypes::tanner: return "Tanner\nNeeds 2 breads\nProduces 1 leather";

    case JobTypes::weaver: return "Weaver\nNeeds 1 bread\nProduces 1 cloth";

    case JobTypes::silkFarmer: return "Silk Farmer\nNeeds 15 cloths\nProduces 1 silk";

    case JobTypes::stoneMason: return "Stone Mason\nNeeds 1 bread\nProduces 3 stones";

    case JobTypes::woodCutter: return "Wood Cutter\nNeeds 1 bread\nProduces 3 wood";

    case JobTypes::ironMiner: return "Iron Miner\nNeeds 2 breads\nProduces 1 iron";

    case JobTypes::goldMiner: return "Gold Miner\nNeeds 10 breads\nProduces 1 gold";

    default:
        break;
    }
    return std::string();
}

void JobMenuState::updateInput(const float& _dt)
{   
    if (sf::Keyboard::isKeyPressed(this->keybinds["CONTROLS"]))
    {
        this->keyCode = "CONTROLS";
    }
    else
    {
        if (this->keyCode == "CONTROLS")
        {
            this->keyCode = " ";
            this->states->push(new ControlsState(this->window, this->supportedKeys, this->states));
        }
    }
    
    if (sf::Keyboard::isKeyPressed(this->keybinds.at("CLOSE")))
    {
        this->keyCode = "CLOSE";
    }
    else
    {
        if (keyCode == "CLOSE")
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

    if (this->buttons["UPGRADE"]->getButtonState() == ButtonState::Pressed)
    {
        this->availableVillagers += 5;
    }

    for (size_t i = 0; i < this->addButtons.size(); ++i)
    {
        this->addButtons[i]->update(this->mousePosView);
        this->substractButtons[i]->update(this->mousePosView);
        this->collectButtons[i]->update(this->mousePosView);
        
        if (this->addButtons[i]->getButtonState() == ButtonState::Idle)
        {
            this->addButtons[i]->setTexture(this->textures["AddButton"]);
        }

        if (this->addButtons[i]->getButtonState() == ButtonState::Hover)
        {
            this->addButtons[i]->setTexture(this->textures["AddButtonHover"]);
        }

        if (this->substractButtons[i]->getButtonState() == ButtonState::Idle)
        {
            this->substractButtons[i]->setTexture(this->textures["SubstractButton"]);
        }

        if (this->substractButtons[i]->getButtonState() == ButtonState::Hover)
        {
            this->substractButtons[i]->setTexture(this->textures["SubstractButtonHover"]);
        }

        if (this->collectButtons[i]->getButtonState() == ButtonState::Idle)
        {
            this->collectButtons[i]->setTexture(this->textures["CollectButton"]);

        }
       
        if (this->collectButtons[i]->getButtonState() == ButtonState::Hover)
        {
            this->collectButtons[i]->setTexture(this->textures["CollectButtonHover"]);
            this->texts["Tooltip"].setString(this->getTooltipMessage(static_cast<JobTypes>(i)));
            this->texts["Tooltip"].setPosition
            (
                this->backgroundTooltip.getPosition().x + (this->backgroundTooltip.getGlobalBounds().width / 2.f) - (this->texts["Tooltip"].getGlobalBounds().width / 2.f),
                this->backgroundTooltip.getPosition().y + (this->backgroundTooltip.getGlobalBounds().height / 2.f) - (this->texts["Tooltip"].getGlobalBounds().height / 2.f)
            );
        }
 
        if (this->addButtons[i]->getButtonState() == ButtonState::Pressed)
        {
            if (this->availableVillagers > 0)
            {
                this->jobs->assignVillagers(static_cast<JobTypes>(i));
                this->availableVillagers--;
                this->initJobList();
            }
        }
        else if (this->substractButtons[i]->getButtonState() == ButtonState::Pressed)
        {
            if (this->jobs->getJobAmount(static_cast<JobTypes>(i)) > 0)
            {
                this->jobs->removeVillagers(static_cast<JobTypes>(i));
                this->availableVillagers++;
                this->initJobList();
            }
        }
    }
}

void JobMenuState::update(const float& _dt)
{
    if (this->collectionClock.getElapsedTime().asSeconds() >= 10.f)
    {
        this->jobs->collectResourcesAutomatically(*resources);
        this->collectionClock.restart();
        this->initResourceList();
    }

    this->texts["AvailableVillagers"].setString("Available Villagers: " + std::to_string(this->availableVillagers));
    this->texts["CollectTimer"].setString("Collect in: " + std::to_string(10 - static_cast<int>(this->collectionClock.getElapsedTime().asSeconds())));

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
        this->collectButtons[i]->render(target);
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

    for (auto text : this->texts)
    {
        if (text.first != "Tooltip")
        {
            target->draw(text.second);
        }
    }

    for (size_t i = 0; i < addButtons.size(); i++)
    {
        if (this->collectButtons[i]->getButtonState() == ButtonState::Hover)
        {
            target->draw(this->backgroundTooltip);
            target->draw(this->texts["Tooltip"]);
        }
    }

    if(this->jobAmount[0].getString() != "-1")
    {
        for (const auto& amount : jobAmount)
        {
            target->draw(amount);
        }
    }

    if (this->resourceAmount[0].getString() != "-1")
    {
        for (const auto& amountText : resourceAmount)
        {
            target->draw(amountText);
        }
    }
}
