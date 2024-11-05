#pragma once

#include "LostFightState.hpp"
#include <vector>

class FightState :
    public State
{
public:
    FightState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Player* _p, sf::Vector2f _lastPos);

    virtual ~FightState();

    void updateInput(const float& _dt);

    void update(const float& _dt);

    void render(sf::RenderTarget* target = nullptr);


private:
    Player* player;
    std::vector<Fighter*> enemies;
    sf::Font font;
    sf::Text text;
    sf::Text message;
    std::vector<sf::RectangleShape> hpBar;
    std::vector<float> hpMax;
    sf::Vector2f lastPosition;


    void initVariables();

    void initKeybinds();

    void initTextures();

    void initFighters(Player* _p);

    void initBackground();

    void initFonts();
};

