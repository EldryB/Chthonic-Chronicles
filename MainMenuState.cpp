#include "MainMenuState.hpp"

void MainMenuState::initVariables()
{
	this->selectedButtonIndex = 0;
	this->keyPressTimer = 0.f;
	this->keyPressDelay = 0.2f;
}

void MainMenuState::initTextures()
{
	if (!this->textures["Background"].loadFromFile("assets/textures/Backgrounds/start.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_BACKGROUND_TEXTURE!";
	}
	
	if (!this->textures["MainMenuButtonIdle"].loadFromFile("assets/textures/MenuButtonIdle.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_MAIN_MENU_BUTTON_IDLE_TEXTURE!";
	}

	if (!this->textures["MainMenuButtonHover"].loadFromFile("assets/textures/MenuButtonHover.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_MAIN_MENU_BUTTON_HOVER_TEXTURE!";
	}
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
		throw "ERROR::MENU_STATE::COULD_NOT_LOAD_FONT";
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
	this->buttons["NEW_GAME_STATE"] = new Button(100.f, 300.f, this->textures["MainMenuButtonIdle"], &this->font, "New Game");
	this->buttons["LOAD_GAME_STATE"] = new Button(100.f, 400.f, this->textures["MainMenuButtonIdle"], &this->font, "Load Game");
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
	this->keyPressTimer += _dt;
	
	if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_UP"]) && this->keyPressTimer >= this->keyPressDelay)
	{
		if (this->selectedButtonIndex < this->buttons.size() - 1)
		{
			++this->selectedButtonIndex;
			this->keyPressTimer = 0.f;
		}
	}

	if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_DOWN"]) && this->keyPressTimer >= this->keyPressDelay)
	{
		if (this->selectedButtonIndex > 0)
		{
			--this->selectedButtonIndex;
			this->keyPressTimer = 0.f;
		}
	}

	if (sf::Keyboard::isKeyPressed(this->keybinds["SELECT"]) && this->keyPressTimer >= this->keyPressDelay)
	{
		auto it = std::next(this->buttons.begin(), this->selectedButtonIndex);
		if (it != this->buttons.end())
		{
			if (it->first == "NEW_GAME_STATE")
			{
				this->states->push(new GameState(this->window, this->supportedKeys, this->states));
			}
			else if (it->first == "LOAD_GAME_STATE")
			{
				Fighter* loadedPlayer = nullptr;
				dataManagement.loadPlayerFromFile("player.json", loadedPlayer);
				this->states->push(new GameState(this->window, this->supportedKeys, this->states, loadedPlayer));
			}
			this->keyPressTimer = 0.f;
		}
	}
}

void MainMenuState::updateButtons()
{
	int index = 0;
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);

		if (it.second->isIdle())
		{
			it.second->setTexture(this->textures["MainMenuButtonIdle"]);
			it.second->setTextFillColor(sf::Color::White);
		}

		if (it.second->isHover())
		{
			it.second->setTexture(this->textures["MainMenuButtonHover"]);
			it.second->setTextFillColor(sf::Color(150, 104, 28));
		}

		if (index == this->selectedButtonIndex)
		{
			it.second->setTexture(this->textures["MainMenuButtonHover"]);
			it.second->setTextFillColor(sf::Color(150, 104, 28));
		}

		++index;
	}

	if (this->buttons["NEW_GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	else if (this->buttons["LOAD_GAME_STATE"]->isPressed())
	{
		Fighter* loadedPlayer = nullptr;
		dataManagement.loadPlayerFromFile("player.json", loadedPlayer);
		this->states->push(new GameState(this->window, this->supportedKeys, this->states, loadedPlayer));
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