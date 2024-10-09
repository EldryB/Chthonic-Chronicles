#include "GameState.hpp"

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
	this->texture.loadFromFile("assets/textures/mainStage.png");
	this->textures["MainStage"] = this->texture;

	this->texture.loadFromFile("assets/textures/right1.png");
	this->textures["Right1"] = this->texture;

	this->texture.loadFromFile("assets/textures/right2.png");
	this->textures["Right2"] = this->texture;

	this->texture.loadFromFile("assets/textures/right3.png");
	this->textures["Right3"] = this->texture;

	this->texture.loadFromFile("assets/textures/left1.png");
	this->textures["Left1"] = this->texture;

	this->texture.loadFromFile("assets/textures/left2.png");
	this->textures["Left2"] = this->texture;

	this->texture.loadFromFile("assets/textures/left3.png");
	this->textures["Left3"] = this->texture;

	this->texture.loadFromFile("assets/textures/front1.png");
	this->textures["Front1"] = this->texture;

	this->texture.loadFromFile("assets/textures/front2.png");
	this->textures["Front2"] = this->texture;

	this->texture.loadFromFile("assets/textures/front3.png");
	this->textures["Front3"] = this->texture;

	this->texture.loadFromFile("assets/textures/back1.png");
	this->textures["Back1"] = this->texture;

	this->texture.loadFromFile("assets/textures/back2.png");
	this->textures["Back2"] = this->texture;

	this->texture.loadFromFile("assets/textures/back3.png");
	this->textures["Back3"] = this->texture;
}

void GameState::initBackground()
{
	this->background.setTexture(this->textures["MainStage"]);
	this->background.setScale(float(Settings::WINDOW_WIDTH) / float(Settings::VIRTUAL_WIDTH), float(Settings::WINDOW_HEIGHT) / float(Settings::VIRTUAL_HEIGHT));
}

void GameState::initCharacterFrames()
{
	this->animationEntity.RightAnimation.push_back(this->textures["Right1"]);
	this->animationEntity.RightAnimation.push_back(this->textures["Right2"]);
	this->animationEntity.RightAnimation.push_back(this->textures["Right2"]);
	this->animationEntity.RightAnimation.push_back(this->textures["Right3"]);

	
	this->animationEntity.LeftAnimation.push_back(this->textures["Left1"]);
	this->animationEntity.LeftAnimation.push_back(this->textures["Left2"]);
	this->animationEntity.LeftAnimation.push_back(this->textures["Left2"]);
	this->animationEntity.LeftAnimation.push_back(this->textures["Left3"]);


	this->animationEntity.FrontAnimation.push_back(this->textures["Front1"]);
	this->animationEntity.FrontAnimation.push_back(this->textures["Front2"]);
	this->animationEntity.FrontAnimation.push_back(this->textures["Front2"]);
	this->animationEntity.FrontAnimation.push_back(this->textures["Front3"]);


	this->animationEntity.BackAnimation.push_back(this->textures["Back1"]);
	this->animationEntity.BackAnimation.push_back(this->textures["Back2"]);
	this->animationEntity.BackAnimation.push_back(this->textures["Back2"]);
	this->animationEntity.BackAnimation.push_back(this->textures["Back3"]);
}


float GameState::pos_x(sf::Sprite& spr)
{
	return spr.getPosition().x;
}

float GameState::pos_y(sf::Sprite& spr)
{
	return spr.getPosition().y;
}

void GameState::set_x(float _x, sf::Sprite& sprite)
{
	float _y = sprite.getPosition().y;
	sprite.setPosition(_x, _y);
}
void GameState::set_y(float _y, sf::Sprite& sprite)
{
	float _x = sprite.getPosition().x;
	sprite.setPosition(_x, _y);
}

void GameState::limitMainBackground(sf::Sprite& sprite)
{
	if (pos_x(sprite) < 160)
	{
		set_x(160, sprite);
	}
	if (pos_x(sprite) >= 160 && pos_x(sprite) < 230)
	{
		if (pos_y(sprite) < 280)
		{
			set_y(280, sprite);
		}

		else if (pos_y(sprite) > 325)
		{
			set_y(325, sprite);
		}
	}

	if (pos_x(sprite) >= 230 && pos_x(sprite) <= 275)
	{
		int marca = 230;
		int marca_y = 335;
		if (pos_y(sprite) < 270)
		{
			set_y(270, sprite);
		}
		//Parte de abajo con movilidad escalera
		if (pos_x(sprite) >= marca + 0 && pos_x(sprite) < marca + 5)
		{
			if (pos_y(sprite) > marca_y - 5)
			{
				set_y(marca_y - 5, sprite);
			}
		}

		else if (pos_x(sprite) >= marca + 5 && pos_x(sprite) < marca + 10)
		{
			if (pos_y(sprite) > marca_y - 10)
			{
				set_y(marca_y - 10, sprite);
			}
		}

		else if (pos_x(sprite) >= marca + 10 && pos_x(sprite) < marca + 15)
		{
			if (pos_y(sprite) > marca_y - 15)
			{
				set_y(marca_y - 15, sprite);
			}
		}

		else if (pos_x(sprite) >= marca + 15 && pos_x(sprite) < marca + 20)
		{
			if (pos_y(sprite) > marca_y - 20)
			{
				set_y(marca_y - 20, sprite);
			}
		}

		else if (pos_x(sprite) >= marca + 20 && pos_x(sprite) < marca + 25)
		{
			if (pos_y(sprite) > marca_y - 25)
			{
				set_y(marca_y - 25, sprite);
			}
		}

		else if (pos_x(sprite) >= marca + 25 && pos_x(sprite) < marca + 30)
		{
			if (pos_y(sprite) > marca_y - 30)
			{
				set_y(marca_y - 30, sprite);
			}
		}

		else if (pos_x(sprite) >= marca + 30 && pos_x(sprite) < marca + 35)
		{
			if (pos_y(sprite) > marca_y - 35)
			{
				set_y(marca_y - 35, sprite);
			}
		}

		else if (pos_x(sprite) >= marca + 35 && pos_x(sprite) < marca + 40)
		{
			if (pos_y(sprite) > marca_y - 40)
			{
				set_y(marca_y - 40, sprite);
			}
		}

		else if (pos_x(sprite) >= marca + 40 && pos_x(sprite) <= marca + 45)
		{
			if (pos_y(sprite) > marca_y - 45)
			{
				set_y(marca_y - 45, sprite);
			}
		}
	}

	if (pos_x(sprite) > 275 && pos_x(sprite) < 505)
	{
		if (pos_y(sprite) > 290)
		{
			set_y(290, sprite);
		}
		//Parte de arriba del puente
		if (pos_x(sprite) >= 365 && pos_x(sprite) < 470)
		{
			{
				if (pos_x(sprite) >= 365 + 0 && pos_x(sprite) < 365 + 5)
				{
					if (pos_y(sprite) < 265 - 5)
					{
						set_y(265 - 5, sprite);
					}
				}

				else if (pos_x(sprite) >= 365 + 5 && pos_x(sprite) < 365 + 10)
				{
					if (pos_y(sprite) < 265 - 10)
					{
						set_y(265 - 10, sprite);
					}
				}
				else if (pos_x(sprite) >= 365 + 10 && pos_x(sprite) < 365 + 15)
				{
					if (pos_y(sprite) < 265 - 15)
					{
						set_y(265 - 15, sprite);
					}
				}
				else if (pos_x(sprite) >= 365 + 15 && pos_x(sprite) < 365 + 20)
				{
					if (pos_y(sprite) < 265 - 20)
					{
						set_y(265 - 20, sprite);
					}
				}
				else if (pos_x(sprite) >= 365 + 20 && pos_x(sprite) < 365 + 25)
				{
					if (pos_y(sprite) < 265 - 25)
					{
						set_y(265 - 25, sprite);
					}
				}
				else if (pos_x(sprite) >= 365 + 25 && pos_x(sprite) < 365 + 30)
				{
					if (pos_y(sprite) < 265 - 30)
					{
						set_y(265 - 30, sprite);
					}
				}
				else
				{
					if (pos_y(sprite) < 265 - 35)
					{
						set_y(265 - 35, sprite);
					}
				}
			}
		}

		else if (pos_x(sprite) >= 470 && pos_x(sprite) < 505)
		{
			if (pos_x(sprite) >= 470 + 0 && pos_x(sprite) < 470 + 5)
			{
				if (pos_y(sprite) < 265 - 35 + 5)
				{
					set_y(265 - 35 + 5, sprite);
				}
			}

			else if (pos_x(sprite) >= 470 + 5 && pos_x(sprite) < 470 + 10)
			{
				if (pos_y(sprite) < 265 - 35 + 10)
				{
					set_y(265 - 35 + 10, sprite);
				}
			}

			else if (pos_x(sprite) >= 470 + 10 && pos_x(sprite) < 470 + 15)
			{
				if (pos_y(sprite) < 265 - 35 + 15)
				{
					set_y(265 - 35 + 15, sprite);
				}
			}

			else if (pos_x(sprite) >= 470 + 15 && pos_x(sprite) < 470 + 20)
			{
				if (pos_y(sprite) < 265 - 35 + 20)
				{
					set_y(265 - 35 + 20, sprite);
				}
			}

			else if (pos_x(sprite) >= 470 + 20 && pos_x(sprite) < 470 + 25)
			{
				if (pos_y(sprite) < 265 - 35 + 25)
				{
					set_y(265 - 35 + 25, sprite);
				}
			}

			else if (pos_x(sprite) >= 470 + 25 && pos_x(sprite) < 470 + 30)
			{
				if (pos_y(sprite) < 265 - 35 + 30)
				{
					set_y(265 - 35 + 30, sprite);
				}
			}

			else if (pos_x(sprite) >= 470 + 30 && pos_x(sprite) < 470 + 35)
			{
				if (pos_y(sprite) < 265 - 35 + 35)
				{
					set_y(265 - 35 + 35, sprite);
				}
			}
		}


		else
		{
			if (pos_y(sprite) < 265)
			{
				set_y(265, sprite);
			}
			else if (pos_y(sprite) > 290)
			{
				set_y(290, sprite);
			}
		}
	}


	if (pos_x(sprite) >= 505 && pos_x(sprite) <= 572)
	{
		if (pos_y(sprite) < 276)
		{
			set_y(276, sprite);
		}
		else if (pos_y(sprite) > 290)
		{
			set_y(290, sprite);
		}
	}
	if (pos_x(sprite) > 572)
	{
		set_x(572, sprite);
	}
}

GameState::GameState(sf::RenderWindow* _window, std::unordered_map<std::string, sf::Keyboard::Key>* _supportedKeys, std::stack<State*>* _states)
	: State(_window, _supportedKeys, _states)
{
	this->initTextures();
	this->initBackground();
	this->initCharacterFrames();
	this->initKeybinds();

	float x = 200.f;
	float y = 500.f;
	this->player.setPosition(x, y);    
	this->currentFrame = 0;
	this->timeSinceLastUpdate = 0.0f;
	this->timeBetweenUpdates = 0.08f;
}

GameState::~GameState()
{

}

void GameState::updateInput(const float& _dt)
{
	timeSinceLastUpdate += _dt;

	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_LEFT")))
	{
		this->player.move(_dt, -1.f, 0.f);
		this->player.animation(timeSinceLastUpdate,timeBetweenUpdates, animationEntity.LeftAnimation, currentFrame);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_RIGHT")))
	{
		this->player.move(_dt, 1.f, 0.f);
		this->player.animation(timeSinceLastUpdate, timeBetweenUpdates, animationEntity.RightAnimation, currentFrame);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_UP")))
	{
		this->player.move(_dt, 0.f, -1.f);
		this->player.animation(timeSinceLastUpdate, timeBetweenUpdates, animationEntity.BackAnimation, currentFrame);
	}
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("MOVE_DOWN")))
	{
		this->player.move(_dt, 0.f, 1.f);
		this->player.animation(timeSinceLastUpdate, timeBetweenUpdates, animationEntity.FrontAnimation, currentFrame);
	}
	
	if (sf::Keyboard::isKeyPressed(this->keybinds.at("CLOSE")))
	{
		this->endState();
	}
	
	sf::Sprite spr = this->player.get_sprite();
	this->limitMainBackground(spr);
	this->player.setSprite(spr);
	
}

void GameState::update(const float& _dt)
{
	this->updateMousePositions();
	this->updateInput(_dt);

	this->player.update(_dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->player.render(target);
}
