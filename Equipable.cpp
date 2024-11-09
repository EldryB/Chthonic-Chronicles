#include "Equipable.hpp"

Equipable::Equipable(sf::Texture& _texture, std::string _name, std::string _description)
	: Item(_texture, _name, _description)
{

}

Equipable::~Equipable()
{

}

void Equipable::use()
{

}
