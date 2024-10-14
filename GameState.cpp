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
	this->player = new Fighter(200.f, 500.f, this->textures["Right2"], "Player");
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



float GameState::getXPos(sf::Sprite spr)
{
	return spr.getPosition().x;
}

float GameState::getYPos(sf::Sprite spr)
{
	return spr.getPosition().y;
}

void GameState::setXPos(float _x, sf::Sprite& sprite)
{
	float _y = sprite.getPosition().y;
	sprite.setPosition(_x, _y);
}
void GameState::setYPos(float _y, sf::Sprite& sprite)
{
	float _x = sprite.getPosition().x;
	sprite.setPosition(_x, _y);
}





void GameState::setMainStageLimits(sf::Sprite& sprite)
{
	if (getXPos(sprite) < 205)
	{
		setXPos(205, sprite);
	}
	if (getXPos(sprite) >= 205 && getXPos(sprite) < 300)
	{
		if (getYPos(sprite) < 360)
		{
			setYPos(360, sprite);
		}

		else if (getYPos(sprite) > 430)
		{
			setYPos(430, sprite);
		}
	}

	if (getXPos(sprite) >= 300 && getXPos(sprite) <= 370)
	{
		int marca = 300;
		int marca_y = 430;
		if (getYPos(sprite) < 350)
		{
			setYPos(350, sprite);
		}
		//Parte de abajo con movilidad escalera
		if (getXPos(sprite) >= marca + 0 && getXPos(sprite) < marca + 5)
		{
			if (getYPos(sprite) > marca_y - 5)
			{
				setYPos(marca_y - 5, sprite);
			}
		}

		else if (getXPos(sprite) >= marca + 5 && getXPos(sprite) < marca + 10)
		{
			if (getYPos(sprite) > marca_y - 10)
			{
				setYPos(marca_y - 10, sprite);
			}
		}

		else if (getXPos(sprite) >= marca + 10 && getXPos(sprite) < marca + 15)
		{
			if (getYPos(sprite) > marca_y - 15)
			{
				setYPos(marca_y - 15, sprite);
			}
		}

		else if (getXPos(sprite) >= marca + 15 && getXPos(sprite) < marca + 20)
		{
			if (getYPos(sprite) > marca_y - 20)
			{
				setYPos(marca_y - 20, sprite);
			}
		}

		else if (getXPos(sprite) >= marca + 20 && getXPos(sprite) < marca + 25)
		{
			if (getYPos(sprite) > marca_y - 25)
			{
				setYPos(marca_y - 25, sprite);
			}
		}

		else if (getXPos(sprite) >= marca + 25 && getXPos(sprite) < marca + 30)
		{
			if (getYPos(sprite) > marca_y - 30)
			{
				setYPos(marca_y - 30, sprite);
			}
		}

		else if (getXPos(sprite) >= marca + 30 && getXPos(sprite) < marca + 35)
		{
			if (getYPos(sprite) > marca_y - 35)
			{
				setYPos(marca_y - 35, sprite);
			}
		}

		else if (getXPos(sprite) >= marca + 35 && getXPos(sprite) < marca + 40)
		{
			if (getYPos(sprite) > marca_y - 40)
			{
				setYPos(marca_y - 40, sprite);
			}
		}

		else if (getXPos(sprite) >= marca + 40 && getXPos(sprite) < marca + 45)
		{
			if (getYPos(sprite) > marca_y - 45)
			{
				setYPos(marca_y - 45, sprite);
			}
		}

		else if (getXPos(sprite) >= marca + 45 && getXPos(sprite) < marca + 50)
		{
			if (getYPos(sprite) > marca_y - 50)
			{
				setYPos(marca_y - 50, sprite);
			}
		}

		else if (getXPos(sprite) >= marca + 50 && getXPos(sprite) < marca + 55)
		{
			if (getYPos(sprite) > marca_y - 55)
			{
				setYPos(marca_y - 55, sprite);
			}
		}

		else if (getXPos(sprite) >= marca + 55 && getXPos(sprite) <= marca + 75)
		{
			if (getYPos(sprite) > marca_y - 60)
			{
				setYPos(marca_y - 60, sprite);
			}
		}

	}

	if (getXPos(sprite) > 370 && getXPos(sprite) < 640)
	{
		if (getYPos(sprite) > 530)
		{
			setYPos(530, sprite);
		}
		//Parte de arriba del puente
		if (getXPos(sprite) >= 460 && getXPos(sprite) < 585)
		{
			{
				if (getYPos(sprite) > 370)
				{
					setYPos(370, sprite);
				}
				int marca = 460;
				int marca_y = 335;
				if (getXPos(sprite) >= marca + 0 && getXPos(sprite) < marca + 5)
				{
					if (getYPos(sprite) < marca_y - 5)
					{
						setYPos(marca_y - 5, sprite);
					}
				}

				else if (getXPos(sprite) >= marca + 5 && getXPos(sprite) < marca + 10)
				{
					if (getYPos(sprite) < marca_y - 10)
					{
						setYPos(marca_y - 10, sprite);
					}
				}
				else if (getXPos(sprite) >= marca + 10 && getXPos(sprite) < marca + 15)
				{
					if (getYPos(sprite) < marca_y - 15)
					{
						setYPos(marca_y - 15, sprite);
					}
				}
				else if (getXPos(sprite) >= marca + 15 && getXPos(sprite) < marca + 20)
				{
					if (getYPos(sprite) < marca_y - 20)
					{
						setYPos(marca_y - 20, sprite);
					}
				}
				else if (getXPos(sprite) >= marca + 20 && getXPos(sprite) < marca + 25)
				{
					if (getYPos(sprite) < marca_y - 25)
					{
						setYPos(marca_y - 25, sprite);
					}
				}
				else if (getXPos(sprite) >= marca + 25 && getXPos(sprite) < marca + 30)
				{
					if (getYPos(sprite) < marca_y - 30)
					{
						setYPos(marca_y - 30, sprite);
					}
				}
				else
				{
					if (getYPos(sprite) < marca_y - 35)
					{
						setYPos(marca_y - 35, sprite);
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
				setYPos(370, sprite);
			}

			if (getXPos(sprite) >= marca + 0 && getXPos(sprite) < marca + 5)
			{
				if (getYPos(sprite) < marca_y - 35)
				{
					setYPos(marca_y - 35, sprite);
				}
			}

			else if (getXPos(sprite) >= marca + 5 && getXPos(sprite) < marca + 10)
			{
				if (getYPos(sprite) < marca_y - 35 + 10)
				{
					setYPos(marca_y - 35 + 10, sprite);
				}
			}

			else if (getXPos(sprite) >= marca + 10 && getXPos(sprite) < marca + 15)
			{
				if (getYPos(sprite) < marca_y - 35 + 15)
				{
					setYPos(marca_y - 35 + 15, sprite);
				}
			}

			else if (getXPos(sprite) >= marca + 15 && getXPos(sprite) < marca + 20)
			{
				if (getYPos(sprite) < marca_y - 35 + 20)
				{
					setYPos(marca_y - 35 + 20, sprite);
				}
			}

			else if (getXPos(sprite) >= marca + 20 && getXPos(sprite) < marca + 25)
			{
				if (getYPos(sprite) < marca_y - 35 + 25)
				{
					setYPos(marca_y - 35 + 25, sprite);
				}
			}

			else if (getXPos(sprite) >= marca + 25 && getXPos(sprite) < marca + 30)
			{
				if (getYPos(sprite) < marca_y - 35 + 30)
				{
					setYPos(marca_y - 35 + 30, sprite);
				}
			}

			else if (getXPos(sprite) >= marca + 30 && getXPos(sprite) < marca + 35)
			{
				if (getYPos(sprite) < marca_y - 35 + 35)
				{
					setYPos(marca_y - 35 + 35, sprite);
				}
			}
		}


		else
		{
			if (getYPos(sprite) < 340)
			{
				setYPos(340, sprite);
			}
			else if (getYPos(sprite) > 370)
			{
				setYPos(370, sprite);
			}
		}
	}


	if (getXPos(sprite) >= 640 && getXPos(sprite) <= 786.0f)
	{
		if (getYPos(sprite) < 352)
		{
			setYPos(352, sprite);
		}
		else if (getYPos(sprite) > 370)
		{
			setYPos(370, sprite);
		}
	}
	if (getXPos(sprite) > 785)
	{
		setXPos(785, sprite);
	}
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

GameState::~GameState()
{
	delete this->player;
}


void GameState::updateInput(const float& _dt)
{
	timeSinceLastUpdate += _dt;


	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT")))
	{
		this->player->move(_dt, -1.f, 0.f);
		this->player->animate(timeSinceLastUpdate,timeBetweenUpdates, animationFighter.LeftAnimation, currentFrame);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT")))
	{
		this->player->move(_dt, 1.f, 0.f);
		this->player->animate(timeSinceLastUpdate, timeBetweenUpdates, animationFighter.RightAnimation, currentFrame);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_UP")))
	{
		this->player->move(_dt, 0.f, -1.f);
		this->player->animate(timeSinceLastUpdate, timeBetweenUpdates, animationFighter.BackAnimation, currentFrame);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_DOWN")))
	{
		this->player->move(_dt, 0.f, 1.f);
		this->player->animate(timeSinceLastUpdate, timeBetweenUpdates, animationFighter.FrontAnimation, currentFrame);
	}

	
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("CLOSE")))
	{
		this->states->push(new MenuState(this->window, this->supportedKeys, this->states));
	}
	
	this->setMainStageLimits(this->player->getSprite());
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
