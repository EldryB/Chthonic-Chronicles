#include "ControlsState.hpp"

void ControlsState::initVariables()
{
	this->keyCode = " ";
}

void ControlsState::initTextures()
{
	if (!this->textures["Background"].loadFromFile("assets/textures/Backgrounds/options.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_BACKGROUND_TEXTURE!";
	}
}

void ControlsState::initBackground()
{
	this->background.setTexture(this->textures["Background"]);
}

void ControlsState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/font.ttf"))
	{
		throw "ERROR::MENU_STATE::COULD_NOT_LOAD_FONT";
	}

	this->title.setFont(this->font);
	this->title.setString("CONTROLS");
	this->title.setCharacterSize(42);
	this->title.setFillColor(sf::Color(206, 185, 141));
	this->title.setPosition((Settings::WINDOW_WIDTH - this->title.getGlobalBounds().width) / 2, 80);
}

void ControlsState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("C");
}

void ControlsState::initControlList()
{
	this->controls.clear();
	/*this->menuControls.clear();
	this->gameControls.clear();*/

	switch (this->states->top()->getCurrentState())
	{
	case CurrentState::MainMenu:
		this->controls.push_back(this->createControlText("Left: Move to the left", 300, 200));
		this->controls.push_back(this->createControlText("Right: Move to the right", 300, 300));
		this->controls.push_back(this->createControlText("Enter: Select option", 300, 400));
		break;
	case CurrentState::Game:
		this->controls.push_back(this->createControlText("A: Move to the left", 300, 200));
		this->controls.push_back(this->createControlText("D: Move to the right", 300, 230));
		this->controls.push_back(this->createControlText("W : Move forward", 300, 360));
		this->controls.push_back(this->createControlText("S : Move backward", 300, 390));
		this->controls.push_back(this->createControlText("Escape: Pause", 300, 420));
		this->controls.push_back(this->createControlText("Q: Jobs and Resources", 300, 450));
		this->controls.push_back(this->createControlText("E : Fight", 300, 480));
		break;
	case CurrentState::PauseMenu:
		this->controls.push_back(this->createControlText("Escape: Go back to the game", 300, 300));
		this->controls.push_back(this->createControlText("Left: Move to the left", 300, 350));
		this->controls.push_back(this->createControlText("Right: Move to the right", 300, 400));
		this->controls.push_back(this->createControlText("Enter: Select option", 300, 450));
		break;
	case CurrentState::JobMenu:
		this->controls.push_back(this->createControlText("Q: Go back to the game", 300, 300));
		this->controls.push_back(this->createControlText("Left: Move to the left", 300, 350));
		this->controls.push_back(this->createControlText("Right: Move to the right", 300, 400));
		this->controls.push_back(this->createControlText("Enter: Select option", 300, 450));
		break;
	case CurrentState::Fight:
		break;
	case CurrentState::LostFight:
		this->controls.push_back(this->createControlText("Left: Move to the left", 100, 100));
		this->controls.push_back(this->createControlText("Right: Move to the right", 200, 130));
		this->controls.push_back(this->createControlText("Enter: Select option", 200, 160));
		break;
	default:
		break;
	}
}


ControlsState::ControlsState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states)
	: State(_window, _supportedKeys, _states)
{
	this->initVariables();
	this->initTextures();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initControlList();
}

ControlsState::~ControlsState()
{
	
}

sf::Text ControlsState::createControlText(const std::string& text, float _x, float _y)
{
	sf::Text controlText;
	controlText.setFont(this->font);
	controlText.setString(text);
	controlText.setCharacterSize(24);
	controlText.setFillColor(sf::Color(206, 185, 141));
	controlText.setPosition(_x, _y);
	return controlText;
}

void ControlsState::updateInput(const float& _dt)
{
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

}

void ControlsState::update(const float& _dt)
{
	this->updateMousePositions();
	this->updateInput(_dt);
}

void ControlsState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);

	target->draw(this->title);

	for (const auto& control : controls)
	{
		target->draw(control);
	}
}