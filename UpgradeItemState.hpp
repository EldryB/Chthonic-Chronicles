#pragma once
#include "State.hpp"
#include "Player.hpp"
#include "MenuState.hpp"

class UpgradeItemState :
    public State
{

public:
    UpgradeItemState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Player* _p);

    virtual ~UpgradeItemState();

    void updateInput(const float& _dt);

    void updateButtons();

    void update(const float& _dt);

    void render(sf::RenderTarget* target = nullptr);

    void renderButtons(sf::RenderTarget* target = nullptr);

    void upgradeItem(Item* it);

private:
    std::vector<Button*> useButtons;
    std::vector<Item*>* items = new std::vector<Item*>();
    Player* player;
    sf::Sprite toolTip;

    void initVariables();

    void initButtons();

    void initKeybinds();

    void initTextures();

    void initBackground();

    void initFonts();

};

