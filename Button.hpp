#pragma once

#include "Settings.hpp"

enum class ButtonState
{
	Idle,
	Hover,
	Pressed
};

class Button
{
public:
	Button(float _x, float _y, sf::Texture _texture, sf::Font* _font, std::string _text);

	Button(float _x, float _y, sf::Sprite _sprite, sf::Font* _font, std::string _text);

	virtual ~Button();

	const bool isIdle() const;

	const bool isHover() const;

	const bool isPressed() const;

	const ButtonState getButtonState() const;

	void setTexture(const sf::Texture& _texture);

	void setSprite(const sf::Sprite& _sprite);

	void setTextCharacterSize(unsigned int size);
	
	void setTextFillColor(const sf::Color& color);

	void setPosition(float _x, float _y);

	void update(const sf::Vector2f mousePos);

	void render(sf::RenderTarget* target);

private:
	ButtonState buttonState;
	sf::Texture texture; 
	sf::Sprite sprite;
	sf::Font* font;
	sf::Text text;
	std::string keyCode;
};

