#include "GameState.hpp"

void GameState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
}

GameState::GameState(sf::RenderWindow* _window, std::map<std::string, sf::Keyboard::Key>* _supportedKeys)
	: State(_window, _supportedKeys)
{
	this->initKeybinds();
}

GameState::~GameState()
{

}

void GameState::endState()
{
	std::cout << "Ending GameState!" << "\n";
}

void GameState::updateInput(const float& _dt)
{
	this->checkForQuit();

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT")))
	{
		this->player.move(_dt, -1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT")))
	{
		this->player.move(_dt, 1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_UP")))
	{
		this->player.move(_dt, 0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_DOWN")))
	{
		this->player.move(_dt, 0.f, 1.f);
	}
}

void GameState::update(const float& _dt)
{
	this->updateInput(_dt);

	this->player.update(_dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	this->player.render(target);
}

