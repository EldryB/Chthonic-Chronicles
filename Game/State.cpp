#include "State.hpp"

State::State(sf::RenderWindow* _window, std::map<std::string, sf::Keyboard::Key>* _supportedKeys)
{
	this->window = _window;
	this->supportedKeys = _supportedKeys;
	this->quit = false;
}

State::~State()
{

}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("CLOSE")))
	{
		this->quit = true;
	}
}
