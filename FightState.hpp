#pragma once

#include "InventoryState.hpp"
#include "LostFightState.hpp"

class FightState :
    public State
{
public:
    FightState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Player* _p, Enemy* _enemy, sf::Vector2f _lastPos);

    virtual ~FightState();

    void updateInput(const float& _dt);

    void updateButtons();

    void update(const float& _dt);

    void render(sf::RenderTarget* target = nullptr);

    void renderButtons(sf::RenderTarget* target = nullptr);


private:
    Player* player;
    Enemy* enemy;
    sf::Font font;

    sf::Text text;
    sf::Text message;
    sf::Text message2;
    sf::Text textBox;
    sf::Text playerStats;

    std::vector<sf::RectangleShape> hpBar;
    std::vector<float> hpMax;
    sf::Vector2f lastPosition;
    std::queue<Fighter*> turnQueue;
    std::vector<Fighter*> fighters;
    bool playerTurn = true;
    std::unordered_map<std::string, Button*> buttons;
    int selectedButtonIndex;

    int turnCount;
    int currentTurn;
    sf::Clock clock;
    float count;

    void updateTurnQueue(int turnCount);

    void initVariables();

    void initKeybinds();

    void initTextures();

    void initFighters(Player* _p, Enemy* _enemy);

    void initBackground();

    void initFonts();

    void initButtons();
};

