#include "MenuState.hpp"

void MenuState::initVariables()
{
	this->currentState = CurrentState::PauseMenu;
	this->selectedButtonIndex = 0;
	this->keyCode = " ";
}

void MenuState::initTextures()
{
	if (!this->textures["Background"].loadFromFile("assets/textures/Backgrounds/pauseMenu.png"))
	{
		throw "ERROR::MENU_STATE::COULD_NOT_LOAD_BACKGROUND_TEXTURE!";
	}

	if (!this->textures["MenuButtonIdle"].loadFromFile("assets/textures/Buttons/MenuButtonIdle.png"))
	{
		throw "ERROR::MENU_STATE::COULD_NOT_LOAD_MENU_BUTTON_IDLE_TEXTURE!";
	}

	if (!this->textures["MenuButtonHover"].loadFromFile("assets/textures/Buttons/MenuButtonHover.png"))
	{
		throw "ERROR::MENU_STATE::COULD_NOT_LOAD_MENU_BUTTON_HOVER_TEXTURE!";
	}
}

void MenuState::initBackground()
{
	this->background.setTexture(this->textures["Background"]);
}

void MenuState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/font.ttf"))
	{
		throw "ERROR::MENU_STATE::COULD_NOT_LOAD_FONT";
	}

	this->message.setFont(this->font);
	this->message.setString("Press 'C' to show controls");
	this->message.setCharacterSize(24);
	this->message.setFillColor(sf::Color::White);
	this->message.setPosition((Settings::WINDOW_WIDTH - this->message.getGlobalBounds().width), (Settings::WINDOW_HEIGHT - this->message.getGlobalBounds().height));
}

void MenuState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("Left");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("Right");
	this->keybinds["SELECT"] = this->supportedKeys->at("Enter");
	this->keybinds["CONTROLS"] = this->supportedKeys->at("C");
}

void MenuState::initButtons()
{
	this->buttons["SAVE_AND_QUIT"] = new Button(
		300.f, 166.5f,
		this->textures["MenuButtonIdle"], &this->font, "SAVE AND\n    QUIT");

	this->buttons["NO_SAVE_AND_QUIT"] = new Button(
		520.f, 166.5f, 
		this->textures["MenuButtonIdle"], &this->font, "NO SAVE AND\n    QUIT");

	this->buttons["BACK_TO_THE_GAME"] = new Button(
		(Settings::WINDOW_WIDTH - this->textures["MenuButtonIdle"].getSize().x) / 2.f, 372.5f,
		this->textures["MenuButtonIdle"], &this->font, "<- BACK TO\nTHE GAME");
}

MenuState::MenuState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Fighter* _p)
	: State(_window, _supportedKeys, _states)
{
	this->initVariables();
	this->initTextures();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->player = _p;
}

MenuState::~MenuState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MenuState::updateInput(const float& _dt)
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

	if (sf::Keyboard::isKeyPressed(this->keybinds["CLOSE"]))
	{
		this->keyCode = "CLOSE";
	}
	else
	{
		if (this->keyCode == "CLOSE")
		{
			this->keyCode = " ";
			this->states->pop();
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
				if (it->first == "BACK_TO_THE_GAME")
				{
					this->states->pop();
				}
				else if (it->first == "NO_SAVE_AND_QUIT")
				{
					this->states->pop();
					this->states->pop();
				}
				else if (it->first == "SAVE_AND_QUIT")
				{
					this->states->pop();
					this->dataManagement.savePlayerToFile(player, "player.json");
					this->states->pop();
				}
			}
		}
	}
}

void MenuState::updateButtons()
{
	int index = 0;
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);

		if (it.second->getButtonState() == ButtonState::Idle)
		{
			it.second->setTexture(this->textures["MenuButtonIdle"]);
			it.second->setTextFillColor(sf::Color(21, 26, 38));
		}

		if (it.second->getButtonState() == ButtonState::Hover || index == this->selectedButtonIndex)
		{
			it.second->setTexture(this->textures["MenuButtonHover"]);
			it.second->setTextFillColor(sf::Color(96, 60, 3));
		}

		++index;
	}

	if (this->buttons["BACK_TO_THE_GAME"]->getButtonState() == ButtonState::Pressed)
	{
		this->states->pop();
	}
	if (this->buttons["NO_SAVE_AND_QUIT"]->getButtonState() == ButtonState::Pressed)
	{
		this->states->pop();
		this->states->pop();
	}
	if (this->buttons["SAVE_AND_QUIT"]->getButtonState() == ButtonState::Pressed)
	{
		this->states->pop();
		this->dataManagement.savePlayerToFile(player, "player.json");
		this->states->pop();
	}
}

void MenuState::update(const float& _dt)
{
	this->updateMousePositions();
	this->updateInput(_dt);
	this->updateButtons();
}

void MenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);

	this->renderButtons(target);

	target->draw(this->message);
}
