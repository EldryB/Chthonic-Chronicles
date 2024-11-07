#pragma once
#include "Entity.hpp"
#include "Item.hpp";

class Fighter :
    public Entity
{
public:
    Fighter(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float _attackPower, int _defense, int _initiative);

    virtual ~Fighter();

    virtual void update(const float& _dt);

    float getHp() const ;

    float getDamage() const ; 

    int getInitiative() const;

    void setHp(float _hp);

    virtual void setAttributes(float _x, float _y, std::string _name, float _hp, float _damage);

    virtual void attack(Fighter* target);

    void takeDamage(float _attackPower);

    bool isAlive() const;
    

protected:
    float hp;
    float attackPower;
    int defense;
    int initiative;

    void initVariables(std::string& _name, float& _hp, float& _damage, int& _defense, int& _initiative);


};

