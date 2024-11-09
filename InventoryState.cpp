#include "InventoryState.hpp"

void InventoryState::initVariables()
{
    this->keyCode = " ";
}

void InventoryState::initTextures()
{
    if (!this->textures["Background"].loadFromFile("assets/textures/Backgrounds/inventory.jpg"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_BACKGROUND_TEXTURE!";
    }

    if (!this->textures["MenuButtonIdle"].loadFromFile("assets/textures/Buttons/MenuButtonIdle.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_MENU_BUTTON_IDLE_TEXTURE!";
    }

    if (!this->textures["MenuButtonHover"].loadFromFile("assets/textures/Buttons/MenuButtonHover.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_MENU_BUTTON_HOVER_TEXTURE!";
    }

    if (!this->textures["ITEMS_SHEET"].loadFromFile("assets/textures/Player/weapons.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_ITEMS_TEXTURE!";
    }
}

void InventoryState::initBackground()
{
    this->background.setTexture(this->textures["Background"]);
}

void InventoryState::initFonts()
{
    if (!this->font.loadFromFile("assets/fonts/font.ttf"))
    {
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_FONT";
    }

    this->title.setFont(this->font);
    this->title.setString("Inventory");
    this->title.setCharacterSize(36);
    this->title.setFillColor(sf::Color(206, 185, 141));
    this->title.setPosition(100, 30);

    this->backgroundItemDescription.setTexture(this->textures["MenuButtonIdle"]);
    this->backgroundItemDescription.setPosition(Settings::WINDOW_WIDTH - this->backgroundItemDescription.getGlobalBounds().width - 10.f, 
        Settings::WINDOW_HEIGHT - this->backgroundItemDescription.getGlobalBounds().height - 10.f);

    this->itemDescription.setFont(this->font);
    this->itemDescription.setString(" ");
    this->itemDescription.setCharacterSize(12);
    this->itemDescription.setFillColor(sf::Color::Black);

    sf::FloatRect itemDescriptionBounds = this->itemDescription.getGlobalBounds();
    this->itemDescription.setPosition(
        this->backgroundItemDescription.getPosition().x + (this->backgroundItemDescription.getGlobalBounds().width / 2.f)  - (itemDescriptionBounds.width / 2.f),
        this->backgroundItemDescription.getPosition().y + (this->backgroundItemDescription.getGlobalBounds().height / 2.f) - (itemDescriptionBounds.height / 2.f)
    );

    this->message.setFont(this->font);
    this->message.setString("Press 'C' to show controls");
    this->message.setCharacterSize(24);
    this->message.setFillColor(sf::Color::White);
    this->message.setPosition((Settings::WINDOW_WIDTH - this->message.getGlobalBounds().width), 20.f);
}

void InventoryState::initKeybinds()
{
    this->keybinds["CLOSE"] = this->supportedKeys->at("I");
    this->keybinds["CONTROLS"] = this->supportedKeys->at("C");
}

void InventoryState::initButtons()
{
    for (int i = 0; i < this->inventory->size(); ++i)
    {
        this->useButtons.push_back(new Button(325.f, 150.f + i * 40, *this->inventory->at(i)->getSprite(), &this->font, ""));
    }
}

InventoryState::InventoryState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Player* _p)
    : State(_window, _supportedKeys, _states)
{    
    this->initVariables();
    this->initTextures();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();


    this->player = _p;
    this->inventory = this->player->getInventory();
    this->initButtons();
    this->initItemList();
}

InventoryState::~InventoryState()
{
    for (auto& button : this->useButtons)
    {
        delete button;
    }
    this->useButtons.clear();
}

void InventoryState::initItemList()
{
    this->itemNames.clear();
    this->itemAmounts.clear();

    for (int i = 0; i < this->inventory->size(); ++i)
    {
        sf::Text itemName;
        itemName.setFont(font);
        itemName.setString(this->inventory->at(i)->getName());
        itemName.setCharacterSize(20);
        itemName.setFillColor(sf::Color(206, 185, 141));
        itemName.setPosition(400.f, 185.f + i * 40);
        itemNames.push_back(itemName);

        //sf::Text itemAmount;
        //itemAmount.setFont(font);
        //itemAmount.setString("x" + std::to_string(this->inventory->at(i)->getAmount()));
        //itemAmount.setCharacterSize(20);
        //itemAmount.setFillColor(sf::Color(206, 185, 141));
        //itemAmount.setPosition(650.f, 185.f + i * 40);
        //itemAmounts.push_back(itemAmount);
    }
}

void InventoryState::updateInput(const float& _dt)
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

void InventoryState::updateButtons()
{
    int i = 0;
    for (auto& button : this->useButtons)
    {
        button->update(this->mousePosView);

        if (button->getButtonState() == ButtonState::Idle)
        {
            button->setSprite(*this->inventory->at(i)->getSprite());
            button->setPosition(325.f, 150.f + i * 40);
        }

        else if (button->getButtonState() == ButtonState::Hover)
        {
            button->setSprite(*this->inventory->at(i)->getSprite());
            button->setPosition(325.f, 150.f + i * 40);
            this->itemDescription.setString(this->inventory->at(i)->getDescription());
            
            sf::FloatRect itemDescriptionBounds = this->itemDescription.getGlobalBounds();
            this->itemDescription.setPosition(
                this->backgroundItemDescription.getPosition().x + (this->backgroundItemDescription.getGlobalBounds().width / 2.f) - (itemDescriptionBounds.width / 2.f),
                this->backgroundItemDescription.getPosition().y + (this->backgroundItemDescription.getGlobalBounds().height / 2.f) - (itemDescriptionBounds.height / 2.f)
            );
        }

        else if (button->getButtonState() == ButtonState::Pressed)
        {
            this->inventory->at(i)->use();
            this->initItemList();
        }
        ++i;
    }
}

void InventoryState::update(const float& _dt)
{
    this->updateMousePositions();
    this->updateInput(_dt);
    this->updateButtons();
}

void InventoryState::renderButtons(sf::RenderTarget* target)
{
    for (auto& button : this->useButtons)
    {
        button->render(target);
    }
}

void InventoryState::render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = this->window;
    }

    target->draw(this->background);

    this->renderButtons(target);

    target->draw(this->title);
    target->draw(this->message);

    for (auto& button : this->useButtons)
    {
        if (button->getButtonState() == ButtonState::Hover)
        {
            target->draw(this->backgroundItemDescription);
            target->draw(this->itemDescription);
        }
    }

    for (const auto& itemName : itemNames)
    {
        target->draw(itemName);
    }

    /*if (this->itemAmounts[0].getString() != "-1")
    {
        for (const auto& itemAmount : itemAmounts)
        {
            target->draw(itemAmount);
        }
    }*/
}