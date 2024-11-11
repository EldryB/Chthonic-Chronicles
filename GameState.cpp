#include "GameState.hpp"

void GameState::initVariables()
{
	this->currentState = CurrentState::Game;
	this->keyCode = " ";
	this->resources = new Resources();
	this->jobs = new Jobs();
	check = " ";
	isBackgroundMoving = false;
	isInLvl1 = (this->player->getStage() == CurrentStage::Lvl1R1) || (this->player->getStage() == CurrentStage::Lvl1R2) || (this->player->getStage() == CurrentStage::Lvl1R3) || 
		(this->player->getStage() == CurrentStage::Lvl1R4) || (this->player->getStage() == CurrentStage::Lvl1R5) || (this->player->getStage() == CurrentStage::Lvl1R6) || 
		(this->player->getStage() == CurrentStage::Lvl1R7) || (this->player->getStage() == CurrentStage::Lvl1R8 || (this->player->getStage() == CurrentStage::Lvl1R9));
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

	if (!this->textures["Lvl1"].loadFromFile("assets/textures/Backgrounds/lvl1.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_MAIN_STAGE_TEXTURE!";
	}

	if (!this->textures["PLAYER_SHEET"].loadFromFile("assets/textures/Player/PLAYER_SHEET.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE!";
	}

	if (!this->textures["ENEMIES_IDLE_SHEET"].loadFromFile("assets/textures/enemy_1/enemiesIdle.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE!";
	}

	if (!this->textures["ITEMS_SHEET"].loadFromFile("assets/textures/Player/weapons.png"))
	{
		throw "ERROR::MENU_STATE::COULD_NOT_LOAD_ITEMS_TEXTURE!";
	}

	if (!this->textures["ARMORS_SHEET"].loadFromFile("assets/textures/Player/armor.png"))
	{
		throw "ERROR::MENU_STATE::COULD_NOT_LOAD_ITEMS_TEXTURE!";
	}

	if (!this->textures["POTION_SHEET"].loadFromFile("assets/textures/Player/potion.png"))
	{
		throw "ERROR::MENU_STATE::COULD_NOT_LOAD_ITEMS_TEXTURE!";
	}
}

void GameState::initFighters()
{
	this->player = new Player(250.f, 370.f, this->textures["PLAYER_SHEET"], "Player", 1000.f, 1000.f, 15, 10);
	this->enemies.push_back(new Skeleton(704.8f, 394.97f, this->textures["ENEMIES_IDLE_SHEET"], "Enemy1", 500.f, 20.f, 7, 7));
	this->enemies.push_back(new Slime(704.8f, 394.97f, this->textures["ENEMIES_IDLE_SHEET"], "Enemy1", 500.f, 20.f, 7, 7));
	this->enemies.push_back(new Rat(704.8f, 394.97f, this->textures["ENEMIES_IDLE_SHEET"], "Enemy1", 500.f, 20.f, 7, 7));
}

void GameState::initItems()
{
	this->items.push_back(new Weapon(this->textures["ITEMS_SHEET"], "Dagger", 50.f, 3, "Amazing dagger!"));
	this->items[0]->setIconRect(sf::IntRect(0, 0, 41, 42));
	this->player->addItem(this->items[0]);

	this->items.push_back(new Weapon(this->textures["ITEMS_SHEET"], "Red Sword", 100.f, -2, "IncREDible sword!"));
	this->items[1]->setIconRect(sf::IntRect(41, 40, 41, 42));
	this->player->addItem(this->items[1]);

	this->items.push_back(new Weapon(this->textures["ITEMS_SHEET"], "Blue Sword", 90.f, -1, "InBaLUEble sword!"));
	this->items[2]->setIconRect(sf::IntRect(82, 40, 41, 42));
	this->player->addItem(this->items[2]);

	this->items.push_back(new Armor(this->textures["ARMORS_SHEET"], "Armor", 70.f, 5, "Heavy armor!"));
	this->items[3]->setIconRect(sf::IntRect(43, 0, 24, 41));
	this->player->addItem(this->items[3]);

	this->items.push_back(new Potion(this->textures["POTION_SHEET"], "Potion", 3, 20.f, "Fresh!"));
	this->items[4]->setIconRect(sf::IntRect(0, 0, 41, 42));
	this->player->addItem(this->items[4]);
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
	this->message.setCharacterSize(18);
	this->message.setFillColor(sf::Color::White);
	this->message.setPosition((Settings::WINDOW_WIDTH/2), (Settings::WINDOW_HEIGHT - this->message.getGlobalBounds().height));

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

void GameState::createCombat()
{

	for(auto enemy: enemies)
	{
		if (enemy->isAlive())
		{
			sf::Vector2f lastPos(this->player->getSprite()->getPosition().x, this->player->getSprite()->getPosition().y);
			this->states->push(new FightState(this->window, this->supportedKeys, this->states, this->player, enemy, lastPos));
			return;
		}
	}
	
}

std::string GameState::getStringStage(CurrentStage _c)
{
	switch (_c)
	{

	case CurrentStage::MainStage: return "MainStage";

	case CurrentStage::Combat:return "Combat";

	case CurrentStage::Lvl1R1:return "Lvl1R1";

	case CurrentStage::Lvl1R2:return "Lvl1R2";

	case CurrentStage::Lvl1R3:return "Lvl1R3";

	case CurrentStage::Lvl1R4:return "Lvl1R4";

	case CurrentStage::Lvl1R5:return "Lvl1R5";

	case CurrentStage::Lvl1R6:return "Lvl1R6";

	case CurrentStage::Lvl1R7:return "Lvl1R7";

	case CurrentStage::Lvl1R8:return "Lvl1R8";

	case CurrentStage::Lvl1R9:return "Lvl1R9";

	default: return " ";
	}
}

GameState::GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states)
	: State(_window, _supportedKeys, _states)
{
	this->initFighters();
	this->initItems();
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

	this->resources = _p->getResources();
	this->jobs = _p->getJobs();
	this->player->setAttributes(_p->getSprite()->getPosition().x, _p->getSprite()->getPosition().y, _p->getName(), _p->getHp(), _p->getAttackPower());
}


GameState::~GameState()
{
	delete this->player;
}


void GameState::updateInput(const float& _dt)
{
	this->timeSinceLastUpdate += _dt;
	//bool isInLadder = ((player->getSprite()->getPosition().y > 307.260651f && player->getSprite()->getPosition().y < 339.698334f) && (player->getSprite()->getPosition().x > 350 && player->getSprite()->getPosition().x < 400));
	//bool isInDoor = ((player->getSprite()->getPosition().y < 330) && (player->getSprite()->getPosition().x > 852 && player->getSprite()->getPosition().x < 895));

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT")))
	{
		this->player->move(-1.f, 0.f, _dt);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT")))
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

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("ACTION")) && this->player->getSprite()->getPosition().x < 180.f)
	{
		this->keyCode = "ACTION2";
	}
	else
	{
		if (this->keyCode == "ACTION2")
		{
			this->keyCode = " ";
			this->player->setPosition(Settings::WINDOW_WIDTH - this->player->getSprite()->getGlobalBounds().width, Settings::WINDOW_HEIGHT/2);
			this->player->pushStage(CurrentStage::Lvl1R1);
			sf::Sprite spr{ this->textures["Lvl1"] };
			spr.setPosition(-2044.86f, -1214.11f);
			this->backgrounds.push(spr);
		}
	}
}

void GameState::updateInput2(const float& _dt)
{
	Dice dice(2147483646 / 1000);
	
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT")) && !isBackgroundMoving)
	{
		this->player->move(-1.f, 0.f, _dt);

		if (dice.getFace() == 50)
		{
			this->createCombat();
		}
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT")) && !isBackgroundMoving)
	{
		this->player->move(1.f, 0.f, _dt);

		if (dice.getFace() == 50)
		{
			this->createCombat();
		}
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_UP")) && !isBackgroundMoving)
	{
		this->player->move(0.f, -1.f, _dt);

		if (dice.getFace() == 50)
		{
			this->createCombat();
		}
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_DOWN")) && !isBackgroundMoving)
	{
		this->player->move(0.f, 1.f, _dt);

		if (dice.getFace() == 50)
		{
			this->createCombat();
		}
	}

	if (this->player->getSprite()->getPosition().x < 500 && this->player->getStage() == CurrentStage::Lvl1R1 && this->enemies[this->enemies.size() - 1]->isAlive())
	{
		sf::Vector2f lastPos(this->player->getSprite()->getPosition().x, this->player->getSprite()->getPosition().y);
		this->states->push(new FightState(this->window, this->supportedKeys, this->states, this->player, this->enemies[this->enemies.size() - 1], lastPos));
	}

	if (this->player->getSprite()->getPosition().x > 800 && sf::Keyboard::isKeyPressed(this->keybinds.at("ACTION")) && this->backgrounds.top().getPosition().x <= -2020)
	{
		this->keyCode = "ACTION2";
	}
	else
	{
		if (this->keyCode == "ACTION2")
		{
			this->keyCode = " ";
			this->player->setPosition(200, 360);
			this->player->pushStage(CurrentStage::MainStage);
			this->backgrounds.pop();
		}
	}
}

void GameState::update(const float& _dt)
{
	isInLvl1 = (this->player->getStage() == CurrentStage::Lvl1R1) || (this->player->getStage() == CurrentStage::Lvl1R2) || (this->player->getStage() == CurrentStage::Lvl1R3) ||
		(this->player->getStage() == CurrentStage::Lvl1R4) || (this->player->getStage() == CurrentStage::Lvl1R5) || (this->player->getStage() == CurrentStage::Lvl1R6) ||
		(this->player->getStage() == CurrentStage::Lvl1R7) || (this->player->getStage() == CurrentStage::Lvl1R8 || (this->player->getStage() == CurrentStage::Lvl1R9));

	this->updateMousePositions();
	if(this->player->getStage() == CurrentStage::MainStage)
	{
		this->updateInput(_dt);
	}
	else if (isInLvl1)
	{
		this->updateInput2(_dt);
	}

	this->player->update(_dt);

	
	std::string textString = "Position: X = " + std::to_string(this->player->getSprite()->getPosition().x) + ", Y = " + std::to_string(this->player->getSprite()->getPosition().y);
	text.setString(textString);
	
	if(isInLvl1)
	{
		std::string textString = "Position: X = " + std::to_string(this->backgrounds.top().getPosition().x) + ", Y = " + std::to_string(this->backgrounds.top().getPosition().y);
		message.setString(textString);;
	}

	updateMap(_dt);
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
}

void GameState::updateMap(const float& dtt)
{
	float _dt = dtt * 3;


	if (this->player->getStage() == CurrentStage::Lvl1R1 && this->player->getSprite()->getPosition().x < 50 && sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT"))
		&& !isBackgroundMoving)
	{
		check = "L1R1R";
	}
	if (check == "L1R1R")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(125 * _dt, 0);
		this->player->moveS(120.f, 0.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R2);
		if (this->player->getSprite()->getPosition().x > 940)
		{
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::Lvl1R2 && this->player->getSprite()->getPosition().x > 940 && sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT"))
		&& !isBackgroundMoving)
	{
		check = "L1R2L";
	}
	if (check == "L1R2L")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(-125 * _dt, 0);
		this->player->moveS(-120.f, 0.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R1);
		if (this->player->getSprite()->getPosition().x < 50)
		{
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::Lvl1R2 && this->player->getSprite()->getPosition().y < 10 && sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_UP"))
		&& !isBackgroundMoving)
	{
		check = "L1R2U";
	}
	if (check == "L1R2U")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(0, 150 * _dt);
		this->player->moveS(0, 120.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R3);
		if (this->player->getSprite()->getPosition().y > Settings::VIRTUAL_HEIGHT - this->player->getSprite()->getGlobalBounds().height)
		{
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::Lvl1R3 &&
		this->player->getSprite()->getPosition().y > Settings::VIRTUAL_HEIGHT - this->player->getSprite()->getGlobalBounds().height
		&& sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_DOWN")) && !isBackgroundMoving)
	{
		check = "L1R3D";
	}
	if (check == "L1R3D")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(0, -150 * _dt);
		this->player->moveS(0, -120.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R2);
		if (this->player->getSprite()->getPosition().y < 10)
		{
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::Lvl1R3 && this->player->getSprite()->getPosition().x > 940 && sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT"))
		&& !isBackgroundMoving)
	{
		check = "L1R3R";
	}
	if (check == "L1R3R")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(-125 * _dt, 0);
		this->player->moveS(-120.f, 0, _dt);
		this->player->pushStage(CurrentStage::Lvl1R4);
		if (this->player->getSprite()->getPosition().x < 50)
		{
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::Lvl1R4 && this->player->getSprite()->getPosition().x < 50 && sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT"))&& 
		!isBackgroundMoving)
	{
		check = "L1R4L";
	}
	if (check == "L1R4L")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(125 * _dt, 0);
		this->player->moveS(120.f, 0, _dt);
		this->player->pushStage(CurrentStage::Lvl1R3);
		if (this->player->getSprite()->getPosition().x > 940)
		{
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::Lvl1R3 && 
		(this->player->getSprite()->getPosition().x > 187 && this->player->getSprite()->getPosition().x < 328) && this->player->getSprite()->getPosition().y < 145 &&
		sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_UP")) && !isBackgroundMoving)
	{
		check = "L1R3U";
	}
	if (check == "L1R3U")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(0, 250 * _dt);
		this->player->moveS(0, 120.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R5);
		if (this->player->getSprite()->getPosition().y > Settings::VIRTUAL_HEIGHT - this->player->getSprite()->getGlobalBounds().height)
		{
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::Lvl1R5 &&
		(this->player->getSprite()->getPosition().x > 174 && this->player->getSprite()->getPosition().x < 328) && 
		this->player->getSprite()->getPosition().y > Settings::VIRTUAL_HEIGHT - this->player->getSprite()->getGlobalBounds().height &&
		sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_DOWN")) && !isBackgroundMoving)
	{
		check = "L1R5D";
	}
	if (check == "L1R5D")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(0, -250 * _dt);
		this->player->moveS(0, -120.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R3);
		if (this->player->getSprite()->getPosition().y < 145)
		{
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::Lvl1R5 && this->player->getSprite()->getPosition().x > 940 && sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT"))
		&& !isBackgroundMoving)
	{
		check = "L1R5R";
	}
	if (check == "L1R5R")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(-125 * _dt, 0);
		this->player->moveS(-120.f, 0, _dt);
		this->player->pushStage(CurrentStage::Lvl1R6);
		if (this->player->getSprite()->getPosition().x < 50)
		{
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::Lvl1R6 && this->player->getSprite()->getPosition().x < 50 && sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT")) &&
		!isBackgroundMoving)
	{
		check = "L1R6L";
	}
	if (check == "L1R6L")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(125 * _dt, 0);
		this->player->moveS(120.f, 0, _dt);
		this->player->pushStage(CurrentStage::Lvl1R5);
		if (this->player->getSprite()->getPosition().x > 940)
		{
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::Lvl1R5 && this->player->getSprite()->getPosition().x < 50 && sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT")) &&
		!isBackgroundMoving)
	{
		check = "L1R5L";
	}
	if (check == "L1R5L")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(145 * _dt, 0);
		this->player->moveS(120.f, 0, _dt);
		this->player->pushStage(CurrentStage::Lvl1R7);
		if (this->player->getSprite()->getPosition().x > 940)
		{
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::Lvl1R7 && this->player->getSprite()->getPosition().x > 940 && sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT"))
		&& !isBackgroundMoving)
	{
		check = "L1R7R";
	}
	if (check == "L1R7R")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(-145 * _dt, 0);
		this->player->moveS(-120.f, 0, _dt);
		this->player->pushStage(CurrentStage::Lvl1R5);
		if (this->player->getSprite()->getPosition().x < 50)
		{
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::Lvl1R7 &&
		this->player->getSprite()->getPosition().y > Settings::VIRTUAL_HEIGHT + 5
		&& sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_DOWN")) && !isBackgroundMoving)
	{
		check = "L1R7D";
	}
	if (check == "L1R7D")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(0, -150 * _dt);
		this->player->moveS(0, -120.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R8);
		if (this->player->getSprite()->getPosition().y < 10)
		{
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::Lvl1R8 && this->player->getSprite()->getPosition().y < 10 && sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_UP"))
		&& !isBackgroundMoving)
	{
		check = "L1R8U";
	}
	if (check == "L1R8U")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(0, 150 * _dt);
		this->player->moveS(0, 120.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R7);
		if (this->player->getSprite()->getPosition().y > Settings::VIRTUAL_HEIGHT + 5)
		{
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::Lvl1R8 &&
		this->player->getSprite()->getPosition().y > Settings::VIRTUAL_HEIGHT + 5
		&& sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_DOWN")) && !isBackgroundMoving)
	{
		check = "L1R8D";
	}
	if (check == "L1R8D")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(0, -170 * _dt);
		this->player->moveS(0, -120.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R9);
		if (this->player->getSprite()->getPosition().y < 10)
		{
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::Lvl1R9 && this->player->getSprite()->getPosition().y < 10 && sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_UP"))
		&& !isBackgroundMoving)
	{
		check = "L1R9U";
	}
	if (check == "L1R9U")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(0, 170 * _dt);
		this->player->moveS(0, 120.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R8);
		if (this->player->getSprite()->getPosition().y > Settings::VIRTUAL_HEIGHT + 5)
		{
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

}