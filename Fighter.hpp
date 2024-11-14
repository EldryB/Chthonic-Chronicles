#pragma once
#include "Entity.hpp"

class Fighter :
    public Entity
{
public:
    Fighter(float _x, float _y, sf::Texture& texture_sheet, std::string _name, float _hp, float _attackPower, int _defense, int _initiative);

    virtual ~Fighter();

    virtual void update(const float& _dt);

    float getHp() const;

    float getHpMax() const;

    float getAttackPower() const; 

    int getDefense() const;

    int getInitiative() const;

    void setHp(float _hp);

    void setHpMax(float _hpMax);

    void setAttackPower(float attack_power);

    void setDefense(int _defense);

    void setInitiative(int _initiative);

    virtual void setAttributes(float _x, float _y, std::string _name, float _hp, float _damage);

    virtual void attack(Fighter* target);

    void takeDamage(float _attackPower);

    bool isAlive() const;
    

protected:
    float hp;
    float hpMax;
    float attackPower;
    int defense;
    int initiative;

    void initVariables(std::string& _name, float& _hp, float& _damage, int& _defense, int& _initiative);


};

