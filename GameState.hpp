#pragma once

#include "InventoryState.hpp"
#include "FightState.hpp"
#include "JobMenuState.hpp"
#include "Dice.hpp"

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
    Jobs* jobs;
    Resources* resources;
    int currentFrame;
    float timeSinceLastUpdate;
    float timeBetweenUpdates;
    sf::Font font;
    sf::Text text;
    sf::Text message;
    sf::Text message2;
    sf::Text stageText;
    std::stack<sf::Sprite> backgrounds;
    std::string check;
    bool isInLvl1;
    bool isBackgroundMoving;

    void initVariables();

    void initKeybinds();

    void initTextures();

    void initFighters();

    void initBackground();

    void initFonts();

    void createCombat();

    std::string getStringStage(CurrentStage _c);
};

