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

	this->message.setFont(this->font);
	this->message.setString("Press 'C' to return");
	this->message.setCharacterSize(24);
	this->message.setFillColor(sf::Color::White);
	this->message.setPosition(0.f, (Settings::WINDOW_HEIGHT - this->message.getGlobalBounds().height));
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
		this->controls.push_back(this->createControlText("Left arrow: Move to the left", 300, 200));
		this->controls.push_back(this->createControlText("Right arrow: Move to the right", 300, 300));
		this->controls.push_back(this->createControlText("Enter: Select option", 300, 400));
		break;

	case CurrentState::Game:
		this->controls.push_back(this->createControlText("A: Move to the left", 300, 200));
		this->controls.push_back(this->createControlText("D: Move to the right", 300, 230));
		this->controls.push_back(this->createControlText("W : Move forward", 300, 260));
		this->controls.push_back(this->createControlText("S : Move backward", 300, 290));
		this->controls.push_back(this->createControlText("Escape: Pause", 300, 320));
		this->controls.push_back(this->createControlText("Q: Jobs and Resources", 300, 350));
		this->controls.push_back(this->createControlText("E : Fight", 300, 380));
		break;

	case CurrentState::PauseMenu:
		this->controls.push_back(this->createControlText("Escape: Go back to the game", 300, 200));
		this->controls.push_back(this->createControlText("Left arrow: Move to the left", 300, 250));
		this->controls.push_back(this->createControlText("Right arrow: Move to the right", 300, 300));
		this->controls.push_back(this->createControlText("Enter: Select option", 300, 350));
		break;

	case CurrentState::JobMenu:
		this->controls.push_back(this->createControlText("Q: Go back to the game", 300, 200));
		this->controls.push_back(this->createControlText("Left arrow: Move to the left", 300, 250));
		this->controls.push_back(this->createControlText("Right arrow: Move to the right", 300, 300));
		this->controls.push_back(this->createControlText("Enter arrow: Select option", 300, 350));
		break;

	case CurrentState::Fight:
		break;

	case CurrentState::LostFight:
		this->controls.push_back(this->createControlText("Left arrow: Move to the left", 100, 100));
		this->controls.push_back(this->createControlText("Right arrow: Move to the right", 200, 130));
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

	target->draw(this->message);

	for (const auto& control : controls)
	{
		target->draw(control);
	}
}