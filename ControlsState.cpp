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

	this->texts["Title"].setFont(this->font);
	this->texts["Title"].setString("CONTROLS");
	this->texts["Title"].setCharacterSize(42);
	this->texts["Title"].setFillColor(sf::Color(206, 185, 141));
	this->texts["Title"].setPosition((Settings::WINDOW_WIDTH - this->texts["Title"].getGlobalBounds().width) / 2, 80);

	this->texts["ReturnMessage"].setFont(this->font);
	this->texts["ReturnMessage"].setString("Press 'C' to return");
	this->texts["ReturnMessage"].setCharacterSize(24);
	this->texts["ReturnMessage"].setFillColor(sf::Color::White);
	this->texts["ReturnMessage"].setPosition(0.f, (Settings::WINDOW_HEIGHT - this->texts["ReturnMessage"].getGlobalBounds().height));
}

void ControlsState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("C");
}

void ControlsState::initControlList()
{
	this->controls.clear();

	switch (this->states->top()->getCurrentState())
	{
	case CurrentState::MainMenu:
		this->texts["MenuControl1"] = this->createControlText("Left arrow: Move to the left", 300, 200);
		this->texts["MenuControl2"] = this->createControlText("Right arrow: Move to the right", 300, 300);
		this->texts["MenuControl3"] = this->createControlText("Enter: Select option", 300, 400);
		break;

	case CurrentState::Game:
		this->texts["MenuControl1"] = this->createControlText("A: Move to the left", 300, 200);
		this->texts["MenuControl2"] = this->createControlText("D: Move to the right", 300, 230);
		this->texts["MenuControl3"] = this->createControlText("W : Move forward", 300, 260);
		this->texts["MenuControl4"] = this->createControlText("S : Move backward", 300, 290);
		this->texts["MenuControl5"] = this->createControlText("Escape: Pause", 300, 320);
		this->texts["MenuControl6"] = this->createControlText("Q: Jobs and Resources", 300, 350);
		this->texts["MenuControl7"] = this->createControlText("E : Change stage", 300, 380);
		break;

	case CurrentState::PauseMenu:
		this->texts["MenuControl1"] = this->createControlText("Escape: Go back to the game", 300, 200);
		this->texts["MenuControl2"] = this->createControlText("Left arrow: Move to the left", 300, 250);
		this->texts["MenuControl3"] = this->createControlText("Right arrow: Move to the right", 300, 300);
		this->texts["MenuControl4"] = this->createControlText("Enter: Select option", 300, 350);
		break;

	case CurrentState::JobMenu:
		this->texts["MenuControl1"] = this->createControlText("Q: Go back to the game", 300, 200);
		this->texts["MenuControl2"] = this->createControlText("Left arrow: Move to the left", 300, 250);
		this->texts["MenuControl3"] = this->createControlText("Right arrow: Move to the right", 300, 300);
		this->texts["MenuControl4"] = this->createControlText("Enter: Select option", 300, 350);
		break;

	case CurrentState::Fight:
		break;

	case CurrentState::LostFight:
		this->texts["MenuControl1"] = this->createControlText("Left arrow: Move to the left", 300, 200);
		this->texts["MenuControl2"] = this->createControlText("Right arrow: Move to the right", 300, 300);
		this->texts["MenuControl3"] = this->createControlText("Enter: Select option", 300, 400);
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

	for (auto text : this->texts)
	{
		target->draw(text.second);
	}
}