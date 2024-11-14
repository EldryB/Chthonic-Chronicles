#include "UpgradeItemState.hpp"

void UpgradeItemState::initVariables()
{
}

void UpgradeItemState::initButtons()
{
	for (int i = 0; i < this->items->size(); ++i)
	{
		this->useButtons.push_back(new Button(100.f + i * 40, 500, *this->items->at(i)->getSprite(), &this->font, ""));
	}
}

void UpgradeItemState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("E");
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
}

UpgradeItemState::UpgradeItemState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Player* _p)
	: State(_window, _supportedKeys, _states)
{
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
		this->keyCode = "E";
	}
	else
	{
		if (this->keyCode == "E")
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
			this->texts["ItemDescription"].setString(this->items->at(i)->getDescription());
			this->texts["ItemDescription"].setPosition(
				this->toolTip.getPosition().x + (this->toolTip.getGlobalBounds().width / 2.f) - (this->texts["ItemDescription"].getGlobalBounds().width / 2.f),
				this->toolTip.getPosition().y + (this->toolTip.getGlobalBounds().height / 2.f) - (this->texts["ItemDescription"].getGlobalBounds().height / 2.f)
			);
		}
		else if (button->getButtonState() == ButtonState::Pressed)
		{
			//llamo a funcion para gastar recursos
		}
		++i;
	}
}

void UpgradeItemState::update(const float& _dt)
{
	 this->updateMousePositions();
	this->updateInput(_dt);
	this->updateButtons();
}

void UpgradeItemState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(target);

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

void UpgradeItemState::upgradeItem(Item* it)
{

}

