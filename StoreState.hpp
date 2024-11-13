#pragma once
#include "MenuState.hpp"
#include "Enemy.hpp"

class StoreState :
    public State
{
public:
    StoreState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Player* _p, std::vector<Item*>* _items);

    virtual ~StoreState();

    void updateInput(const float& _dt);

    void update(const float& _dt);

    void render(sf::RenderTarget* target = nullptr);

    void takeItem();


private:

    std::vector<Item*>* items = new std::vector<Item*>();
    std::vector<Item*>* listItems = new std::vector<Item*>();
    Player* player;
    bool isBackgroundMoving;
    std::string check;

    void initVariables();

    void initKeybinds();

    void initTextures();

    void initItems();

    void initBackground();

    void initFonts();

    std::string getStringStage(CurrentStage _c);

    void updateMap(const float& dt);
};

