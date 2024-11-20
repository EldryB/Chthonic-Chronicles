#pragma once

#include "FightState.hpp"
#include "JobMenuState.hpp"
#include "Dice.hpp"
#include "StoreState.hpp"
#include "UpgradeItemState.hpp"

class GameState :
    public State
{
public:
    GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states);

    GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Player* _p);

    virtual ~GameState();

    void updateInput(const float& _dt);

    void updateInput2(const float& _dt);

    void update(const float& _dt);

    void updateMap(const float& _dt);

    void render(sf::RenderTarget* target = nullptr);

private:
    Player* player;
    std::vector<Enemy*> enemies;
    std::vector<Item*> items;
    Jobs* jobs;
    Resources* resources;
    std::vector<sf::Sprite> houses;
    std::vector<sf::Sprite> rooms;
    std::stack<sf::Sprite> backgrounds;
    std::string check;

    Enemy* enemyToShow;
    float enemyVisibleTime;
    sf::Clock enemyVisibleTimer;
    
    bool isInLvl1;
    bool showEnemy;
    bool isBackgroundMoving;

    void initVariables();

    void initKeybinds();

    void initTextures();

    void initFighters();

    void initItems();

    void initBackground();

    void initFonts();

    void initRooms();

    void createCombat();

    std::string getStringStage(CurrentStage _c);
};

