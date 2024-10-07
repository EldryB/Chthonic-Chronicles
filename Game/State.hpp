#pragma once

#include "Entity.hpp"

class State
{
public:
	State(sf::RenderWindow* _window, std::map<std::string, sf::Keyboard::Key>* _supportedKeys);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();
	virtual void endState() = 0;

	virtual void updateInput(const float& _dt) = 0;
	virtual void update(const float& _dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

protected:
	sf::RenderWindow* window;
	std::map<std::string, sf::Keyboard::Key>* supportedKeys;
	std::map<std::string, sf::Keyboard::Key> keybinds;
	bool quit;

	std::vector<sf::Texture> textures;

	virtual void initKeybinds() = 0;

};

