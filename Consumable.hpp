#pragma once

#include "Item.hpp"

class Consumable :
    public Item
{
public:
    Consumable(sf::Texture& _texture, std::string _name, int _amount, std::string _description);
    virtual ~Consumable();

    int getAmount() const;
    void setAmount(int _amount);
    void addAmount(int _amount);
    void substractAmount(int _amount);

    virtual void use();

private:
    int amount;
};

