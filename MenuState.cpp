#include "MenuState.hpp"

void MenuState::initVariables()
{

}

void MenuState::initTextures()
{
	if (!this->textures["Background"].loadFromFile("assets/textures/pause.png"))
	{
		throw "ERROR::MENU_STATE::COULD_NOT_LOAD_BACKGROUND_TEXTURE!";
	}

	if (!this->textures["MenuButtonIdle"].loadFromFile("assets/textures/MenuButtonIdle.png"))
	{
		throw "ERROR::MENU_STATE::COULD_NOT_LOAD_MENU_BUTTON_IDLE_TEXTURE!";
	}

	if (!this->textures["MenuButtonHover"].loadFromFile("assets/textures/MenuButtonHover.png"))
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
}

void MenuState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("Up");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("Down");
	this->keybinds["SELECT"] = this->supportedKeys->at("Enter");
}

void MenuState::initButtons()
{
	this->buttons["BACK_TO_THE_GAME"] = new Button(10.f, 512.5f, this->textures["MenuButtonIdle"], &this->font, "<- Back to\nthe game");
	this->buttons["NO_SAVE_AND_QUIT"] = new Button(250.f, 512.5f, this->textures["MenuButtonIdle"], &this->font, "No save and\nquit");
	this->buttons["SAVE_AND_QUIT"] = new Button(490.f, 512.5f, this->textures["MenuButtonIdle"], &this->font, "Save and\nquit");
}

MenuState::MenuState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states)
	: State(_window, _supportedKeys, _states)
{
	this->initVariables();
	this->initTextures();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
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
	
}

void MenuState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);

		if (it.second->isIdle())
		{
			it.second->setTexture(this->textures["MenuButtonIdle"]);
			it.second->setTextFillColor(sf::Color::White);
		}

		if (it.second->isHover())
		{
			it.second->setTexture(this->textures["MenuButtonHover"]);
			it.second->setTextFillColor(sf::Color(150, 104, 28));
		}
	}

	if (this->buttons["BACK_TO_THE_GAME"]->isPressed())
	{
		this->states->pop();
	}
	if (this->buttons["NO_SAVE_AND_QUIT"]->isPressed())
	{
		this->states->pop();
		this->states->pop();
	}
	if (this->buttons["SAVE_AND_QUIT"]->isPressed())
	{
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
}
