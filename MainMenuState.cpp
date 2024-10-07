#include "MainMenuState.hpp"

void MainMenuState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("Up");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("Down");
	this->keybinds["SELECT"] = this->supportedKeys->at("Enter");

	//WS Up Down Enter
}

MainMenuState::MainMenuState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys)
	: State(_window, _supportedKeys)
{
	this->initKeybinds();

	this->texture.loadFromFile("assets/textures/start.png");
	this->background.setTexture(this->texture);
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::endState()
{
	std::cout << "Ending MainMenuState!" << "\n";
}

void MainMenuState::updateInput(const float& _dt)
{
	this->checkForQuit();


}

void MainMenuState::update(const float& _dt)
{
	this->updateInput(_dt);


}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
}