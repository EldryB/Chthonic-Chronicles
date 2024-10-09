#include "MainMenuState.hpp"

void MainMenuState::initVariables()
{

}

void MainMenuState::initTextures()
{
	this->texture.loadFromFile("assets/textures/start.png");
	this->textures["Background"] = this->texture;
	
	this->texture.loadFromFile("assets/textures/mainMenuButtonIdle.png");
	this->textures["MainMenuButtonIdle"] = this->texture;

	this->texture.loadFromFile("assets/textures/mainMenuButtonHover.png");
	this->textures["MainMenuButtonHover"] = this->texture;
}

void MainMenuState::initBackground()
{
	this->background.setTexture(this->textures["Background"]);
	this->background.setScale(float(Settings::WINDOW_WIDTH) / float(Settings::VIRTUAL_WIDTH), float(Settings::WINDOW_HEIGHT) / float(Settings::VIRTUAL_HEIGHT));
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/font.ttf"))
	{
		throw("COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("Up");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("Down");
	this->keybinds["SELECT"] = this->supportedKeys->at("Enter");
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(100, 400, this->textures["MainMenuButtonIdle"], &this->font, "New Game");
}

MainMenuState::MainMenuState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states)
	: State(_window, _supportedKeys, _states)
{
	this->initVariables();
	this->initTextures();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::updateInput(const float& _dt)
{
	
}

void MainMenuState::updateButtons()
{
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
	
	if (this->buttons["GAME_STATE"]->isIdle())
	{
		this->buttons["GAME_STATE"]->setTexture(this->textures["MainMenuButtonIdle"]);
		this->buttons["GAME_STATE"]->setTextFillColor(sf::Color::White);
	}
	
	if (this->buttons["GAME_STATE"]->isHover())
	{
		this->buttons["GAME_STATE"]->setTexture(this->textures["MainMenuButtonHover"]);
		this->buttons["GAME_STATE"]->setTextFillColor(sf::Color( 150, 104, 28 ));
	}
	
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

}

void MainMenuState::update(const float& _dt)
{
	this->updateMousePositions();
	this->updateInput(_dt);
	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);

	this->renderButtons(target);
}