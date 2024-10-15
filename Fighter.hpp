#pragma once
#include "Entity.hpp"

class Fighter :
    public Entity
{
public:
    Fighter(float _x, float _y, sf::Texture& texture_sheet, std::string _name);

    virtual ~Fighter();

    virtual void update(const float& _dt);

private:
    void initVariables();

    void initComponents();


};

