#pragma once
#include "Entity.hpp"

class Fighter :
    public Entity
{
public:
    Fighter(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float _damage);

    virtual ~Fighter();

    virtual void update(const float& _dt);

    virtual float getHp();

    virtual float getDamage();

    virtual void setHp(float _hp);

    virtual void setAttributes(float _x, float _y, std::string _name, float _hp, float _damage);

private:
    float hp;
    float damage;

    void initVariables(float& _hp, float& _damage);

    void initComponents();


};

