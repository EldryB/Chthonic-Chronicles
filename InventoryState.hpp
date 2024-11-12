#pragma once

#include "MenuState.hpp"
#include "Player.hpp"

class InventoryState :
    public State
{
public:
    InventoryState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Player* _p);

    virtual ~InventoryState();

    void updateInput(const float& _dt);

    void updateButtons();

    void update(const float& _dt);

    void renderButtons(sf::RenderTarget* target = nullptr);

    void render(sf::RenderTarget* target = nullptr);

private:
    sf::Font font;
    std::vector<Button*> useButtons;
    Player* player;
    std::vector<Item*>* inventory = new std::vector<Item*>();

    sf::Text title;

    sf::Text message;

    sf::Sprite equip;
    sf::Text equipText;

    std::vector<sf::Text> itemNames;
    std::vector<sf::Text> itemAmounts;
    sf::Text itemDescription;
    sf::Sprite backgroundItemDescription;

    void initVariables();

    void initTextures();

    void initBackground();

    void initFonts();

    void initKeybinds();

    void initButtons();

    void initItemList();

    void initConsumableList();
};



