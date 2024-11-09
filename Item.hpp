#pragma once

#include "Settings.hpp"
#include "Fighter.hpp"

class Item
{
public:
	Item(sf::Texture& _texture, std::string _name, std::string _description);
	virtual ~Item();

	sf::Texture getTexture() const;
	sf::Sprite* getSprite() const;
	std::string getName() const;
	std::string getDescription() const;

	void setTexture(const sf::Texture& _texture);
	void setSprite(sf::Sprite* _sprite);
	void setPosition(float _x, float _y);
	void setName(std::string _name);
	void setDescription(std::string _description);
	void setIconRect(sf::IntRect icon_rect);

	virtual void use(Fighter* target);

	void render(sf::RenderTarget* target);

private:
	sf::Sprite* sprite = new sf::Sprite();
	
	std::string name;
	std::string description;
};

