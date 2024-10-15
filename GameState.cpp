#include "GameState.hpp"

void GameState::initVariables()
{

}

void GameState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
}

void GameState::initTextures()
{
	if (!this->textures["MainStage"].loadFromFile("assets/textures/mainStage.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_MAIN_STAGE_TEXTURE!";
	}

	if (!this->textures["LowBridge"].loadFromFile("assets/textures/low_bridge_edge.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_LOW_BRIDGE_TEXTURE!";
	}

	if (!this->textures["PLAYER_SHEET"].loadFromFile("assets/textures/Player/PLAYER_SHEET.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE!";
	}

	if (!this->textures["Right1"].loadFromFile("assets/textures/right1.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TEXTURE!";
	}

	if (!this->textures["Right2"].loadFromFile("assets/textures/right2.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TEXTURE!";
	}

	if (!this->textures["Right3"].loadFromFile("assets/textures/right3.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TEXTURE!";
	}

	if (!this->textures["Left1"].loadFromFile("assets/textures/left1.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TEXTURE!";
	}

	if (!this->textures["Left2"].loadFromFile("assets/textures/left2.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TEXTURE!";
	}

	if (!this->textures["Left3"].loadFromFile("assets/textures/left3.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TEXTURE!";
	}

	if (!this->textures["Front1"].loadFromFile("assets/textures/front1.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TEXTURE!";
	}

	if (!this->textures["Front2"].loadFromFile("assets/textures/front2.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TEXTURE!";
	}

	if (!this->textures["Front3"].loadFromFile("assets/textures/front3.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TEXTURE!";
	}

	if (!this->textures["Back1"].loadFromFile("assets/textures/back1.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TEXTURE!";
	}

	if (!this->textures["Back2"].loadFromFile("assets/textures/back2.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TEXTURE!";
	}

	if (!this->textures["Back3"].loadFromFile("assets/textures/back3.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_TEXTURE!";
	}
}

void GameState::initFighters()
{
	this->player = new Fighter(250.f, 370.f, this->textures["PLAYER_SHEET"], "Player");
}

void GameState::initBackground()
{
	this->background.setTexture(this->textures["MainStage"]);
	this->background.setScale(float(Settings::WINDOW_WIDTH) / float(Settings::VIRTUAL_WIDTH), float(Settings::WINDOW_HEIGHT) / float(Settings::VIRTUAL_HEIGHT));
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/font.ttf"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_FONT";
	}
}

void GameState::initFighterFrames()
{
	this->animationFighter.RightAnimation.push_back(this->textures["Right1"]);
	this->animationFighter.RightAnimation.push_back(this->textures["Right2"]);
	this->animationFighter.RightAnimation.push_back(this->textures["Right2"]);
	this->animationFighter.RightAnimation.push_back(this->textures["Right3"]);


	this->animationFighter.LeftAnimation.push_back(this->textures["Left1"]);
	this->animationFighter.LeftAnimation.push_back(this->textures["Left2"]);
	this->animationFighter.LeftAnimation.push_back(this->textures["Left2"]);
	this->animationFighter.LeftAnimation.push_back(this->textures["Left3"]);


	this->animationFighter.FrontAnimation.push_back(this->textures["Front1"]);
	this->animationFighter.FrontAnimation.push_back(this->textures["Front2"]);
	this->animationFighter.FrontAnimation.push_back(this->textures["Front2"]);
	this->animationFighter.FrontAnimation.push_back(this->textures["Front3"]);


	this->animationFighter.BackAnimation.push_back(this->textures["Back1"]);
	this->animationFighter.BackAnimation.push_back(this->textures["Back2"]);
	this->animationFighter.BackAnimation.push_back(this->textures["Back2"]);
	this->animationFighter.BackAnimation.push_back(this->textures["Back3"]);
}



float GameState::getXPos(sf::Sprite* spr)
{
	return spr->getPosition().x;
}

float GameState::getYPos(sf::Sprite* spr)
{
	return spr->getPosition().y;
}

void GameState::setXPos(float _x, sf::Sprite* sprite)
{
	float _y = sprite->getPosition().y;
	sprite->setPosition(_x, _y);
}
void GameState::setYPos(float _y, sf::Sprite* sprite)
{
	float _x = sprite->getPosition().x;
	sprite->setPosition(_x, _y);
}

GameState::GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states)
	: State(_window, _supportedKeys, _states)
{
	this->initVariables();
	this->initTextures();
	this->initFighters();
	this->initBackground();
	this->initFonts();
	this->initFighterFrames();
	this->initKeybinds();

	this->currentFrame = 0;
	this->timeSinceLastUpdate = 0.0f;
	this->timeBetweenUpdates = 0.08f;
	this->text.setFont(this->font);
	this->text.setCharacterSize(20);
	this->text.setFillColor(sf::Color::White);
	text.setPosition(30, 30);
}

GameState::GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states, Fighter* _p)
	: State(_window, _supportedKeys, _states)
{
	this->initVariables();
	this->initTextures();
	this->initFighters();
	this->initBackground();
	this->initFonts();
	this->initFighterFrames();
	this->initKeybinds();

	this->currentFrame = 0;
	this->timeSinceLastUpdate = 0.0f;
	this->timeBetweenUpdates = 0.08f;
	this->text.setFont(this->font);
	this->text.setCharacterSize(20);
	this->text.setFillColor(sf::Color::White);
	text.setPosition(30, 30);
	this->player->setAttributes(_p->getSprite()->getPosition().x, _p->getSprite()->getPosition().y, _p->getName());
	this->player->setPosition(_p->getSprite()->getPosition().x, _p->getSprite()->getPosition().y);
}


GameState::~GameState()
{
	delete this->player;
}


void GameState::updateInput(const float& _dt)
{
	timeSinceLastUpdate += _dt;
	float lastX;
	float lastY;

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT")))
	{
		lastX = this->player->getSprite()->getPosition().x;
		lastY = this->player->getSprite()->getPosition().y;

		this->player->move(-1.f, 0.f, _dt);
		//this->player->animate(timeSinceLastUpdate, timeBetweenUpdates, animationFighter.LeftAnimation, currentFrame);
	}
	else if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT")))
	{
		lastX = this->player->getSprite()->getPosition().x;
		lastY = this->player->getSprite()->getPosition().y;

		this->player->move(1.f, 0.f, _dt);
		//this->player->animate(timeSinceLastUpdate, timeBetweenUpdates, animationFighter.RightAnimation, currentFrame);
	}
	else if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_UP")))
	{
		lastX = this->player->getSprite()->getPosition().x;
		lastY = this->player->getSprite()->getPosition().y;

		this->player->move(0.f, -1.f, _dt);
		//this->player->animate(timeSinceLastUpdate, timeBetweenUpdates, animationFighter.BackAnimation, currentFrame);
	}
	else if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_DOWN")))
	{
		lastX = this->player->getSprite()->getPosition().x;
		lastY = this->player->getSprite()->getPosition().y;

		this->player->move(0.f, 1.f, _dt);
		//this->player->animate(timeSinceLastUpdate, timeBetweenUpdates, animationFighter.FrontAnimation, currentFrame);
	}


	if (sf::Keyboard::isKeyPressed(this->keybinds.at("CLOSE")))
	{
		this->states->push(new MenuState(this->window, this->supportedKeys, this->states, this->player));
	}


	sf::Sprite* spr = this->player->getSprite();
	this->setMainStageLimits(spr, lastX, lastY);
	this->player->setSprite(spr);
}

void GameState::update(const float& _dt)
{
	this->updateMousePositions();
	this->updateInput(_dt);

	this->player->update(_dt);
	std::string textString = "Position: X = " + std::to_string(this->getXPos(this->player->getSprite())) + ", Y = " + std::to_string(this->getYPos(this->player->getSprite()));
	text.setString(textString);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->player->render(target);


	target->draw(this->text);
}




void GameState::setMainStageLimits(sf::Sprite* sprite, float& lastx, float& lasty)
{
	if (getXPos(sprite) < 170)
	{
		sprite->setPosition(lastx, lasty);
	}
	if (getXPos(sprite) > 170 && getXPos(sprite) < 307 && getYPos(sprite) > 399)
	{
		sprite->setPosition(lastx, lasty);
	}
	if (getXPos(sprite) >= 170 && getXPos(sprite) < 300)
	{
		if (getYPos(sprite) < 360)
		{
			sprite->setPosition(lastx, lasty);
		}

		else if (getYPos(sprite) > 430)
		{
			sprite->setPosition(lastx, lasty);
		}
	}
	if (getXPos(sprite) >= 369 && getXPos(sprite) < 700)
	{


		if (getYPos(sprite) > 370)
		{
			sprite->setPosition(lastx, lasty);
		}
	}

	if (getXPos(sprite) >= 300 && getXPos(sprite) <= 370)
	{
		int marca = 300;
		int marca_y = 430;
		if (getXPos(sprite) < 351)
		{
			if (getYPos(sprite) < 350)
			{
				sprite->setPosition(lastx, lasty);
			}
		}
		//Parte de abajo con movilidad escalera
		if (getXPos(sprite) >= marca + 0 && getXPos(sprite) < marca + 5)
		{
			if (getYPos(sprite) > marca_y - 5)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 5 && getXPos(sprite) < marca + 10)
		{
			if (getYPos(sprite) > marca_y - 10)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 10 && getXPos(sprite) < marca + 15)
		{
			if (getYPos(sprite) > marca_y - 15)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 15 && getXPos(sprite) < marca + 20)
		{
			if (getYPos(sprite) > marca_y - 20)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 20 && getXPos(sprite) < marca + 25)
		{
			if (getYPos(sprite) > marca_y - 25)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 25 && getXPos(sprite) < marca + 30)
		{
			if (getYPos(sprite) > marca_y - 30)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 30 && getXPos(sprite) < marca + 35)
		{
			if (getYPos(sprite) > marca_y - 35)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 35 && getXPos(sprite) < marca + 40)
		{
			if (getYPos(sprite) > marca_y - 40)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 40 && getXPos(sprite) < marca + 45)
		{
			if (getYPos(sprite) > marca_y - 45)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 45 && getXPos(sprite) < marca + 50)
		{
			if (getYPos(sprite) > marca_y - 50)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 50 && getXPos(sprite) < marca + 55)
		{
			if (getYPos(sprite) > marca_y - 55)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

		else if (getXPos(sprite) >= marca + 55 && getXPos(sprite) <= marca + 75)
		{
			if (getYPos(sprite) > marca_y - 60)
			{
				sprite->setPosition(lastx, lasty);
			}
		}

	}

	if (getXPos(sprite) > 370 && getXPos(sprite) < 640)
	{
		if (getYPos(sprite) > 530)
		{
			sprite->setPosition(lastx, lasty);
		}
		//Parte de arriba del puente
		if (getXPos(sprite) >= 460 && getXPos(sprite) < 585)
		{
			{
				if (getYPos(sprite) > 370)
				{
					sprite->setPosition(lastx, lasty);
				}
				int marca = 460;
				int marca_y = 335;
				if (getXPos(sprite) >= marca + 0 && getXPos(sprite) < marca + 5)
				{
					if (getYPos(sprite) < marca_y - 5)
					{
						sprite->setPosition(lastx, lasty);
					}
				}

				else if (getXPos(sprite) >= marca + 5 && getXPos(sprite) < marca + 10)
				{
					if (getYPos(sprite) < marca_y - 10)
					{
						sprite->setPosition(lastx, lasty);
					}
				}
				else if (getXPos(sprite) >= marca + 10 && getXPos(sprite) < marca + 15)
				{
					if (getYPos(sprite) < marca_y - 15)
					{
						sprite->setPosition(lastx, lasty);
					}
				}
				else if (getXPos(sprite) >= marca + 15 && getXPos(sprite) < marca + 20)
				{
					if (getYPos(sprite) < marca_y - 20)
					{
						sprite->setPosition(lastx, lasty);
					}
				}
				else if (getXPos(sprite) >= marca + 20 && getXPos(sprite) < marca + 25)
				{
					if (getYPos(sprite) < marca_y - 25)
					{
						sprite->setPosition(lastx, lasty);
					}
				}
				else if (getXPos(sprite) >= marca + 25 && getXPos(sprite) < marca + 30)
				{
					if (getYPos(sprite) < marca_y - 30)
					{
						sprite->setPosition(lastx, lasty);
					}
				}
				else
				{
					if (getYPos(sprite) < marca_y - 35)
					{
						sprite->setPosition(lastx, lasty);
					}
				}
			}
		}

		else if (getXPos(sprite) >= 585 && getXPos(sprite) < 620)
		{
			int marca = 585;
			int marca_y = 335;

			if (getYPos(sprite) > 370)
			{
				sprite->setPosition(lastx, lasty);
			}

			if (getXPos(sprite) >= marca + 0 && getXPos(sprite) < marca + 5)
			{
				if (getYPos(sprite) < marca_y - 35)
				{
					sprite->setPosition(lastx, lasty);
				}
			}

			else if (getXPos(sprite) >= marca + 5 && getXPos(sprite) < marca + 10)
			{
				if (getYPos(sprite) < marca_y - 35 + 10)
				{
					sprite->setPosition(lastx, lasty);
				}
			}

			else if (getXPos(sprite) >= marca + 10 && getXPos(sprite) < marca + 15)
			{
				if (getYPos(sprite) < marca_y - 35 + 15)
				{
					sprite->setPosition(lastx, lasty);
				}
			}

			else if (getXPos(sprite) >= marca + 15 && getXPos(sprite) < marca + 20)
			{
				if (getYPos(sprite) < marca_y - 35 + 20)
				{
					sprite->setPosition(lastx, lasty);
				}
			}

			else if (getXPos(sprite) >= marca + 20 && getXPos(sprite) < marca + 25)
			{
				if (getYPos(sprite) < marca_y - 35 + 25)
				{
					sprite->setPosition(lastx, lasty);
				}
			}

			else if (getXPos(sprite) >= marca + 25 && getXPos(sprite) < marca + 30)
			{
				if (getYPos(sprite) < marca_y - 35 + 30)
				{
					sprite->setPosition(lastx, lasty);
				}
			}

			else if (getXPos(sprite) >= marca + 30 && getXPos(sprite) < marca + 35)
			{
				if (getYPos(sprite) < marca_y - 35 + 35)
				{
					sprite->setPosition(lastx, lasty);
				}
			}
		}


		else
		{
			if (getXPos(sprite) > 400)
			{
				if (getYPos(sprite) < 340)
				{
					sprite->setPosition(lastx, lasty);
				}
			}
			else if (getYPos(sprite) > 370)
			{
				sprite->setPosition(lastx, lasty);
			}
		}
	}

	if (getXPos(sprite) >= 330 && getXPos(sprite) <= 400 && getYPos(sprite) < 260)
	{
		sprite->setPosition(lastx, lasty);
	}

	if (getXPos(sprite) > 640 && getXPos(sprite) < 660)
	{
		if (getYPos(sprite) < 340)
		{
			sprite->setPosition(lastx, lasty);
		}
		if (getYPos(sprite) > 370)
		{
			sprite->setPosition(lastx, lasty);
		}
	}

	if (getXPos(sprite) >= 660)
	{
		if (getYPos(sprite) < 323)
		{
			sprite->setPosition(lastx, lasty);
		}
	}

	if (getXPos(sprite) > 860 && (getYPos(sprite) > 322 && getYPos(sprite) <= 331))
	{
		if (getXPos(sprite) > 934)
		{
			sprite->setPosition(lastx, lasty);
		}
	}

	if (getXPos(sprite) > 830 && (getYPos(sprite) > 350 && getYPos(sprite) <= 380))
	{
		sprite->setPosition(lastx, lasty);
	}

	if (getXPos(sprite) >= 710 && (getYPos(sprite) >= 330 && getYPos(sprite) <= 350))
	{
		sprite->setPosition(lastx, lasty);
	}

	if (getXPos(sprite) >= 660 && getXPos(sprite) <= 830 && (getYPos(sprite) > 370))
	{
		sprite->setPosition(lastx, lasty);
	}


}



