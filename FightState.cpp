#include "FightState.hpp"

void FightState::initVariables()
{
	this->currentState = CurrentState::Fight;
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
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("Left");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("Right");
	this->keybinds["SELECT"] = this->supportedKeys->at("Enter");
}	

void FightState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/font.ttf"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_FONT";
	}

	this->texts["PlayerHp"].setFont(this->font);
	this->texts["PlayerHp"].setString(std::to_string(this->player->getHp()));
	this->texts["PlayerHp"].setCharacterSize(24);
	this->texts["PlayerHp"].setFillColor(sf::Color::White);
	this->texts["PlayerHp"].setPosition(20,20);

	this->texts["EnemyHp"].setFont(this->font);
	this->texts["EnemyHp"].setString(std::to_string(this->enemy->getHp()));
	this->texts["EnemyHp"].setCharacterSize(24);
	this->texts["EnemyHp"].setFillColor(sf::Color::White);
	this->texts["EnemyHp"].setPosition(20, 20);

	this->texts["TextBox"].setFont(this->font);
	this->texts["TextBox"].setString(" ");
	this->texts["TextBox"].setCharacterSize(17);
	this->texts["TextBox"].setFillColor(sf::Color::White);
	this->texts["TextBox"].setPosition(550, 500);

	this->texts["PlayerStats"].setFont(this->font);
	this->texts["PlayerStats"].setString(" ");
	this->texts["PlayerStats"].setCharacterSize(17);
	this->texts["PlayerStats"].setFillColor(sf::Color::White);
	this->texts["PlayerStats"].setPosition(Settings::WINDOW_WIDTH - this->texts["PlayerStats"].getGlobalBounds().width, Settings::WINDOW_HEIGHT - this->texts["PlayerStats"].getGlobalBounds().height);
}

void FightState::initTextures()
{
	if (!this->textures["FightStage"].loadFromFile("assets/textures/Backgrounds/cave.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_MAIN_STAGE_TEXTURE!";
	}

	if (!this->textures["AttackMenuButtonIdle"].loadFromFile("assets/textures/Buttons/MenuButtonIdle.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_MAIN_MENU_BUTTON_IDLE_TEXTURE!";
	}

	if (!this->textures["AttackMenuButtonHover"].loadFromFile("assets/textures/Buttons/MenuButtonHover.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_MAIN_MENU_BUTTON_HOVER_TEXTURE!";
	}

	if (!this->textures["DICE_SHEET"].loadFromFile("assets/textures/DICE_SHEET.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_MAIN_MENU_BUTTON_HOVER_TEXTURE!";
	}
}

void FightState::initButtons()
{
	this->buttons["ATTACK"] = new Button(100.f, 470.f, this->textures["AttackMenuButtonIdle"], &this->font, "ATTACK");
	this->buttons["INVENTORY"] = new Button(320.f, 470.f, this->textures["AttackMenuButtonIdle"], &this->font, "INVENTORY");
}

void FightState::initDice()
{
	this->dice = new Dice(this->textures["DICE_SHEET"], 20);
	this->dice->setPosition(18.f, 500.f);
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
	this->initDice();
	this->lastPosition = _lastPos;
	
	sf::RectangleShape hpBar1;
	hpBar1.setPosition(100.f,100.f);
	hpBar1.setSize(sf::Vector2f(200.0f, 20.0f));
	hpBar1.setFillColor(sf::Color::Green);
	this->texts["PlayerHp"].setPosition(hpBar1.getPosition().x, hpBar1.getPosition().y - this->texts["EnemyHp"].getGlobalBounds().height + 5);

	this->hpBar.push_back(hpBar1);

	sf::RectangleShape hpBar2;
	hpBar2.setPosition(600.f, 100.f);
	hpBar2.setSize(sf::Vector2f(200.0f, 20.0f));
	hpBar2.setFillColor(sf::Color::Green);
	this->texts["EnemyHp"].setPosition(hpBar2.getPosition().x, hpBar2.getPosition().y - this->texts["EnemyHp"].getGlobalBounds().height + 5);

	this->hpBar.push_back(hpBar2);

	this->fighters.push_back(player);
	this->fighters.push_back(enemy);

	this->currentTurn = 0;
	this->turnCount = 0;
}

FightState::~FightState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->dice;
	this->textures.clear();
}

void FightState::updateInput(const float& _dt)
{
	if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_LEFT"]))
	{
		this->keyCode = "MOVE_LEFT";
	}
	else
	{
		if (this->keyCode == "MOVE_LEFT")
		{
			this->keyCode = " ";
			if (this->selectedButtonIndex > 0)
			{
				--this->selectedButtonIndex;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_RIGHT"]))
	{
		this->keyCode = "MOVE_RIGHT";
	}
	else
	{
		if (this->keyCode == "MOVE_RIGHT")
		{
			this->keyCode = " ";
			if (this->selectedButtonIndex < this->buttons.size() - 1)
			{
				++this->selectedButtonIndex;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(this->keybinds["SELECT"]))
	{
		this->keyCode = "SELECT";
	}
	else
	{
		if (this->keyCode == "SELECT")
		{
			this->keyCode = " ";
			auto it = std::next(this->buttons.begin(), this->selectedButtonIndex);
			if (it != this->buttons.end())
			{
				if (it->first == "ATTACK")
				{
					this->dice->roll();
					this->enemy->takeDamage(this->player->getAttackPower() + (this->player->getAttackPower() * (this->dice->getFace() / 100)));

					this->playerTurn = false;
					this->turnQueue.pop();
					count = 0;
				}
				else if (it->first == "INVENTORY")
				{
					this->states->push(new InventoryState(this->window, this->supportedKeys, this->states, this->player, this->check));
				}
			}
		}
	}
}

void FightState::updateButtons()
{
	int index = 0;
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);

		if (it.second->getButtonState() == ButtonState::Idle)
		{
			it.second->setTexture(this->textures["AttackMenuButtonIdle"]);
			it.second->setTextFillColor(sf::Color(21, 26, 38));
		}

		if (it.second->getButtonState() == ButtonState::Hover || index == this->selectedButtonIndex)
		{
			it.second->setTexture(this->textures["AttackMenuButtonHover"]);
			it.second->setTextFillColor(sf::Color(96, 60, 3));
		}

		++index;
	}

	if (this->buttons["ATTACK"]->getButtonState() == ButtonState::Pressed && this->playerTurn)
	{
		this->dice->roll();
		this->enemy->takeDamage(this->player->getAttackPower() + (this->player->getAttackPower() * (this->dice->getFace() / 100)));

		this->playerTurn = false;
		this->turnQueue.pop();
		count = 0;
	}

	if (this->buttons["INVENTORY"]->getButtonState() == ButtonState::Pressed && this->playerTurn)
	{
		this->states->push(new InventoryState(this->window, this->supportedKeys, this->states, this->player,this->check));
	}
}

void FightState::update(const float& _dt)
{
	this->player->setLookingDirection(LookingDirection::Right);
	count += this->clock.restart().asSeconds();
	
	this->player->update(_dt);
	this->enemy->update(_dt);
	if (this->playerTurn)
	{
		this->updateMousePositions();
		this->updateInput(_dt);
		this->updateButtons();
		this->dice->update(_dt);
	}

	if (this->check->at(0) == 'N')
	{
		this->check->at(0) = 'S';
		this->playerTurn = false;
		this->turnQueue.pop();
		count = 0;
	}

	float barLife = this->player->getHp() / this->hpMax[0];
	this->hpBar[0].setSize(sf::Vector2f(200.0f * barLife, 20.0f));

	for (size_t i = 1; i < hpBar.size(); i++)
	{
		float bar = this->enemy->getHp() / this->hpMax[i];
		this->hpBar[i].setSize(sf::Vector2f(200.0f * bar, 20.0f));
	}

	this->texts["PlayerHp"].setString(std::to_string(static_cast<int>(this->player->getHp())));
	this->texts["EnemyHp"].setString(std::to_string(static_cast<int>(this->enemy->getHp())));

	if (!this->player->isAlive())
	{
		this->states->push(new LostFightState(this->window, this->supportedKeys, this->states, this->player));
	}

	if (!this->enemy->isAlive())
	{
		Dice dropItemProbability(100);
		if (dropItemProbability.getFace() <= 20)
		{
			this->player->addItem(this->enemy->dropItem());
		}
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
		this->texts["TextBox"].setString(stringText);

		if (Player* p = dynamic_cast<Player*>(currentFighter))
		{
			this->playerTurn = true;
		}

		if (!this->playerTurn)
		{
			if (count > 3.f)
			{
				this->player->takeDamage(this->enemy->getAttackPower());
				turnQueue.pop();
			}
		}
	}
	
	std::string text2 = "AttackPower: " + std::to_string(static_cast<int>(this->player->getAttackPower())) + "\n" + "Defense: " + std::to_string(this->player->getDefense())
		+ "\n" + "Initiative: " + std::to_string(this->player->getInitiative());
	this->texts["PlayerStats"].setString(text2);
	this->texts["PlayerStats"].setPosition(this->hpBar[0].getPosition().x, this->hpBar[0].getPosition().y + this->hpBar[0].getGlobalBounds().height + this->texts["PlayerStats"].getGlobalBounds().height);
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
		this->dice->render(target);
	}

	this->player->render(target);

	this->enemy->render(target);

	for (auto item: this->hpBar)
	{
		target->draw(item);
	}

	for (auto text : this->texts)
	{
		target->draw(text.second);
	}
}

void FightState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}
