#include "Button.hpp"

Button::Button(float _x, float _y, sf::Texture _texture, sf::Font* _font, std::string _text)
{
	this->buttonState = ButtonStates::Idle;
	this->texture = _texture;
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(_x, _y);
	
	this->font = _font;
	this->text.setFont(*this->font);
	this->text.setString(_text);
	this->text.setCharacterSize(20);
	this->text.setFillColor(sf::Color::White);
	this->text.setPosition(
		this->sprite.getPosition().x + (this->sprite.getGlobalBounds().width / 2.f) - this->sprite.getGlobalBounds().width / 4.f,
		this->sprite.getPosition().y + (this->sprite.getGlobalBounds().height / 2.f) - this->sprite.getGlobalBounds().height / 16.f
	);

}

Button::~Button()
{

}

const bool Button::isPressed() const
{
	if (this->buttonState == ButtonStates::Pressed)
	{
		return true;
	}
	
	return false;
}

void Button::update(const sf::Vector2f mousePos)
{
	this->buttonState = ButtonStates::Idle;

	if (this->sprite.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = ButtonStates::Hover;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = ButtonStates::Pressed;
		}
	}

	//A different sprite for each state
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	target->draw(this->text);
}
