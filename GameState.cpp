#include "GameState.hpp"

void GameState::initVariables()
{
	this->currentState = CurrentState::Game;
	this->keyCode = " ";
	this->resources = new Resources();
	this->jobs = new Jobs();
	this->dt = 0;
}

void GameState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
	this->keybinds["ACTION"] = this->supportedKeys->at("E");
	this->keybinds["Q"] = this->supportedKeys->at("Q");
	this->keybinds["CONTROLS"] = this->supportedKeys->at("C");
	this->keybinds["INVENTORY"] = this->supportedKeys->at("I");
}

void GameState::initTextures()
{
	if (!this->textures["MainStage"].loadFromFile("assets/textures/Backgrounds/mainStage.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_MAIN_STAGE_TEXTURE!";
	}

	if (!this->textures["Stage2"].loadFromFile("assets/textures/Backgrounds/stage2.png"))
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
	this->player = new Player(250.f, 370.f, this->textures["PLAYER_SHEET"], "Player", 1000.f, 100.f, 10, 8);
}

void GameState::initBackground()
{
	sf::Sprite back;
	back.setTexture(this->textures["MainStage"]);
	back.setScale(float(Settings::WINDOW_WIDTH) / float(Settings::VIRTUAL_WIDTH), float(Settings::WINDOW_HEIGHT) / float(Settings::VIRTUAL_HEIGHT));
	this->backgrounds.push(back);

}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/font.ttf"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_FONT";
	}

	this->message.setFont(this->font);
	this->message.setString("Press 'C' to show controls");
	this->message.setCharacterSize(24);
	this->message.setFillColor(sf::Color::White);
	this->message.setPosition((Settings::WINDOW_WIDTH - this->message.getGlobalBounds().width), (Settings::WINDOW_HEIGHT - this->message.getGlobalBounds().height));

	this->message2.setFont(this->font);
	this->message2.setString("Press E to enter");
	this->message2.setCharacterSize(24);
	this->message2.setFillColor(sf::Color::White);
	this->message2.setPosition(600,250);

	this->text.setFont(this->font);
	this->text.setCharacterSize(20);
	this->text.setFillColor(sf::Color(206, 185, 141));
	text.setPosition(30, 30);

	this->stageText.setFont(this->font);
	this->stageText.setCharacterSize(24);
	this->stageText.setFillColor(sf::Color::White);
	this->stageText.setPosition(700, 30);
}

std::string GameState::getStringStage(CurrentStage _c)
{
	switch (_c)
	{

	case CurrentStage::MainStage: return "MainStage";

	case CurrentStage::Combat:return "Combat";

	case CurrentStage::Stage2:return "Stage2";

	default: return " ";
	}
}

GameState::GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states)
	: State(_window, _supportedKeys, _states)
{
	this->initFighters();
	this->initVariables();
	this->initTextures();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();

	this->player->pushStage(CurrentStage::MainStage);
}

GameState::GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Player* _p)
	: State(_window, _supportedKeys, _states)
{
	this->initFighters();
	this->initVariables();
	this->initTextures();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();

	this->player->setAttributes(_p->getSprite()->getPosition().x, _p->getSprite()->getPosition().y, _p->getName(), _p->getHp(), _p->getDamage());
}


GameState::~GameState()
{
	delete this->player;
}


void GameState::updateInput(const float& _dt)
{
	this->timeSinceLastUpdate += _dt;
	bool isInLadder = ((player->getSprite()->getPosition().y > 307.260651f && player->getSprite()->getPosition().y < 339.698334f) && (player->getSprite()->getPosition().x > 350 && player->getSprite()->getPosition().x < 400));
	bool isInDoor = ((player->getSprite()->getPosition().y < 330) && (player->getSprite()->getPosition().x > 852 && player->getSprite()->getPosition().x < 895));

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT")) && !(isInLadder))
	{
		this->player->move(-1.f, 0.f, _dt);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT")) && !(isInLadder))
	{
		this->player->move(1.f, 0.f, _dt);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_UP")))
	{
		this->player->move(0.f, -1.f, _dt);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_DOWN")))
	{
		this->player->move(0.f, 1.f, _dt);
	}


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

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("CLOSE")))
	{
		this->keyCode = "CLOSE";
	}
	else
	{
		if (this->keyCode == "CLOSE")
		{
			this->keyCode = " ";
			this->states->push(new MenuState(this->window, this->supportedKeys, this->states, this->player));
		}
	}

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("Q")))
	{
		this->keyCode = "Q";
	}
	else
	{
		if (this->keyCode == "Q")
		{
			this->keyCode = " ";
			this->states->push(new JobMenuState(this->window, this->supportedKeys, this->states, *jobs, *resources, this->player));
		}
	}

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("INVENTORY")))
	{
		this->keyCode = "INVENTORY";
	}
	else
	{
		if (this->keyCode == "INVENTORY")
		{
			this->keyCode = " ";
			this->states->push(new InventoryState(this->window, this->supportedKeys, this->states, this->player));
		}
	}

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("ACTION")) && this->player->getSprite()->getPosition().x > 771.f)
	{
		this->keyCode = "ACTION2";
	}
	else
	{
		if (this->keyCode == "ACTION2")
		{
			this->keyCode = " ";
			this->player->setPosition(200,300);
			this->player->pushStage(CurrentStage::Stage2);
			sf::Sprite spr{ this->textures["Stage2"] };
			this->backgrounds.push(spr);
		}
	}
}

void GameState::updateInput2(const float& _dt)
{
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT")) )
	{
		this->player->move(-1.f, 0.f, _dt);
		if(this->backgrounds.top().getPosition().x <= 0)
		{
			this->backgrounds.top().move(80 * _dt, 0);
		}
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT")) )
	{
		this->player->move(1.f, 0.f, _dt);
		if(true)
		{
			this->backgrounds.top().move(-80 * _dt, 0);
		}
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_UP")))
	{
		this->player->move(0.f, -1.f, _dt);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_DOWN")))
	{
		this->player->move(0.f, 1.f, _dt);
	}

	if (this->player->getSprite()->getPosition().x < 50 && sf::Keyboard::isKeyPressed(this->keybinds.at("ACTION")) && this->backgrounds.top().getPosition().x >= -10)
	{
		this->keyCode = "ACTION2";
	}
	else
	{
		if (this->keyCode == "ACTION2")
		{
			this->keyCode = " ";
			this->player->setPosition(780, 360);
			this->player->popStage();
			this->backgrounds.pop();
		}
	}

	if (this->player->getSprite()->getPosition().x > 400 && this->player->getStage() == CurrentStage::Stage2)
	{
		sf::Vector2f lastPos(this->player->getSprite()->getPosition().x, this->player->getSprite()->getPosition().y);
		this->states->push(new FightState(this->window, this->supportedKeys, this->states, this->player, lastPos));
	}

	if (this->player->getSprite()->getPosition().x > 865)
	{	
		
	}
}

void GameState::update(const float& _dt)
{
	this->updateMousePositions();
	if(this->player->getStage() == CurrentStage::MainStage)
	{
		this->updateInput(_dt);
	}
	else if (this->player->getStage() == CurrentStage::Stage2)
	{
		this->updateInput2(_dt);
	}

	this->player->update(_dt);
	std::string textString = "Position: X = " + std::to_string(this->player->getSprite()->getPosition().x) + ", Y = " + std::to_string(this->player->getSprite()->getPosition().y);
	text.setString(textString);
	this->stageText.setString(this->getStringStage(this->player->getStage()));
}

void GameState::render(sf::RenderTarget* target)
{
	bool isInDoor = ((player->getSprite()->getPosition().y < 330) && (player->getSprite()->getPosition().x > 852 && player->getSprite()->getPosition().x < 895));

	if (!target)
	{
		target = this->window;
	}

	target->draw(this->backgrounds.top());
	
	this->player->render(target);
	
	target->draw(this->text);

	target->draw(this->message);

	target->draw(this->stageText);

	if ((isInDoor || this->player->getSprite()->getPosition().x > 771.f) && this->player->getStage() == CurrentStage::MainStage)
	{
		target->draw(this->message2);
	}

	if (this->player->getStage() == CurrentStage::Stage2)
	{
		//renderizar minimapa
	}
}
