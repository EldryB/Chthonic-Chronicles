#include "StoreState.hpp"

void StoreState::initVariables()
{
	this->isBackgroundMoving = false;
	this->check = " ";
}

void StoreState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
	this->keybinds["ACTION"] = this->supportedKeys->at("E");
	this->keybinds["INVENTORY"] = this->supportedKeys->at("I");
	this->keybinds["Q"] = this->supportedKeys->at("Q");
}

void StoreState::initTextures()
{
	if (!this->textures["StoreStage"].loadFromFile("assets/textures/Backgrounds/storeStage.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_MAIN_STAGE_TEXTURE!";
	}
}

void StoreState::initItems()
{
}

void StoreState::initBackground()
{
	sf::Sprite back;
	back.setTexture(this->textures["StoreStage"]);
	back.setScale(float(Settings::WINDOW_WIDTH) / float(Settings::VIRTUAL_WIDTH), float(Settings::WINDOW_HEIGHT + 0.5f) / float(Settings::VIRTUAL_HEIGHT));
	this->background = (back);
}

void StoreState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/font.ttf"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_FONT";
	}

	this->texts["Message"].setFont(this->font);
	this->texts["Message"].setCharacterSize(18);
	this->texts["Message"].setFillColor(sf::Color(sf::Color::Black));
	this->texts["Message"].setString("String");
	this->texts["Message"].setPosition((Settings::WINDOW_WIDTH / 2), (Settings::WINDOW_HEIGHT - this->texts["Message"].getGlobalBounds().height));

	this->texts["PlayerPosition"].setFont(this->font);
	this->texts["PlayerPosition"].setCharacterSize(20);
	this->texts["PlayerPosition"].setFillColor(sf::Color(sf::Color::Black));
	this->texts["PlayerPosition"].setPosition(30, 30);

	this->texts["CurrentStage"].setFont(this->font);
	this->texts["CurrentStage"].setCharacterSize(24);
	this->texts["CurrentStage"].setFillColor(sf::Color(sf::Color::Black));
	this->texts["CurrentStage"].setPosition(700, 30);

	this->texts["Description"].setFont(this->font);
	this->texts["Description"].setCharacterSize(12);
	this->texts["Description"].setFillColor(sf::Color(sf::Color::Black));
	this->texts["Description"].setPosition(50, 500);

	this->message.setFont(this->font);
	this->message.setCharacterSize(12);
	this->message.setString("Pres E to Buy");
	this->message.setFillColor(sf::Color(sf::Color::Black));
	this->message.setPosition(300, 500);
}

std::string StoreState::getStringStage(CurrentStage _c)
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



StoreState::StoreState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Player* _p, std::vector<Item*> _items)
	: State(_window, _supportedKeys, _states)
{
	initVariables();
	initTextures();
	initKeybinds();
	initBackground();
	initFonts();
	this->player = _p;
	this->player->pushStage(CurrentStage::StoreStage);
	this->player->setPosition(230.f, 547.f);
	this->items = _items;
	this->takeItem();
}

StoreState::~StoreState()
{

}

void StoreState::updateInput(const float& _dt)
{

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT")) && !isBackgroundMoving)
	{
		this->player->move(-1.f, 0.f, _dt);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT")) && !isBackgroundMoving)
	{
		this->player->move(1.f, 0.f, _dt);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_UP")) && !isBackgroundMoving)
	{
		this->player->move(0.f, -1.f, _dt);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_DOWN")) && !isBackgroundMoving)
	{
		this->player->move(0.f, 1.f, _dt);
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

	if (sf::Keyboard::isKeyPressed(this->keybinds["ACTION"]) && this->player->getSprite()->getPosition().y > 540.f)
	{
		this->keyCode = "ACTION";
	}
	else
	{
		if (this->keyCode == "ACTION")
		{
			this->keyCode = " ";
			this->player->setPosition(250.f, 248.f);
			this->player->pushStage(CurrentStage::MainStage);
			this->states->pop();

		}
	}

	Item* it = this->itemColision();
	if (it)
	{
		this->message.setString("Press E to buy\nPrice: " + std::to_string(it->getPrice()));
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds["ACTION"]) && this->player->getStage() == CurrentStage::StoreStage2 && it)
	{
		this->keyCode = "BUY";

	}
	else
	{
		if (it)
		{
			if (this->keyCode == "BUY")
			{
				this->keyCode = " ";

				if ((this->player->getResourceAmoun(ResourceTypes::coin) - it->getPrice() >= 0))
				{
					this->player->setResourceAmoun(ResourceTypes::coin, this->player->getResourceAmoun(ResourceTypes::coin) - it->getPrice());
					this->player->addItem(it);
					for (int i = 0; i < items.size(); ++i)
					{
						if (items[i] == it)
						{
							this->items.erase(this->items.begin() + i);
						}
					}
					it = nullptr;
				}
			}
		}
	}

}

void StoreState::update(const float& _dt)
{
	updateInput(_dt);
	this->player->update(_dt);

	std::string textString = "Position: X = " + std::to_string(this->player->getSprite()->getPosition().x) + ", Y = " + std::to_string(this->player->getSprite()->getPosition().y);
	this->texts["PlayerPosition"].setString(textString);

	std::string textString2 = "Position: X = " + std::to_string(this->background.getPosition().x) + ", Y = " + std::to_string(this->background.getPosition().y);
	this->texts["Message"].setString(textString2);

	this->texts["CurrentStage"].setString(this->getStringStage(this->player->getStage()));

	this->updateMap(_dt);
	std::string textstr{ " " };
	for (auto item : this->items)
	{
		textstr += item->getName() + "\n";
	}
	textstr += "Coins: " + std::to_string(this->player->getResourceAmoun(ResourceTypes::coin));
	this->texts["Description"].setString(textstr);
}

void StoreState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->player->render(target);

	for (auto text : this->texts)
	{
		target->draw(text.second);
	}

	if (this->player->getStage() == CurrentStage::StoreStage2)
	{
		for (auto item : this->items)
		{
			item->render(target);
		}
	}

	Item* it = this->itemColision();
	if (it)
	{
		target->draw(this->message);
	}
}

void StoreState::takeItem()
{
	Dice dice(this->items.size());
	std::vector<Item*> itemList;
	while (itemList.size() != 4)
	{
		bool check = true;
		Item* item = items[dice.getFace() - 1];
		for (int j = 0; j < itemList.size(); ++j)
		{
			if (item->getName() == itemList[j]->getName())
			{
				check = false;
				break;
			}
		}
		if (check)
		{
			itemList.push_back(item);
		}
	}
	items = itemList;


	items[0]->setPosition(200 + 1100, 150);
	items[1]->setPosition(500 + 1100, 150);
	items[2]->setPosition(200 + 1100, 250);
	items[3]->setPosition(500 + 1100, 250);

}

Item* StoreState::itemColision()
{
	for (auto item : this->items)
	{
		sf::FloatRect rect1 = this->player->getSprite()->getGlobalBounds();
		sf::FloatRect rect2 = item->getSprite()->getGlobalBounds();

		if (rect1.intersects(rect2))
		{
			return item;
		}
	}

	return nullptr;
}

void StoreState::updateMap(const float& dt)
{
	float _dt = 3 * dt;
	if (this->player->getStage() == CurrentStage::StoreStage && this->player->getSprite()->getPosition().x > 940 && sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT"))
		&& !isBackgroundMoving)
	{
		check = "StoreR";
	}
	if (check == "StoreR")
	{
		this->isBackgroundMoving = true;
		this->background.move(-125 * _dt, 0);
		this->player->moveS(-110.f, 0.f, _dt);
		this->player->pushStage(CurrentStage::StoreStage2);

		for (auto item : this->items)
		{
			item->move(-130.f, 0.f, _dt);
		}

		if (this->background.getPosition().x < -970.f)
		{
			this->background.setPosition(-970.f, this->background.getPosition().y);
			this->isBackgroundMoving = false;
			check = " ";
		}
	}

	if (this->player->getStage() == CurrentStage::StoreStage2 && this->player->getSprite()->getPosition().x < 50 && sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT"))
		&& !isBackgroundMoving)
	{
		check = "StoreL";
	}
	if (check == "StoreL")
	{
		this->isBackgroundMoving = true;
		this->background.move(125 * _dt, 0);
		this->player->moveS(110.f, 0.f, _dt);

		for (auto item : this->items)
		{
			item->move(130.f, 0.f, _dt);
		}

		if (this->background.getPosition().x > 0)
		{
			this->background.setPosition(0, this->background.getPosition().y);
			this->isBackgroundMoving = false;
			check = " ";
			this->player->pushStage(CurrentStage::StoreStage);
		}
	}
}



