#include "FightState.hpp"

void FightState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["ACTION"] = this->supportedKeys->at("E");
	this->keybinds["CONTROLS"] = this->supportedKeys->at("C");
	this->keybinds["Q"] = this->supportedKeys->at("Q");
	this->keybinds["Z"] = this->supportedKeys->at("Z");
}

void FightState::initVariables()
{
	this->keyCode = " ";
	this->vidaMaxima = this->player->getHp();
}	

void FightState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/font.ttf"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_FONT";
	}

	this->message.setFont(this->font);
	this->message.setString(std::to_string(this->player->getHp()));
	this->message.setCharacterSize(24);
	this->message.setFillColor(sf::Color::White);
	this->message.setPosition(20,20);
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
	this->enemies.push_back(new Fighter(704.8f, 524.97f, this->textures["Bat1"], "Enemy1", 500, 50));
}

void FightState::initBackground()
{
	this->background.setTexture(this->textures["FightStage"]);
	this->background.setScale(float(Settings::WINDOW_WIDTH) / float(Settings::VIRTUAL_WIDTH), float(Settings::WINDOW_HEIGHT) / float(Settings::VIRTUAL_HEIGHT));
}

FightState::FightState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Fighter* _p)
	: State(_window, _supportedKeys, _states)
{
	this->initFighters(_p);
	this->initVariables();
	this->initTextures();
	this->initBackground();
	this->initKeybinds();
	this->initFonts();
	
	this->barraVida.setPosition(100.f,100.f);
	this->barraVida.setSize(sf::Vector2f(200.0f, 20.0f));
	this->barraVida.setFillColor(sf::Color::Green);
}

FightState::~FightState()
{
	//delete this->player;
}

void FightState::updateInput(const float& _dt)
{
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("Q")))
	{
		this->keyCode = "Q";
	}
	else
	{
		if (this->keyCode == "Q")
		{
			this->keyCode = " ";
			this->player->setHp(this->player->getHp() - 50.f);
			if (this->player->getHp() < 0)
			{
				this->player->setHp(0);
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("Z")))
	{
		this->keyCode = "Z";
	}
	else
	{
		if (this->keyCode == "Z")
		{
			this->keyCode = " ";
			this->enemies[0]->setHp(this->enemies[0]->getHp() - 50.f);
			if (this->enemies[0]->getHp() < 0)
			{
				this->enemies[0]->setHp(0);
			}
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

	float porcentajeVida = this->player->getHp() / vidaMaxima;
	barraVida.setSize(sf::Vector2f(200.0f * porcentajeVida, 20.0f));

	std::string textString = "Position: X = " + std::to_string(this->player->getSprite()->getPosition().x) + ", Y = " + std::to_string(this->player->getSprite()->getPosition().y);
	text.setString(textString);
	this->message.setString(std::to_string(this->player->getHp()));

	if (this->player->getHp() <= 0)
	{
		this->states->push(new LostFightState(this->window, this->supportedKeys, this->states));
	}

	if (this->enemies[0]->getHp() <= 0)
	{
		this->states->pop();
	}
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
	target->draw(this->barraVida);
	target->draw(this->message);

}