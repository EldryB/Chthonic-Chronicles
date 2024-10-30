#include "MainMenuState.hpp"

void MainMenuState::initVariables()
{
	this->currentState = CurrentState::MainMenu;
	this->selectedButtonIndex = 0;
	this->keyCode = " ";
}

void MainMenuState::initTextures()
{
	if (!this->textures["Background"].loadFromFile("assets/textures/Backgrounds/mainMenu.jpg"))
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
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/font.ttf"))
	{
		throw "ERROR::MENU_STATE::COULD_NOT_LOAD_FONT";
	}

	this->title.setFont(this->font);
	this->title.setString("CHTHONIC CHRONICLES");
	this->title.setCharacterSize(42);
	this->title.setFillColor(sf::Color(206, 185, 141));
	this->title.setPosition((Settings::WINDOW_WIDTH - this->title.getGlobalBounds().width) / 2, 75);
}

void MainMenuState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("Left");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("Right");
	this->keybinds["SELECT"] = this->supportedKeys->at("Enter");
	this->keybinds["CONTROLS"] = this->supportedKeys->at("C");
}

void MainMenuState::initButtons()
{
	this->buttons["LOAD_GAME_STATE"] = new Button(700.f, 175.f, this->textures["MainMenuButtonIdle"], &this->font, "LOAD GAME");
	this->buttons["NEW_GAME_STATE"] = new Button(125.f, 175.f, this->textures["MainMenuButtonIdle"], &this->font, "NEW GAME");
	
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
	if (sf::Keyboard::isKeyPressed(this->keybinds["CONTROLS"]))
	{
		this->keyCode = "CONTROLS";
	}
	else
	{
		if (this->keyCode == "CONTROLS")
		{
			this->keyCode = " ";
			this->states->push(new ControlsState(this->window, this->supportedKeys, this->states));
		}
	}
	
	if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_LEFT"]))
	{
		this->keyCode = "MOVE_LEFT";
	}
	else
	{
		if (this->keyCode == "MOVE_LEFT")
		{
			this->keyCode = " ";
			if (this->selectedButtonIndex > 0)
			{
				--this->selectedButtonIndex;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_RIGHT"]))
	{
		this->keyCode = "MOVE_RIGHT";
	}
	else
	{
		if (this->keyCode == "MOVE_RIGHT")
		{
			this->keyCode = " ";
			if (this->selectedButtonIndex < this->buttons.size() - 1)
			{
				++this->selectedButtonIndex;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(this->keybinds["SELECT"]))
	{
		this->keyCode = "SELECT";
	}
	else
	{
		if (this->keyCode == "SELECT")
		{
			this->keyCode = " ";
			auto it = std::next(this->buttons.begin(), this->selectedButtonIndex);
			if (it != this->buttons.end())
			{
				if (it->first == "NEW_GAME_STATE")
				{
					this->states->push(new GameState(this->window, this->supportedKeys, this->states));
				}
				else if (it->first == "LOAD_GAME_STATE")
				{
					Fighter* loadedPlayer = new Fighter(500.f, 370, this->textures["PLAYER_LEFT"], "Player", 10, 10);
					dataManagement.loadPlayerFromFile("player.json", loadedPlayer);
					this->states->push(new GameState(this->window, this->supportedKeys, this->states, loadedPlayer));
				}
			}
		}
	}
}

void MainMenuState::updateButtons()
{
	int index = 0;
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);

		if (it.second->getButtonState() == ButtonState::Idle)
		{
			it.second->setTexture(this->textures["MainMenuButtonIdle"]);
			it.second->setTextFillColor(sf::Color(21, 26, 38));
		}

		if (it.second->getButtonState() == ButtonState::Hover || index == this->selectedButtonIndex)
		{
			it.second->setTexture(this->textures["MainMenuButtonHover"]);
			it.second->setTextFillColor(sf::Color(96, 60, 3));
		}

		++index;
	}

	if (this->buttons["NEW_GAME_STATE"]->getButtonState() == ButtonState::Pressed)
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	else if (this->buttons["LOAD_GAME_STATE"]->getButtonState() == ButtonState::Pressed)
	{
		Fighter* loadedPlayer = new Fighter(500.f, 370, this->textures["PLAYER_LEFT"], "Player", 10, 10);
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

	target->draw(this->title);
}