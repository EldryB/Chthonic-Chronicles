#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class ButtonStates
{
	Idle,
	Hover,
	Pressed
};

class Button
{
public:
	Button(float _x, float _y, sf::Texture _texture, sf::Font* _font, std::string _text);

	virtual ~Button();

	const bool isIdle() const;

	const bool isHover() const;

	const bool isPressed() const;

	void setTexture(const sf::Texture& _texture);

	void setTextFillColor(const sf::Color& color);

	void update(const sf::Vector2f mousePos);

	void render(sf::RenderTarget* target);

private:
	ButtonStates buttonState;
	sf::Texture texture; 
	sf::Sprite sprite;
	sf::Font* font;
	sf::Text text;
};

