#pragma once

#include "Entity.hpp"

class State
{
public:
	State(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();
	virtual void endState() = 0;

	virtual void updateMousePositions();
	virtual void updateInput(const float& _dt) = 0;
	virtual void update(const float& _dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::unordered_map<std::string, sf::Keyboard::Key>* supportedKeys;
	std::unordered_map<std::string, sf::Keyboard::Key> keybinds;
	bool quit;
	sf::Sprite background;
	sf::Texture texture;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	std::unordered_map<std::string, sf::Texture> textures;

	virtual void initKeybinds() = 0;

};

