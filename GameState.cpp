#include "GameState.hpp"

void GameState::initVariables()
{

}

void GameState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
}

void GameState::initTextures()
{
	if (!this->textures["MainStage"].loadFromFile("assets/textures/Backgrounds/mainStage.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_MAIN_STAGE_TEXTURE!";
	}

	if (!this->textures["PLAYER_SHEET"].loadFromFile("assets/textures/Player/PLAYER_SHEET.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE!";
	}
}

void GameState::initFighters()
{
	this->player = new Fighter(250.f, 370.f, this->textures["PLAYER_SHEET"], "Player");
}

void GameState::initBackground()
{
	this->background.setTexture(this->textures["MainStage"]);
	this->background.setScale(float(Settings::WINDOW_WIDTH) / float(Settings::VIRTUAL_WIDTH), float(Settings::WINDOW_HEIGHT) / float(Settings::VIRTUAL_HEIGHT));
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/font.ttf"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_FONT";
	}
}

GameState::GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states)
	: State(_window, _supportedKeys, _states)
{
	this->initVariables();
	this->initTextures();
	this->initFighters();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();

	this->text.setFont(this->font);
	this->text.setCharacterSize(20);
	this->text.setFillColor(sf::Color::White);
	text.setPosition(30, 30);
}

GameState::GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Fighter* _p)
	: State(_window, _supportedKeys, _states)
{
	this->initVariables();
	this->initTextures();
	this->initFighters();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();

	this->text.setFont(this->font);
	this->text.setCharacterSize(20);
	this->text.setFillColor(sf::Color::White);
	text.setPosition(30, 30);
	this->player->setAttributes(_p->getSprite()->getPosition().x, _p->getSprite()->getPosition().y, _p->getName());
	this->player->setPosition(_p->getSprite()->getPosition().x, _p->getSprite()->getPosition().y);
}


GameState::~GameState()
{
	delete this->player;
}


void GameState::updateInput(const float& _dt)
{
	timeSinceLastUpdate += _dt;
	bool isInLadder = ((player->getSprite()->getPosition().y > 307.260651f && player->getSprite()->getPosition().y < 339.698334f) && (player->getSprite()->getPosition().x > 350 && player->getSprite()->getPosition().x < 400));


	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT")) && !(isInLadder))
	{
		this->player->move(-1.f, 0.f, _dt);
	}
	else if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT")) && !(isInLadder))
	{
		this->player->move(1.f, 0.f, _dt);
	}
	else if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_UP")))
	{
		this->player->move(0.f, -1.f, _dt);
	}
	else if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_DOWN")))
	{
		this->player->move(0.f, 1.f, _dt);
	}

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("CLOSE")))
	{
		this->states->push(new MenuState(this->window, this->supportedKeys, this->states, this->player));
	}
}

void GameState::update(const float& _dt)
{
	this->updateMousePositions();
	this->updateInput(_dt);

	this->player->update(_dt);
	std::string textString = "Position: X = " + std::to_string(this->player->getSprite()->getPosition().x) + ", Y = " + std::to_string(this->player->getSprite()->getPosition().y);
	text.setString(textString);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->player->render(target);


	target->draw(this->text);
}
