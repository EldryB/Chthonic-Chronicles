#pragma once

#include "Item.hpp"

class Equipable :
    public Item
{
public:
    Equipable(sf::Texture& _texture, std::string _name, std::string _description);
    virtual ~Equipable();

    virtual void use();
};

