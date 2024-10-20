#pragma once
#include "State.hpp"
#include"MenuState.hpp"
#include <vector>

class FightState :
    public State
{
public:

    FightState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Fighter* _p);

    virtual ~FightState();

    void updateInput(const float& _dt);

    void update(const float& _dt);

    void render(sf::RenderTarget* target = nullptr);


private:
    Fighter* player;
    std::vector<Fighter*> enemies;
    sf::Font font;
    sf::Text text;

    void initVariables();

    void initKeybinds();

    void initTextures();

    void initFighters(Fighter* _p);

    void initBackground();

    void initFonts();

    void playerWeakAttack(int& positionEnemy);
};

