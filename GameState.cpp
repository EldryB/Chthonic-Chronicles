#include "GameState.hpp"

void GameState::initVariables()
{
	this->currentState = CurrentState::Game;
	this->keyCode = " ";
	this->resources = new Resources();
	this->jobs = new Jobs();
	check = " ";
	isBackgroundMoving = false;
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

	if (!this->textures["House1"].loadFromFile("assets/textures/Backgrounds/casa1.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_MAIN_STAGE_TEXTURE!";
	}

	if (!this->textures["House2"].loadFromFile("assets/textures/Backgrounds/casa2.png"))
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

	this->player = new Player(250.f, 370.f, this->textures["PLAYER_SHEET"], "Player", 15.f, 6.f, 16, 5);
	this->enemies.push_back(new Skeleton(704.8f, 394.97f, this->textures["ENEMIES_IDLE_SHEET"], "Skeleton", 20.f, 6.f, 13, 2));
	this->enemies.push_back(new Slime(704.8f, 394.97f, this->textures["ENEMIES_IDLE_SHEET"], "Slime", 13.f, 4.f, 12, 4));
	this->enemies.push_back(new Rat(704.8f, 394.97f, this->textures["ENEMIES_IDLE_SHEET"], "Rat", 10.f, 3.f, 7, 6));
	this->enemies.push_back(new Bat(704.8f, 394.97f, this->textures["ENEMIES_IDLE_SHEET"], "Bat", 18.f, 2.f, 14, 7));
	this->enemies.push_back(new Skeleton(704.8f, 394.97f, this->textures["ENEMIES_IDLE_SHEET"], "Skeleton", 20.f, 6.f, 13, 2));
	this->enemies.push_back(new Slime(704.8f, 394.97f, this->textures["ENEMIES_IDLE_SHEET"], "Slime", 13.f, 4.f, 12, 4));
	this->enemies.push_back(new Rat(704.8f, 394.97f, this->textures["ENEMIES_IDLE_SHEET"], "Rat", 10.f, 3.f, 7, 6));
	this->enemies.push_back(new Bat(704.8f, 394.97f, this->textures["ENEMIES_IDLE_SHEET"], "Bat", 18.f, 2.f, 14, 7));
}

void GameState::initItems()
{
	//NO CAMBIAR EL NOMBRE A LOS ITEMS
	this->items.push_back(new Weapon(this->textures["ITEMS_SHEET"], "Dagger", 4.f, 3, "Amazing dagger!", 10));
	this->items[0]->setIconRect(sf::IntRect(0, 0, 41, 42));
	this->player->addItem(this->items[0]);

	this->items.push_back(new Weapon(this->textures["ITEMS_SHEET"], "Red Sword", 6.f, -2, "IncREDible sword!", 10));
	this->items[1]->setIconRect(sf::IntRect(41, 40, 41, 42));
	this->player->addItem(this->items[1]);

	this->items.push_back(new Weapon(this->textures["ITEMS_SHEET"], "Blue Sword", 8.f, 0, "InBaLUEble sword!", 10));
	this->items[2]->setIconRect(sf::IntRect(82, 40, 41, 42));
	this->player->addItem(this->items[2]);

	this->items.push_back(new Potion(this->textures["POTION_SHEET"], "Potion", 3, 20.f, "Fresh!" , 10));
	this->items[3]->setIconRect(sf::IntRect(0, 0, 41, 42));
	this->player->addItem(this->items[3]);

	this->items.push_back(new Armor(this->textures["ARMORS_SHEET"], "Rusty Armor", 5.f, 5, "Heavy armor!", 10));
	this->items[4]->setIconRect(sf::IntRect(43, 0, 24, 41));
	this->player->addItem(this->items[4]);

	this->items.push_back(new Armor(this->textures["ARMORS_SHEET"], "Thunder Armor", 8.f, 5, "THUNDER!", 10));
	this->items[5]->setIconRect(sf::IntRect(265, 0, 26, 41));
	this->player->addItem(this->items[5]);

	this->items.push_back(new Potion(this->textures["POTION_SHEET"], "Potion", 1, 20.f, "Fresh!", 10));
	this->items[6]->setIconRect(sf::IntRect(0, 0, 41, 42));

	this->items.push_back(new Weapon(this->textures["ITEMS_SHEET"], "Red Sword", 6.f, -2, "IncREDible sword!", 10));
	this->items[7]->setIconRect(sf::IntRect(41, 40, 41, 42));
	this->player->addItem(this->items[7]);
	
	for (auto enemy : this->enemies)
	{
		enemy->addItem(this->items[0]);
		enemy->addItem(this->items[6]);
	}
}


void GameState::initBackground()
{
	sf::Sprite back;
	back.setTexture(this->textures["MainStage"]);
	back.setScale(float(Settings::WINDOW_WIDTH) / float(Settings::VIRTUAL_WIDTH), float(Settings::WINDOW_HEIGHT) / float(Settings::VIRTUAL_HEIGHT));
	this->backgrounds.push(back);

	this->houses.push_back(sf::Sprite(this->textures["House1"]));
	this->houses[0].setPosition(187.f,140.f);
	this->houses.push_back(sf::Sprite(this->textures["House2"]));
	this->houses[1].setPosition(706.f, 174.f);
	this->houses.push_back(sf::Sprite(this->textures["House2"]));
	this->houses[2].setPosition(825.f, 310.f);

}

void GameState::initRooms() 
{
	
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/font.ttf"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_FONT";
	}

	this->texts["Message"].setFont(this->font);
	this->texts["Message"].setString("Press 'C' to show controls");
	this->texts["Message"].setCharacterSize(18);
	this->texts["Message"].setFillColor(sf::Color(206, 185, 141));
	this->texts["Message"].setPosition((Settings::WINDOW_WIDTH/2), (Settings::WINDOW_HEIGHT - this->texts["Message"].getGlobalBounds().height));

	this->texts["PlayerPosition"].setFont(this->font);
	this->texts["PlayerPosition"].setCharacterSize(20);
	this->texts["PlayerPosition"].setFillColor(sf::Color(206, 185, 141));
	this->texts["PlayerPosition"].setPosition(30, 30);

	this->texts["CurrentStage"].setFont(this->font);
	this->texts["CurrentStage"].setCharacterSize(24);
	this->texts["CurrentStage"].setFillColor(sf::Color(206, 185, 141));
	this->texts["CurrentStage"].setPosition(700, 30);
}

void GameState::createCombat()
{
	for (auto enemy: enemies)
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

	default: return " ";
	}
}

GameState::GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states)
	: State(_window, _supportedKeys, _states)
{
	this->initTextures();
	this->initFighters();
	this->initItems();
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();

	this->player->pushStage(CurrentStage::MainStage);
}

GameState::GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Player* _p)
	: State(_window, _supportedKeys, _states)
{
	this->initTextures();
	this->initFighters();
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();

	this->resources = _p->getResources();
	this->jobs = _p->getJobs();

	for (int i = 0; i < static_cast<int>(ResourceTypes::count); i++)
	{
		player->setResourceAmoun(static_cast<ResourceTypes>(i), _p->getResourceAmoun(static_cast<ResourceTypes>(i)));
	}

	this->player->setAttributes(_p->getName(),_p->getSprite()->getPosition().x, _p->getSprite()->getPosition().y, _p->getHp(), _p->getAttackPower(), _p->getInitiative(), _p->getDefense(), _p->getVillagers());
}


GameState::~GameState()
{
	delete this->player;
}


void GameState::updateInput(const float& _dt)
{
	bool isInHouse1 = (this->player->getSprite()->getPosition().x > 244 && this->player->getSprite()->getPosition().x < 272 && this->player->getSprite()->getPosition().y < 248.5f);
	bool isInHouse2 = (this->player->getSprite()->getPosition().x > 732 && this->player->getSprite()->getPosition().x < 766 && this->player->getSprite()->getPosition().y < 258.5f);
	bool isInHouse3 = (this->player->getSprite()->getPosition().x > 847 && this->player->getSprite()->getPosition().x < 880 && this->player->getSprite()->getPosition().y > 357.5f 
		&& this->player->getSprite()->getPosition().y < 391);
	this->timeSinceLastUpdate += _dt;

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

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("ACTION")) && isInHouse2)
	{
		this->keyCode = "HOUSE2";
	}
	else
	{
		if (this->keyCode == "HOUSE2")
		{
			this->keyCode = " ";
			this->states->push(new JobMenuState(this->window, this->supportedKeys, this->states, this->player));
		}
	}

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("INVENTORY")) )
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

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("ACTION")) && isInHouse1)
	{
		this->keyCode = "HOUSE1";
	}
	else
	{
		if (this->keyCode == "HOUSE1")
		{
			this->keyCode = " ";
			this->states->push(new StoreState(this->window, this->supportedKeys, this->states, this->player, this->items));
		}
	}

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("ACTION")) && isInHouse3)
	{
		this->keyCode = "HOUSE3";
	}
	else
	{
		if (this->keyCode == "HOUSE3")
		{
			this->keyCode = " ";
			this->states->push(new UpgradeItemState(this->window, this->supportedKeys, this->states, this->player));
		}
	}
}

void GameState::updateInput2(const float& _dt)
{
	Dice dice(1100);
	Dice dice2(1100);
	
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT")) && !isBackgroundMoving)
	{
		this->player->move(-1.f, 0.f, _dt);

		if (dice.getFace() == dice2.getFace())
		{
			this->createCombat();
		}
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT")) && !isBackgroundMoving)
	{
		this->player->move(1.f, 0.f, _dt);

		if (dice.getFace() == dice2.getFace())
		{
			this->createCombat();
		}
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_UP")) && !isBackgroundMoving)
	{
		this->player->move(0.f, -1.f, _dt);

		if (dice.getFace() == dice2.getFace())
		{
			this->createCombat();
		}
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_DOWN")) && !isBackgroundMoving)
	{
		this->player->move(0.f, 1.f, _dt);

		if (dice.getFace() == dice2.getFace())
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
}

void GameState::update(const float& _dt)
{
	isInLvl1 = (this->player->getStage() == CurrentStage::Lvl1R1) || (this->player->getStage() == CurrentStage::Lvl1R2) || (this->player->getStage() == CurrentStage::Lvl1R3) ||
		(this->player->getStage() == CurrentStage::Lvl1R4) || (this->player->getStage() == CurrentStage::Lvl1R5) || (this->player->getStage() == CurrentStage::Lvl1R6) ||
		(this->player->getStage() == CurrentStage::Lvl1R7) || (this->player->getStage() == CurrentStage::Lvl1R8);

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
	this->texts["PlayerPosition"].setString(textString);
	
	if(isInLvl1)
	{
		std::string textString = "Position: X = " + std::to_string(this->backgrounds.top().getPosition().x) + ", Y = " + std::to_string(this->backgrounds.top().getPosition().y);
		this->texts["Message"].setString(textString);
	}

	updateMap(_dt);
	this->texts["CurrentStage"].setString(this->getStringStage(this->player->getStage()));

}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->backgrounds.top());
	
	if (this->player->getStage() == CurrentStage::MainStage)
	{
		for (auto item : this->houses)
		{
			target->draw(item);
		}
	}

	this->player->render(target);

	for (auto text : this->texts)
	{
		target->draw(text.second);
	}
	
}

void GameState::updateMap(const float& dtt)
{
	float _dt = dtt*3;


	if (this->player->getStage() == CurrentStage::Lvl1R1 && this->player->getSprite()->getPosition().x < 50 && sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT"))
		&& !isBackgroundMoving)
	{
		check = "L1R1L";
	}
	if (check == "L1R1L")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(125 * _dt, 0);
		this->player->moveS(110.f, 0.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R2);
		if (this->backgrounds.top().getPosition().x > -1114.9040f)
		{
			this->backgrounds.top().setPosition(-1114.9040f, this->backgrounds.top().getPosition().y);
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::Lvl1R2 && this->player->getSprite()->getPosition().x > 940 && sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT"))
		&& !isBackgroundMoving)
	{
		check = "L1R2R";
	}
	if (check == "L1R2R")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(-125 * _dt, 0);
		this->player->moveS(-110.f, 0.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R1);
		if (this->backgrounds.top().getPosition().x < -2044.8599f)
		{
			this->backgrounds.top().setPosition(-2044.8599f, this->backgrounds.top().getPosition().y);
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
		this->player->moveS(0, 110.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R3);
		if (this->backgrounds.top().getPosition().y > -667.5717f)
		{
			this->backgrounds.top().setPosition(this->backgrounds.top().getPosition().x, -667.5717f);
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
		this->player->moveS(0, -110.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R2);
		if (this->backgrounds.top().getPosition().y < -1214.1099f)
		{
			this->backgrounds.top().setPosition(this->backgrounds.top().getPosition().x, -1214.1099f);
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
		this->player->moveS(-110.f, 0, _dt);
		this->player->pushStage(CurrentStage::Lvl1R4);
		if (this->backgrounds.top().getPosition().x < -2042.2817f)
		{
			this->backgrounds.top().setPosition(-2042.2817f, this->backgrounds.top().getPosition().y);
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
		this->player->moveS(110.f, 0, _dt);
		this->player->pushStage(CurrentStage::Lvl1R3);
		if (this->backgrounds.top().getPosition().x > -1114.9040f)
		{
			this->backgrounds.top().setPosition(-1114.9040f, this->backgrounds.top().getPosition().y);
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::Lvl1R3 && 
		(this->player->getSprite()->getPosition().x > 185 && this->player->getSprite()->getPosition().x < 328) && this->player->getSprite()->getPosition().y < 145 &&
		sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_UP")) && !isBackgroundMoving)
	{
		check = "L1R3U";
	}
	if (check == "L1R3U")
	{
		this->isBackgroundMoving = true;
		this->backgrounds.top().move(0, 250 * _dt);
		this->player->moveS(0, 110.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R5);
		if (this->backgrounds.top().getPosition().y > -31.7096f)
		{
			this->backgrounds.top().setPosition(this->backgrounds.top().getPosition().x, -31.7096f);
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
		this->player->moveS(0, -110.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R3);
		if (this->backgrounds.top().getPosition().y < -667.5717f)
		{
			this->backgrounds.top().setPosition(this->backgrounds.top().getPosition().x, -667.5717f);
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
		this->player->moveS(-110.f, 0, _dt);
		this->player->pushStage(CurrentStage::Lvl1R6);
		if (this->backgrounds.top().getPosition().x < -2042.2817f)
		{
			this->backgrounds.top().setPosition(-2042.2817f, this->backgrounds.top().getPosition().y);
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
		this->player->moveS(110.f, 0, _dt);
		this->player->pushStage(CurrentStage::Lvl1R5);
		if (this->backgrounds.top().getPosition().x > -1114.9040f)
		{
			this->backgrounds.top().setPosition(-1114.9040f, this->backgrounds.top().getPosition().y);
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
		this->player->moveS(110.f, 0, _dt);
		this->player->pushStage(CurrentStage::Lvl1R7);
		if (this->backgrounds.top().getPosition().x > -39.2039f)
		{
			this->backgrounds.top().setPosition(-39.2039f, this->backgrounds.top().getPosition().y);
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
		this->player->moveS(-110.f, 0, _dt);
		this->player->pushStage(CurrentStage::Lvl1R5);
		if (this->backgrounds.top().getPosition().x < -1114.9040f)
		{
			this->backgrounds.top().setPosition(-1114.9040f, this->backgrounds.top().getPosition().y);
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
		this->player->moveS(0, -110.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R8);
		if (this->backgrounds.top().getPosition().y < -644.4125f)
		{
			this->backgrounds.top().setPosition(this->backgrounds.top().getPosition().x, -644.4125f);
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
		this->player->moveS(0, 110.f, _dt);
		this->player->pushStage(CurrentStage::Lvl1R7);
		if (this->backgrounds.top().getPosition().y > -31.7096f)
		{
			this->backgrounds.top().setPosition(this->backgrounds.top().getPosition().x, -31.7096f);
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

}