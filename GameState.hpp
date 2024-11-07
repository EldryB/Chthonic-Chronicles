#pragma once

#include "InventoryState.hpp"
#include "FightState.hpp"
#include "JobMenuState.hpp"

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

    void render(sf::RenderTarget* target = nullptr);

private:
    Player* player;
    std::vector<Item*> items;
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
    float dt;

    void initVariables();

    void initKeybinds();

    void initTextures();

    void initFighters();

    void initItems();

    void initBackground();

    void initFonts();

    std::string getStringStage(CurrentStage _c);
};

