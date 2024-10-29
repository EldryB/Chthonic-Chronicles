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

    if (!this->textures["SubstractButtonHover"].loadFromFile("assets/textures/substractButtonHover.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_SUBSTRACT_BUTTON_TEXTURE!";
    }

    if (!this->textures["CollectButton"].loadFromFile("assets/textures/collectButton.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_SUBSTRACT_BUTTON_TEXTURE!";
    }

    if (!this->textures["CollectButtonHover"].loadFromFile("assets/textures/collectButtonHover.png"))
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

    this->backgroundTooltip.setTexture(this->textures["MenuButtonIdle"]);
    this->backgroundTooltip.setPosition(700.f, 450.f);

    this->tooltip.setFont(this->font);
    this->tooltip.setString(" ");
    this->tooltip.setCharacterSize(12);
    this->tooltip.setFillColor(sf::Color::Black);
    this->tooltip.setPosition
    (
        this->backgroundTooltip.getPosition().x + (this->backgroundTooltip.getGlobalBounds().width / 2.f) - this->backgroundTooltip.getGlobalBounds().width / 2.7f,
        this->backgroundTooltip.getPosition().y + (this->backgroundTooltip.getGlobalBounds().height / 2.5f) - this->backgroundTooltip.getGlobalBounds().height / 23.f
    );
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
    this->buttons["UNLOCK"] = new Button(100.f, 450.f, this->textures["MenuButtonIdle"], &this->font, "UNLOCK");
     
    for (int i = 0; i < static_cast<int>(JobTypes::count); ++i)
    {
        this->addButtons.push_back(new Button(300.f, 55.f + i * 40, this->textures["AddButton"], &this->font, ""));
        this->substractButtons.push_back(new Button(340.f, 55.f + i * 40, this->textures["SubstractButton"], &this->font, ""));
        this->collectButtons.push_back(new Button(380.f, 55.f + i * 40, this->textures["CollectButton"], &this->font, ""));
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

    for (auto& button : this->collectButtons)
    {
        delete button;
    }
    this->collectButtons.clear();
}

void JobMenuState::initJobList()
{
    this->jobTexts.clear();
    this->jobAmount.clear();

    for (int i = 0; i < static_cast<int>(JobTypes::count); ++i)
    {
        sf::Text jobText;
        jobText.setFont(font);
        jobText.setString(jobs.getJobName(static_cast<JobTypes>(i)));
        jobText.setCharacterSize(20);
        jobText.setFillColor(sf::Color(206, 185, 141));
        jobText.setPosition(100.f, 70.f + i * 40);
        jobTexts.push_back(jobText);

        sf::Text amountText;
        amountText.setFont(font);
        amountText.setString(std::to_string(jobs.getJobAmount(static_cast<JobTypes>(i))));
        amountText.setCharacterSize(20);
        amountText.setFillColor(sf::Color(206, 185, 141));
        amountText.setPosition(450.f, 70.f + i * 40);
        jobAmount.push_back(amountText);
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

std::string JobMenuState::getTooltipMessage(JobTypes _jobs)
{
    switch (_jobs)
    {
    case JobTypes::coinMaker: return "CoinMaker\nNecesita 1 oro\nProduce 11 monedas";
        
    case JobTypes::farmer:return "Farmer\nNo necesita nada\nProduce 1 trigo";
       
    case JobTypes::baker:return "Baker\nNecesita 2 trigos\nProduce 1 pan";
       
    case JobTypes::tanner:return "Tanner\nNecesita 2 panes\nProduce 1 cuero";
       
    case JobTypes::weaver:return "Weaver\nNecesita 1 pan\nProduce 1 ropa";
      
    case JobTypes::silkFarmer:return "SilkFarmer\nNecesita 15 ropa\nProduce 1 seda";
 
    case JobTypes::stoneMason:return "StoneMason\nNecesita 1 pan\nProduce 3 piedras";

    case JobTypes::woodCutter:return "WoodCutter\nNecesita 1 pan\nProduce 3 maderas";

    case JobTypes::ironMiner:return "IronMiner\nNecesita 2 pan\nProduce 1 hierro";

    case JobTypes::goldMiner:return "GoldMiner\nNecesita 10 pan\nProduce 1 oro";

    default:
        break;
    }
    return std::string();
}

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
    if (this->buttons["UNLOCK"]->getButtonState() == ButtonState::Pressed)
    {
        for (int i = 0; i < static_cast<int>(JobTypes::count); ++i)
        {
            if (this->jobs.getJobAmount(static_cast<JobTypes>(i)) == -1)
            {
                this->jobs.unlockJob(static_cast<JobTypes>(i));
                this->initJobList();
                this->initResourceList();
            }
        }

        for (int i = 0; i < static_cast<int>(ResourceTypes::count); ++i)
        {
            if (this->resources.getResourceAmount(static_cast<ResourceTypes>(i)) == -1)
            {
                this->resources.unlockResource(static_cast<ResourceTypes>(i));
                this->initJobList();
                this->initResourceList();
            }
        }
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
            this->tooltip.setString(this->getTooltipMessage(static_cast<JobTypes>(i)));
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
        else if (this->collectButtons[i]->getButtonState() == ButtonState::Pressed)
        {
            this->jobs.collectResources(resources,static_cast<JobTypes>(i));
            this->initJobList();
            this->initResourceList();
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

    target->draw(this->title);
    target->draw(this->villagersAvailable);
    for (size_t i = 0; i < addButtons.size(); i++)
    {
        if (this->collectButtons[i]->getButtonState() == ButtonState::Hover)
        {
            target->draw(this->backgroundTooltip);
            target->draw(this->tooltip);
        }
    }

    for (const auto& jobText : jobTexts)
    {
        target->draw(jobText);
    }

    for (const auto& amount : jobAmount)
    {
        target->draw(amount);
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
