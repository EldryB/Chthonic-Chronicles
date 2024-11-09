#include "Consumable.hpp"

Consumable::Consumable(sf::Texture& _texture, std::string _name, int _amount, std::string _description)
	: amount(_amount), Item(_texture, _name, _description)
{

}

Consumable::~Consumable()
{

}

int Consumable::getAmount() const
{
	return this->amount;
}

void Consumable::setAmount(int _amount)
{
	this->amount = _amount;
}

void Consumable::addAmount(int _amount)
{
	this->setAmount(this->getAmount() + _amount);
}

void Consumable::substractAmount(int _amount)
{
	if (this->getAmount() - _amount >= 0)
	{
		this->setAmount(this->getAmount() - _amount);
	}
}

void Consumable::use()
{

}


