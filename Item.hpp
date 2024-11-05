#pragma once

#include "Settings.hpp"

class Item
{
public:
	Item(sf::Texture& _texture, std::string _name, int _amount, std::string _description);
	virtual ~Item();

	sf::Sprite* getSprite() const;
	std::string getName() const;
	int getAmount() const;
	std::string getDescription() const;

	void setTexture(const sf::Texture& _texture);
	void setSprite(sf::Sprite* _sprite);
	void setPosition(float _x, float _y);
	void setName(std::string _name);
	void setAmount(int _amount);
	void setDescription(std::string _description);

	virtual void use();

	virtual void render(sf::RenderTarget* target);

private:
	sf::Sprite* sprite = new sf::Sprite();
	
	std::string name;
	int amount;
	std::string description;
};

