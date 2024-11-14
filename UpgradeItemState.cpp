#include "UpgradeItemState.hpp"

void UpgradeItemState::initVariables()
{
	this->keyCode = " ";
}

void UpgradeItemState::initButtons()
{
	for (int i = 0; i < this->items->size(); ++i)
	{
		this->useButtons.push_back(new Button(100.f + i * 55, 500, *this->items->at(i)->getSprite(), &this->font, ""));
	}
}

void UpgradeItemState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
}

void UpgradeItemState::initTextures()
{
	if (!this->textures["UpgradeStage"].loadFromFile("assets/textures/Backgrounds/upgradeStage.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_MAIN_STAGE_TEXTURE!";
	}

	if (!this->textures["MenuButtonIdle"].loadFromFile("assets/textures/Buttons/MenuButtonIdle.png"))
	{
		throw "ERROR::MENU_STATE::COULD_NOT_LOAD_MENU_BUTTON_IDLE_TEXTURE!";
	}

	if (!this->textures["MenuButtonHover"].loadFromFile("assets/textures/Buttons/MenuButtonHover.png"))
	{
		throw "ERROR::MENU_STATE::COULD_NOT_LOAD_MENU_BUTTON_HOVER_TEXTURE!";
	}
}

void UpgradeItemState::initBackground()
{
	sf::Sprite back;
	back.setTexture(this->textures["UpgradeStage"]);
	//back.setScale(float(Settings::WINDOW_WIDTH) / float(Settings::VIRTUAL_WIDTH), float(Settings::WINDOW_HEIGHT) / float(Settings::VIRTUAL_HEIGHT));
	this->background = (back);

	this->toolTip.setTexture(this->textures["MenuButtonIdle"]);
	this->toolTip.setPosition(Settings::WINDOW_WIDTH - this->toolTip.getGlobalBounds().width - 10.f,
		Settings::WINDOW_HEIGHT - this->toolTip.getGlobalBounds().height - 10.f);
}

void UpgradeItemState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/font.ttf"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_FONT";
	}

	this->texts["ItemDescription"].setFont(this->font);
	this->texts["ItemDescription"].setString(" ");
	this->texts["ItemDescription"].setCharacterSize(12);
	this->texts["ItemDescription"].setFillColor(sf::Color::Black);
	this->texts["ItemDescription"].setPosition(
		this->toolTip.getPosition().x + (this->toolTip.getGlobalBounds().width / 2.f) - (this->texts["ItemDescription"].getGlobalBounds().width / 2.f),
		this->toolTip.getPosition().y + (this->toolTip.getGlobalBounds().height / 2.f) - (this->texts["ItemDescription"].getGlobalBounds().height / 2.f)
	);

	this->texts["InfoResources"].setFont(this->font);
	this->texts["InfoResources"].setString(" ");
	this->texts["InfoResources"].setCharacterSize(12);
	this->texts["InfoResources"].setFillColor(sf::Color::White);
	this->texts["InfoResources"].setPosition(Settings::WINDOW_WIDTH - this->texts["InfoResources"].getGlobalBounds().width - 10.f,
		Settings::WINDOW_HEIGHT/2 - this->texts["InfoResources"].getGlobalBounds().height - 10.f);
}

UpgradeItemState::UpgradeItemState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Player* _p)
	: State(_window, _supportedKeys, _states)
{
	this->initVariables();
	this->initTextures();
	this->initBackground();
	this->initFonts();

	this->player = _p;
	this->items = player->getInventory();
	this->initButtons();

}

UpgradeItemState::~UpgradeItemState()
{
	for (auto& button : this->useButtons)
	{
		delete button;
	}
	this->useButtons.clear();

}

void UpgradeItemState::updateInput(const float& _dt)
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

void UpgradeItemState::updateButtons()
{
	int i = 0;
	for (auto& button: this->useButtons)
	{
		button->update(this->mousePosView);

		if (button->getButtonState() == ButtonState::Idle)
		{
			button->setSprite(*this->items->at(i)->getSprite());
			button->setPosition(100 + i * 40, 500);
		}

		else if (button->getButtonState() == ButtonState::Hover)
		{
			button->setSprite(*this->items->at(i)->getSprite());
			button->setPosition(100 + i * 40, 500);
			this->setDescription(this->items->at(i));
			this->texts["ItemDescription"].setPosition(
				this->toolTip.getPosition().x + (this->toolTip.getGlobalBounds().width / 2.f) - (this->texts["ItemDescription"].getGlobalBounds().width / 2.f),
				this->toolTip.getPosition().y + (this->toolTip.getGlobalBounds().height / 2.f) - (this->texts["ItemDescription"].getGlobalBounds().height / 2.f)
			);
		}
		else if (button->getButtonState() == ButtonState::Pressed)
		{
			if (Weapon* c = dynamic_cast<Weapon*>(this->items->at(i)))
			{
				upgradeItem(c);

				for (int j = 0; j < pos.size(); j++)
				{
					int k = 0;
					for (auto& button : this->useButtons)
					{
						if(k == pos[j])
						{
							delete button;
							this->useButtons.erase(this->useButtons.begin() + k);
							--i;
							this->useButtons.clear();
							this->initButtons();
						}
						++k;
					}
				}
				pos.clear();
			}
		}
		++i;
	}
}

void UpgradeItemState::update(const float& _dt)
{
	this->updateInput(_dt);
	 this->updateMousePositions();
	this->updateButtons();

	std::string textStr = "";
	for (int i = 0; i < static_cast<int>(ResourceTypes::count); ++i)
	{
		textStr += this->player->getResourceName(static_cast<ResourceTypes>(i)) + ": " + std::to_string(this->player->getResourceAmoun(static_cast<ResourceTypes>(i))) + "\n";
	}
	this->texts["InfoResources"].setString(textStr);
	this->texts["InfoResources"].setPosition(Settings::WINDOW_WIDTH - this->texts["InfoResources"].getGlobalBounds().width - 10.f,
		Settings::WINDOW_HEIGHT / 2 - this->texts["InfoResources"].getGlobalBounds().height - 10.f);
}

void UpgradeItemState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(target);

	for (auto text : this->texts)
	{
		if (text.first != "ItemDescription")
		{
			target->draw(text.second);
		}
	}

	for (auto& button : this->useButtons)
	{
		if (button->getButtonState() == ButtonState::Hover)
		{
			target->draw(this->toolTip);
			target->draw(this->texts["ItemDescription"]);
		}
	}
}

void UpgradeItemState::renderButtons(sf::RenderTarget* target)
{
	for (auto& button : this->useButtons)
	{
		button->render(target);
	}
}

void UpgradeItemState::upgradeItem(Weapon* it)
{
	std::string str = it->getName();
	
	if (str == "Dagger")
	{
		int wood = this->player->getResourceAmoun(ResourceTypes::wood);
		int cloth = this->player->getResourceAmoun(ResourceTypes::cloth);
		int stone = this->player->getResourceAmoun(ResourceTypes::stone);

		bool check = (wood - 20 >= 0 ) && (cloth - 2 >= 0) && (stone - 10 >= 0);
		
		if(check)
		{
			this->player->setResourceAmoun(ResourceTypes::wood, wood - 20);
			this->player->setResourceAmoun(ResourceTypes::cloth, cloth - 2);
			this->player->setResourceAmoun(ResourceTypes::stone, stone - 10);

			it->setAtributes(it->getInitiative() + 1, it->getAttackPower() + 2);

		}
	}

	else if (str == "Red Sword")
	{
		int count = 0;

		for (auto item: *items)
		{
			if (item->getName() == "Red Sword")
			{
				++count;
			}
		}

		int iron = this->player->getResourceAmoun(ResourceTypes::iron);
		int silk = this->player->getResourceAmoun(ResourceTypes::silk);

		bool check = (count >= 2) && (iron - 20 >= 0) && (silk - 5 >= 0);

		if (check)
		{
			this->player->setResourceAmoun(ResourceTypes::iron, iron - 20);
			this->player->setResourceAmoun(ResourceTypes::silk, silk - 5);

			it->setAtributes(it->getInitiative() + 1, it->getAttackPower() + 3);
			this->pos.push_back(this->player->eraseItem(it));
			this->pos.push_back(this->player->eraseItem(it));
			Weapon* w = it;
			this->player->addItem(w);
			
		}
	}

	else if (str == "Blue Sword")
	{
		int count = 0;

		for (auto item : *items)
		{
			if (item->getName() == "Blue Sword")
			{
				++count;
			}
		}

		int gold = this->player->getResourceAmoun(ResourceTypes::gold);
		int silk = this->player->getResourceAmoun(ResourceTypes::silk);
		int leather = this->player->getResourceAmoun(ResourceTypes::leather);

		bool check = (count >= 3) && (gold - 10 >= 0) && (silk - 2 >= 0) && (leather - 25 >= 0);

		if (check)
		{
			this->player->setResourceAmoun(ResourceTypes::gold, gold - 10);
			this->player->setResourceAmoun(ResourceTypes::silk, silk - 2);
			this->player->setResourceAmoun(ResourceTypes::leather, leather - 25);

			it->setAtributes(it->getInitiative() + 2, it->getAttackPower() + 3);
			this->pos.push_back(this->player->eraseItem(it));
			this->pos.push_back(this->player->eraseItem(it));
			this->pos.push_back(this->player->eraseItem(it));
			Weapon* w = it;
			this->player->addItem(w);

		}
	}

	else if (str == "Potion")
	{
	

		int gold = this->player->getResourceAmoun(ResourceTypes::gold);
		int silk = this->player->getResourceAmoun(ResourceTypes::silk);
		int leather = this->player->getResourceAmoun(ResourceTypes::leather);

		bool check = (gold - 1 >= 0) && (silk - 1 >= 0) && (leather - 2 >= 0);

		if (check)
		{
			this->player->setResourceAmoun(ResourceTypes::gold, gold - 1);
			this->player->setResourceAmoun(ResourceTypes::silk, silk - 1);
			this->player->setResourceAmoun(ResourceTypes::leather, leather - 2);
			Item* item1 = (new Potion(this->textures["POTION_SHEET"], "Potion", 1, 20.f, "Fresh!", 10));
			item1->setIconRect(sf::IntRect(0, 0, 41, 42));
			this->player->addItem(item1);

		}
	}

}

void UpgradeItemState::setDescription(Item* it)
{
	std::string str = it->getName();

	if (str == "Dagger")
	{
		this->texts["ItemDescription"].setString("Need 20 wood\n2 cloth\n10 stone\n+1 init\n+2 attack");
	}

	else if (str == "Red Sword")
	{
		this->texts["ItemDescription"].setString("Need 2 red sword\n20 iron\n5 silk\n+1 init\n+3 attack");
	}

	else if (str == "Blue Sword")
	{
		this->texts["ItemDescription"].setString("Need 3 blue sword\n10 gold\n2 silk\n25 leather\n+2 init\n+3 attack");
	}

	else if (str == "Potion")
	{
		this->texts["ItemDescription"].setString("Need 1 gold\n1 silk\n2 leather\n+1 potion");
	}

	else if (str == "Rusty Armor")
	{
		this->texts["ItemDescription"].setString("Have not upgrade");
	}

	else if (str == "Thunder Armor")
	{
		this->texts["ItemDescription"].setString("Have not upgrade");
	}
}

