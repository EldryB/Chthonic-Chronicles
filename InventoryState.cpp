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

    this->texts["Title"].setFont(this->font);
    this->texts["Title"].setString("Inventory");
    this->texts["Title"].setCharacterSize(36);
    this->texts["Title"].setFillColor(sf::Color(206, 185, 141));
    this->texts["Title"].setPosition(100, 30);

    this->texts["ItemDescription"].setFont(this->font);
    this->texts["ItemDescription"].setString(" ");
    this->texts["ItemDescription"].setCharacterSize(12);
    this->texts["ItemDescription"].setFillColor(sf::Color::Black);
    this->texts["ItemDescription"].setPosition(
        this->backgroundItemDescription.getPosition().x + (this->backgroundItemDescription.getGlobalBounds().width / 2.f) - (this->texts["ItemDescription"].getGlobalBounds().width / 2.f),
        this->backgroundItemDescription.getPosition().y + (this->backgroundItemDescription.getGlobalBounds().height / 2.f) - (this->texts["ItemDescription"].getGlobalBounds().height / 2.f)
    );

    this->texts["EquippedWeapon"].setFont(this->font);
    this->texts["EquippedWeapon"].setString(" ");
    this->texts["EquippedWeapon"].setCharacterSize(12);
    this->texts["EquippedWeapon"].setFillColor(sf::Color::Black);
    this->texts["EquippedWeapon"].setPosition(
        this->equip.getPosition().x + (this->equip.getGlobalBounds().width / 2.f) - (this->texts["EquippedWeapon"].getGlobalBounds().width / 2.f),
        this->equip.getPosition().y + (this->equip.getGlobalBounds().height / 2.f) - (this->texts["EquippedWeapon"].getGlobalBounds().height / 2.f)
    );

    this->texts["EquippedArmor"].setFont(this->font);
    this->texts["EquippedArmor"].setString(" ");
    this->texts["EquippedArmor"].setCharacterSize(12);
    this->texts["EquippedArmor"].setFillColor(sf::Color::Black);
    this->texts["EquippedArmor"].setPosition(this->texts["EquippedWeapon"].getPosition().x, this->texts["EquippedWeapon"].getPosition().y + 15);
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

    this->backgroundItemDescription.setTexture(this->textures["MenuButtonIdle"]);
    this->backgroundItemDescription.setPosition(Settings::WINDOW_WIDTH - this->backgroundItemDescription.getGlobalBounds().width - 10.f,
        Settings::WINDOW_HEIGHT - this->backgroundItemDescription.getGlobalBounds().height - 10.f);

    this->equip.setTexture(this->textures["MenuButtonIdle"]);
    this->equip.setPosition(10,
        Settings::WINDOW_HEIGHT - this->backgroundItemDescription.getGlobalBounds().height - 10.f);

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

        if (Consumable* consumable = dynamic_cast<Consumable*>(this->inventory->at(i)))
        {
            sf::Text itemAmount;
            itemAmount.setFont(font);
            itemAmount.setString("x" + std::to_string(consumable->getAmount()));
            itemAmount.setCharacterSize(20);
            itemAmount.setFillColor(sf::Color(206, 185, 141));
            itemAmount.setPosition(650.f, 185.f + i * 40);
            itemAmounts.push_back(itemAmount);
        }
    }
}

void InventoryState::initConsumableList()
{
    this->itemAmounts.clear();

    for (int i = 0; i < this->inventory->size(); ++i)
    {
        if (Consumable* consumable = dynamic_cast<Consumable*>(this->inventory->at(i)))
        {
            sf::Text itemName;
            itemName.setFont(font);
            itemName.setString(this->inventory->at(i)->getName());
            itemName.setCharacterSize(20);
            itemName.setFillColor(sf::Color(206, 185, 141));
            itemName.setPosition(400.f, 185.f + i * 40);
            itemNames.push_back(itemName);
            
            sf::Text itemAmount;
            itemAmount.setFont(font);
            itemAmount.setString("x" + std::to_string(consumable->getAmount()));
            itemAmount.setCharacterSize(20);
            itemAmount.setFillColor(sf::Color(206, 185, 141));
            itemAmount.setPosition(650.f, 185.f + i * 40);
            itemAmounts.push_back(itemAmount);
        }
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
            this->texts["ItemDescription"].setString(this->inventory->at(i)->getDescription());
            this->texts["ItemDescription"].setPosition(
                this->backgroundItemDescription.getPosition().x + (this->backgroundItemDescription.getGlobalBounds().width / 2.f) - (this->texts["ItemDescription"].getGlobalBounds().width / 2.f),
                this->backgroundItemDescription.getPosition().y + (this->backgroundItemDescription.getGlobalBounds().height / 2.f) - (this->texts["ItemDescription"].getGlobalBounds().height / 2.f)
            );
        }
        else if (button->getButtonState() == ButtonState::Pressed)
        {
            this->inventory->at(i)->use(this->player);

            if (Consumable* consumable = dynamic_cast<Consumable*>(this->inventory->at(i)))
            {
                if (consumable->getAmount() == 0)
                {
                    this->inventory->erase(this->inventory->begin() + i);
                    delete button; 
                    this->useButtons.erase(this->useButtons.begin() + i);
                    --i;
                    this->initItemList();
                    continue;
                }
            }

            if (Weapon* c = dynamic_cast<Weapon*>(this->inventory->at(i)))
            {
                if (this->inventory->at(i)->isEquipped())
                {

                    //Aqui desequipo las otras armas que tenga equipadas
                    for (int j = 0; j < this->inventory->size(); ++j)
                    {
                        if (Weapon* c = dynamic_cast<Weapon*>(this->inventory->at(j)))
                        {
                            if (this->inventory->at(j)->isEquipped() && (this->inventory->at(j)->getName() != this->inventory->at(i)->getName()))
                            {
                                this->inventory->at(j)->use(this->player);
                                this->texts["EquippedWeapon"].setString(" ");
                            }
                        }
                    }

                    std::string textString = this->inventory->at(i)->getName() + " Equipped";
                    this->texts["EquippedWeapon"].setString(textString);
                    this->texts["EquippedWeapon"].setPosition(
                        this->equip.getPosition().x + (this->equip.getGlobalBounds().width / 2.f) - (this->texts["EquippedWeapon"].getGlobalBounds().width / 2.f),
                        this->equip.getPosition().y + (this->equip.getGlobalBounds().height / 2.f) - (this->texts["EquippedWeapon"].getGlobalBounds().height / 2.f)
                    );
                }
                else
                {
                    this->texts["EquippedWeapon"].setString(" ");
                }
            }

            if (Armor* a = dynamic_cast<Armor*>(this->inventory->at(i)))
            {
                if (this->inventory->at(i)->isEquipped())
                {
                    //Aqui desequipo las otras armaduras que tenga equipadas
                   for (int j = 0; j < this->inventory->size(); ++j)
                   {
                        if (Armor* c = dynamic_cast<Armor*>(this->inventory->at(j)))
                        {
                            if (this->inventory->at(j)->isEquipped() && (this->inventory->at(j)->getName() != this->inventory->at(i)->getName()))
                            {
                                this->inventory->at(j)->use(this->player);
                                this->texts["EquippedArmor"].setString(" ");
                            }
                        }
                   }

                    std::string textString = this->inventory->at(i)->getName() + "Equipped";
                    this->texts["EquippedArmor"].setString(textString);
                    this->texts["EquippedArmor"].setPosition(this->texts["EquippedWeapon"].getPosition().x, this->texts["EquippedWeapon"].getPosition().y + 15);
                }
                else
                {
                    this->texts["EquippedArmor"].setString(" ");
                }
            }
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

    target->draw(this->equip);

    for (auto text : this->texts)
    {
        if (text.first != "ItemDescription")
        {
            target->draw(text.second);
        }
    }

    int i = 0;
    for (auto& button : this->useButtons)
    {
        target->draw(itemNames[i]);

        if (button->getButtonState() == ButtonState::Hover)
        {
            target->draw(this->backgroundItemDescription);
            target->draw(this->texts["ItemDescription"]);
        }
        
        ++i;
    }

    for (auto itemAmount : itemAmounts)
    {
        target->draw(itemAmount);
    }
}