#include "FightState.hpp"

bool FightState::isFightOver()
{
	return (!this->player->isAlive()) || (!this->enemy->isAlive());
}

void FightState::initVariables()
{
	this->selectedButtonIndex = 0;
	this->keyCode = " ";
	this->hpMax.push_back(this->player->getHp());
	this->hpMax.push_back(this->enemy->getHp());
	this->count = 0;
}

void FightState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["ACTION"] = this->supportedKeys->at("E");
	this->keybinds["CONTROLS"] = this->supportedKeys->at("C");
	this->keybinds["Q"] = this->supportedKeys->at("Q");
	this->keybinds["Z"] = this->supportedKeys->at("Z");
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

	this->message2.setFont(this->font);
	this->message2.setString(std::to_string(this->enemy->getHp()));
	this->message2.setCharacterSize(24);
	this->message2.setFillColor(sf::Color::White);
	this->message2.setPosition(20, 20);

	this->textBox.setFont(this->font);
	this->textBox.setString(" ");
	this->textBox.setCharacterSize(17);
	this->textBox.setFillColor(sf::Color::White);
	this->textBox.setPosition(450, 550);
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

	if (!this->textures["Bat"].loadFromFile("assets/textures/enemy_1/at1.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE!";
	}

	if (!this->textures["AttackMenuButtonIdle"].loadFromFile("assets/textures/Buttons/MenuButtonIdle.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_MAIN_MENU_BUTTON_IDLE_TEXTURE!";
	}

	if (!this->textures["AttackMenuButtonHover"].loadFromFile("assets/textures/Buttons/MenuButtonHover.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_MAIN_MENU_BUTTON_HOVER_TEXTURE!";
	}
}

void FightState::initButtons()
{
	this->buttons["ATTACK"] = new Button(100, 470.f, this->textures["AttackMenuButtonIdle"], &this->font, "ATTACK");
}

void FightState::initFighters(Player* _p, Enemy* _enemy)
{
	this->player = _p;
	this->player->setLookingDirection(LookingDirection::Right);
	this->player->setPosition(304.8f, 394.97f);
	this->enemy = _enemy;
}

void FightState::initBackground()
{
	this->background.setTexture(this->textures["FightStage"]);
	this->background.setScale(float(Settings::WINDOW_WIDTH) / float(Settings::VIRTUAL_WIDTH), float(Settings::WINDOW_HEIGHT) / float(Settings::VIRTUAL_HEIGHT));
}

FightState::FightState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Player* _p, Enemy* _enemy, sf::Vector2f _lastPos)
	: State(_window, _supportedKeys, _states)
{
	this->initTextures();
	this->initFighters(_p, _enemy);
	this->initVariables();
	this->initBackground();
	this->initKeybinds();
	this->initFonts();
	this->initButtons();
	this->lastPosition = _lastPos;
	
	sf::RectangleShape hpBar1;
	hpBar1.setPosition(100.f,100.f);
	hpBar1.setSize(sf::Vector2f(200.0f, 20.0f));
	hpBar1.setFillColor(sf::Color::Green);
	this->message.setPosition(hpBar1.getPosition().x, hpBar1.getPosition().y - this->message2.getGlobalBounds().height + 5);

	this->hpBar.push_back(hpBar1);

	sf::RectangleShape hpBar2;
	hpBar2.setPosition(600.f, 100.f);
	hpBar2.setSize(sf::Vector2f(200.0f, 20.0f));
	hpBar2.setFillColor(sf::Color::Green);
	this->message2.setPosition(hpBar2.getPosition().x, hpBar2.getPosition().y - this->message2.getGlobalBounds().height + 5);

	this->hpBar.push_back(hpBar2);

	fighters.push_back(player);
	fighters.push_back(enemy);

	this->currentTurn = 0;
	this->turnCount = 0;
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
			this->enemy->setHp(this->enemy->getHp() - 50.f);
			if (this->enemy->getHp() < 0)
			{
				this->enemy->setHp(0);
			}
		}
	}
}

void FightState::updateButtons()
{

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);

		if (it.second->getButtonState() == ButtonState::Idle)
		{
			it.second->setTexture(this->textures["AttackMenuButtonIdle"]);
			it.second->setTextFillColor(sf::Color(21, 26, 38));
		}

		if (it.second->getButtonState() == ButtonState::Hover)
		{
			it.second->setTexture(this->textures["AttackMenuButtonHover"]);
			it.second->setTextFillColor(sf::Color(96, 60, 3));
		}
	}


	if (this->buttons["ATTACK"]->getButtonState() == ButtonState::Pressed && this->playerTurn)
	{
		//this->enemy->takeDamage(this->player->getDamage());
		this->enemy->takeDamage(this->player->getDamage());

		this->playerTurn = false;
		this->turnQueue.pop();
		count = 0;
	}
}

void FightState::update(const float& _dt)
{

	count += this->clock.restart().asSeconds();

	this->updateMousePositions();
	this->updateInput(_dt);
	this->player->update(_dt);
	this->enemy->update(_dt);
	this->updateButtons();

	float barLife = this->player->getHp() / this->hpMax[0];
	this->hpBar[0].setSize(sf::Vector2f(200.0f * barLife, 20.0f));

	for (size_t i = 1; i < hpBar.size(); i++)
	{
		float bar = this->enemy->getHp() / this->hpMax[i];
		this->hpBar[i].setSize(sf::Vector2f(200.0f * bar, 20.0f));
	}

	this->message.setString(std::to_string(static_cast<int>(this->player->getHp())));
	this->message2.setString(std::to_string(static_cast<int>(this->enemy->getHp())));

	if (!this->player->isAlive())
	{
		this->states->push(new LostFightState(this->window, this->supportedKeys, this->states, this->player));
	}

	if (!this->enemy->isAlive())
	{
		this->player->setPosition(lastPosition.x, lastPosition.y);
		this->states->pop();
	}

	
	turnCount++;
	updateTurnQueue(turnCount);
	if (!turnQueue.empty())
	{
		currentTurn++;
		auto currentFighter = turnQueue.front();
		std::string stringText = currentFighter->getName() + " empieza su turno ";
		this->textBox.setString(stringText);

		if (Player* p = dynamic_cast<Player*>(currentFighter))
		{
			this->playerTurn = true;
			//p->attack(fighters[1]);
		}

		if (!this->playerTurn)
		{
			if(count > 3.f)
			{
				this->player->takeDamage(this->enemy->getDamage());
				turnQueue.pop();
			}
		}
	}
	
}

void FightState::updateTurnQueue(int turnCount)
{
	for (const auto& fighter : fighters)
	{
		if (turnCount % (100 / fighter->getInitiative()) == 0)
		{
			turnQueue.push(fighter);
		}
	}
}

void FightState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);

	if(playerTurn)
	{
		this->renderButtons(target);
	}

	this->player->render(target);

	this->enemy->render(target);

	target->draw(this->text);
	for (auto item: this->hpBar)
	{
		target->draw(item);
	}
	target->draw(this->message);
	target->draw(this->message2);
	target->draw(this->textBox);

}

void FightState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}
