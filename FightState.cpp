#include "FightState.hpp"

void FightState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
	this->keybinds["ACTION"] = this->supportedKeys->at("E");
}

void FightState::initVariables()
{
	this->keyCode = " ";
}	

void FightState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/font.ttf"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_FONT";
	}
}

void FightState::initTextures()
{
	if (!this->textures["FightStage"].loadFromFile("assets/textures/Backgrounds/cave.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_MAIN_STAGE_TEXTURE!";
	}

	if (!this->textures["player"].loadFromFile("assets/textures/Player/frontSpark.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE!";
	}

	if (!this->textures["Bat1"].loadFromFile("assets/textures/enemy_1/at1.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE!";
	}
}

void FightState::initFighters(Fighter* _p)
{
	this->player = _p;
	this->player->setLookingDirection(LookingDirection::Right);
	this->player->setPosition(304.8f, 524.97f);
	this->enemies.push_back(new Fighter(200.f, 200.f, this->textures["Bat1"], "Enemy1", 500, 50));
}

void FightState::initBackground()
{
	this->background.setTexture(this->textures["FightStage"]);
	this->background.setScale(float(Settings::WINDOW_WIDTH) / float(Settings::VIRTUAL_WIDTH), float(Settings::WINDOW_HEIGHT) / float(Settings::VIRTUAL_HEIGHT));
}

FightState::FightState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Fighter* _p)
	: State(_window, _supportedKeys, _states)
{
	this->initVariables();
	this->initTextures();
	this->initFighters(_p);
	this->initBackground();
	this->initKeybinds();
	this->initFonts();
	
	this->player->setStage(CurrentStage::Combat);
}

FightState::~FightState()
{
	//delete this->player;
}

void FightState::updateInput(const float& _dt)
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
			this->player->setPosition(870.77f, 323.92f);
			this->states->push(new LostFightState(this->window, this->supportedKeys, this->states));
		}
	}

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("ACTION")))
	{
		this->keyCode = "ACTION";
	}
	else
	{
		if (this->keyCode == "ACTION")
		{
			this->keyCode = " ";
			this->player->setPosition(870.77f, 323.92f);
			this->states->pop();
			this->player->setStage(CurrentStage::MainStage);
		}
	}
}

void FightState::update(const float& _dt)
{
	this->updateMousePositions();
	this->updateInput(_dt);
	this->player->update(_dt);
	for (auto item: this->enemies)
	{
		item->update(_dt);
	}

	std::string textString = "Position: X = " + std::to_string(this->player->getSprite()->getPosition().x) + ", Y = " + std::to_string(this->player->getSprite()->getPosition().y);
	text.setString(textString);
}

void FightState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->player->render(target);

	for (auto item: this->enemies)
	{
		item->render(target);
	}

	target->draw(this->text);

}