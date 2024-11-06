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

    if (!this->textures["UseButton"].loadFromFile("assets/textures/Buttons/useButton.png"))
    {
        throw "ERROR::MENU_STATE::COULD_NOT_LOAD_SUBSTRACT_BUTTON_TEXTURE!";
    }

    if (!this->textures["UseButtonHover"].loadFromFile("assets/textures/Buttons/useButtonHover.png"))
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

    if (!this->textures["ITEMS_SHEET"].loadFromFile("assets/textures/Player/swords.png"))
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
    this->itemDescription.setPosition
    (
        this->backgroundItemDescription.getPosition().x + (this->backgroundItemDescription.getGlobalBounds().width / 2.f) - this->backgroundItemDescription.getGlobalBounds().width / 2.7f,
        this->backgroundItemDescription.getPosition().y + (this->backgroundItemDescription.getGlobalBounds().height / 2.5f) - this->backgroundItemDescription.getGlobalBounds().height / 23.f
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

//void InventoryState::initButtons()
//{
//    for (int i = 0; i < this->inventory->size(); ++i)
//    {
//        this->useButtons.push_back(new Button(475.f, 160.f + i * 40, *this->inventory->at(i)->getSprite(), &this->font, ""));
//    }
//}

InventoryState::InventoryState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Player* _p)
    : State(_window, _supportedKeys, _states)
{
    Item* item = new Item(this->textures["ITEMS_SHEET"], "Sword", 1, "Amazing sword!");
    item->addItemIcon("SWORD_2", 77, 0, 43, 23);
    item->setItemIcon("SWORD_2");
    _p->addItem(item);
    
    this->initVariables();
    this->initTextures();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->inventory = _p->getInventory();
    //this->initButtons();
    this->initItemList();
    this->player = _p;
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
    this->useButtons.clear();

    for (int i = 0; i < this->inventory->size(); ++i)
    {
        sf::Text itemName;
        itemName.setFont(font);
        itemName.setString(this->inventory->at(i)->getName());
        itemName.setCharacterSize(20);
        itemName.setFillColor(sf::Color(206, 185, 141));
        itemName.setPosition(325.f, 175.f + i * 40);
        itemNames.push_back(itemName);

        sf::Text itemAmount;
        itemAmount.setFont(font);
        itemAmount.setString(std::to_string(this->inventory->at(i)->getAmount()));
        itemAmount.setCharacterSize(20);
        itemAmount.setFillColor(sf::Color(206, 185, 141));
        itemAmount.setPosition(425.f, 175.f + i * 40);
        itemAmounts.push_back(itemAmount);
        
        Button* button = new Button(475.f, 160.f + i * 40, *this->inventory->at(i)->getSprite(), &this->font, "");
        this->useButtons.push_back(button);
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
            button->setTexture(this->textures["UseButton"]);
        }

        else if (button->getButtonState() == ButtonState::Hover)
        {
            button->setTexture(this->textures["UseButtonHover"]);
            this->itemDescription.setString(this->inventory->at(i)->getDescription());
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

    if (this->itemAmounts[0].getString() != "-1")
    {
        for (const auto& itemAmount : itemAmounts)
        {
            target->draw(itemAmount);
        }
    }
}