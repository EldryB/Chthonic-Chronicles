#pragma once

#include "MainMenuState.hpp"

class Game
{
public:
	Game();
	virtual ~Game();

	//Functions
	void endApplication();
	void updateDt();
	void updateSFMLEvents();
	void update();
	void render();
	void run();

private:
	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;

	std::stack<State*> states;
	std::unordered_map<std::string, sf::Keyboard::Key> supportedKeys;

	sf::Clock dtClock;
	float dt;

	//Initialization
	void initWindow();
	void initKeys();
	void initStates();
};
