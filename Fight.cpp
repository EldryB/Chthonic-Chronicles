#include "Fight.hpp"

Fight::Fight(Player* player, Enemy* enemy) : turnCount(0), currentTurn(0)
{
    fighters.push_back(player);
    fighters.push_back(enemy);
}

void Fight::updateTurnQueue(int turnCount)
{
    for (const auto& fighter : fighters)
    {
        if (turnCount % (100 / fighter->getInitiative()) == 0)
        {
            turnQueue.push(fighter);
        }
    }
}

bool Fight::isFightOver()
{
    for (const auto& fighter : fighters)
    {
        if (!fighter->isAlive())
        {
            return true;
        }
    }
    return false;
}

void Fight::startTurn()
{
    while (!isFightOver())
    {
        turnCount++;
        updateTurnQueue(turnCount);

        if (isFightOver())
        {
            std::cout << "El Fighte ha terminado." << std::endl;
            return;
        }

        if (!turnQueue.empty())
        {
            currentTurn++;
            std::cout << "Turno " << currentTurn << std::endl;
            auto currentFighter = turnQueue.front();
            std::cout << currentFighter->getName() << " empieza su turno." << std::endl;

            std::cout << currentFighter->getName() << " vida: " << currentFighter->getHp() << std::endl;

            if (Player* p = dynamic_cast<Player*>(currentFighter)) 
            {
                p->attack(fighters[1]);
            }
            else if (Enemy* e = dynamic_cast<Enemy*>(currentFighter)) 
            {
                e->attack(fighters[0]);
            }



            std::cout << std::endl;

            if (isFightOver())
            {
                std::cout << "El Fighte ha terminado." << std::endl;
                return;
            }

            turnQueue.pop();
        }
    }
}
