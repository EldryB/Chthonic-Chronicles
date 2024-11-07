#pragma once

#include "Player.hpp"
#include "Enemy.hpp"

class Fight
{
public:
    Fight(Player* player, Enemy* enemy);
    void startTurn();

private:
    void updateTurnQueue(int turnCount);
    bool isFightOver();

    std::queue<Fighter*> turnQueue;
    std::vector<Fighter*> fighters;

    int turnCount;
    int currentTurn;
};

