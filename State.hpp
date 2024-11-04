#pragma once

#include "Fighter.hpp"

class State
{
public:
	State(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states);
	virtual ~State();

	const bool& getQuit() const;

	const CurrentState getCurrentState() const;

	virtual void endState();

	virtual void updateMousePositions();
	virtual void updateInput(const float& _dt) = 0;
	virtual void update(const float& _dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

protected:
	CurrentState currentState;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::unordered_map<std::string, sf::Keyboard::Key>* supportedKeys;
	std::unordered_map<std::string, sf::Keyboard::Key> keybinds;
	std::string keyCode{ "" };
	bool quit;
	sf::Sprite background;
	sf::Text stage;
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	std::unordered_map<std::string, sf::Texture> textures;

	virtual void initVariables() = 0;
	virtual void initKeybinds() = 0;

	State() : states(nullptr), window(nullptr), supportedKeys(nullptr), quit(false) {}
};

