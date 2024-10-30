#include "LostFightState.hpp"

void LostFightState::initVariables()
{
	this->currentState = CurrentState::LostFight;
	this->selectedButtonIndex = 0;
	this->keyCode = " ";
}

void LostFightState::initTextures()
{
	if (!this->textures["Background"].loadFromFile("assets/textures/Backgrounds/lostFight.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_BACKGROUND_TEXTURE!";
	}

	if (!this->textures["MainMenuButtonIdle"].loadFromFile("assets/textures/MenuButtonIdle.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_MENU_BUTTON_IDLE_TEXTURE!";
	}

	if (!this->textures["MainMenuButtonHover"].loadFromFile("assets/textures/MenuButtonHover.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_MENU_BUTTON_HOVER_TEXTURE!";
	}
}

void LostFightState::initBackground()
{
	this->background.setTexture(this->textures["Background"]);
}

void LostFightState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/font.ttf"))
	{
		throw "ERROR::MENU_STATE::COULD_NOT_LOAD_FONT";
	}

	this->title.setFont(this->font);
	this->title.setString("YOU LOST...");
	this->title.setCharacterSize(42);
	this->title.setFillColor(sf::Color(206, 185, 141));
	this->title.setPosition((Settings::WINDOW_WIDTH - this->title.getGlobalBounds().width) / 2, 75);

	this->message.setFont(this->font);
	this->message.setString("Press 'C' to show controls");
	this->message.setCharacterSize(24);
	this->message.setFillColor(sf::Color::White);
	this->message.setPosition((Settings::WINDOW_WIDTH - this->message.getGlobalBounds().width), 20.f);
}

void LostFightState::initKeybinds()
{
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("Left");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("Right");
	this->keybinds["SELECT"] = this->supportedKeys->at("Enter");
	this->keybinds["CONTROLS"] = this->supportedKeys->at("C");
}

void LostFightState::initButtons()
{
	this->buttons["GIVE_UP"] = new Button(275.f, 472.5f, this->textures["MainMenuButtonIdle"], &this->font, "GIVE UP");
	this->buttons["RETRY"] = new Button(550.f, 472.5f, this->textures["MainMenuButtonIdle"], &this->font, "RETRY");
}

LostFightState::LostFightState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states)
	: State(_window, _supportedKeys, _states)
{
	this->initVariables();
	this->initTextures();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

LostFightState::~LostFightState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void LostFightState::updateInput(const float& _dt)
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
				if (it->first == "GIVE_UP")
				{
					this->states->pop();
					this->states->pop();
					this->states->pop();
				}
				else if (it->first == "RETRY")
				{
					this->states->pop();
					this->states->pop();
					//this->states->push(new FightState(this->window, this->supportedKeys, this->states, this->player));
				}
			}
		}
	}
}

void LostFightState::updateButtons()
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

	if (this->buttons["GIVE_UP"]->getButtonState() == ButtonState::Pressed)
	{
		this->states->pop();
		this->states->pop();
		this->states->pop();
	}

	else if (this->buttons["RETRY"]->getButtonState() == ButtonState::Pressed)
	{
		this->states->pop();
		this->states->pop();
		//this->states->push(new FightState(this->window, this->supportedKeys, this->states, this->player));
	}
}

void LostFightState::update(const float& _dt)
{
	this->updateMousePositions();
	this->updateInput(_dt);
	this->updateButtons();
}

void LostFightState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void LostFightState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);

	this->renderButtons(target);

	target->draw(this->title);

	target->draw(this->message);
}
