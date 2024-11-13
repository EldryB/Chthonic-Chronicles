#pragma once

#include "MenuState.hpp"

class InventoryState :
    public State
{
public:
    InventoryState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Player* _p, bool show_consumables_only = false);

    virtual ~InventoryState();

    void updateInput(const float& _dt);

    void updateButtons();

    void update(const float& _dt);

    void renderButtons(sf::RenderTarget* target = nullptr);

    void render(sf::RenderTarget* target = nullptr);

private:
    std::vector<Button*> useButtons;
    Player* player;
    std::vector<Item*>* inventory = new std::vector<Item*>();
    bool showConsumablesOnly;

    sf::Sprite equip;

    std::vector<sf::Text> itemNames;
    std::vector<sf::Text> itemAmounts;
    sf::Sprite backgroundItemDescription;

    void initVariables();

    void initTextures();

    void initBackground();

    void initFonts();

    void initKeybinds();

    void initButtons();

    void initItemList();
};



