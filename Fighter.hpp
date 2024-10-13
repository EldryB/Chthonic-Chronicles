#pragma once
#include "Entity.hpp"

class Fighter :
    public Entity
{
public: 
    Fighter(float _x, float _y, sf::Texture* _texture, std::string _name);
    virtual ~Fighter();

private:
    void initVariables();
    void initComponents();
};

