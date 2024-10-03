#include <stdexcept> 
#include <settings.hpp>
#include <animation.hpp>
#include <iostream>

const std::string Settings::ASSETS_PATH{"assets"};
const std::string Settings::TEXTURES_PATH{"assets/textures"};

std::unordered_map<std::string,sf::Texture> Settings::textures{};

void Settings::init(std::vector<sf::Texture>& _M)
{
	Settings::load_textures();
	Settings::load_monster1(_M);
}

void Settings::load_monster1(std::vector<sf::Texture>& _A)
{
	_A.push_back(Settings::textures["Monster1_at1"]);
	_A.push_back(Settings::textures["Monster1_at2"]);
	_A.push_back(Settings::textures["Monster1_at3"]);
	_A.push_back(Settings::textures["Monster1_at4"]);
}

void Settings::load_textures()
{
	sf::Texture texture{};

	if (!texture.loadFromFile("assets/textures/right1.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Right1"] = texture;

	if (!texture.loadFromFile("assets/textures/right2.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Right2"] = texture;

	if (!texture.loadFromFile("assets/textures/right3.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Right3"] = texture;

	//frente
	if (!texture.loadFromFile("assets/textures/front1.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Front1"] = texture;

	if (!texture.loadFromFile("assets/textures/front2.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Front2"] = texture;

	if (!texture.loadFromFile("assets/textures/front3.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Front3"] = texture;


	if (!texture.loadFromFile("assets/textures/left1.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Left1"] = texture;

	if (!texture.loadFromFile("assets/textures/left2.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Left2"] = texture;

	if (!texture.loadFromFile("assets/textures/left3.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Left3"] = texture;


	if (!texture.loadFromFile("assets/textures/back1.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Back1"] = texture;


	if (!texture.loadFromFile("assets/textures/back2.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Back2"] = texture;


	if (!texture.loadFromFile("assets/textures/back3.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Back3"] = texture;

	if (!texture.loadFromFile("assets/textures/enemy_1/standing.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Monster1_stand"] = texture;

	if (!texture.loadFromFile("assets/textures/enemy_1/at1.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Monster1_at1"] = texture;

	if (!texture.loadFromFile("assets/textures/enemy_1/at2.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Monster1_at2"] = texture;

	if (!texture.loadFromFile("assets/textures/enemy_1/at3.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Monster1_at3"] = texture;

	if (!texture.loadFromFile("assets/textures/enemy_1/at4.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Monster1_at4"] = texture;

	if (!texture.loadFromFile("assets/textures/enemy_1/dead.png"))
	{
		std::cerr << "Error loading image" << std::endl;
		return;
	}
	Settings::textures["Monster1_dead"] = texture;

}

void Settings::load_frames(std::vector<sf::Texture>& _AnimationRight, std::vector<sf::Texture>& _AnimationLeft, std::vector<sf::Texture>& _AnimationFront, std::vector<sf::Texture>& _AnimationBack)
{
	_AnimationRight.push_back(Settings::textures["Right1"]);
	_AnimationRight.push_back(Settings::textures["Right2"]);
	_AnimationRight.push_back(Settings::textures["Right3"]);
	_AnimationRight.push_back(Settings::textures["Right2"]);
	_AnimationLeft.push_back(Settings::textures["Left1"]);
	_AnimationLeft.push_back(Settings::textures["Left2"]);
	_AnimationLeft.push_back(Settings::textures["Left3"]);
	_AnimationLeft.push_back(Settings::textures["Left2"]);
	_AnimationFront.push_back(Settings::textures["Front1"]);
	_AnimationFront.push_back(Settings::textures["Front2"]);
	_AnimationFront.push_back(Settings::textures["Front3"]);
	_AnimationFront.push_back(Settings::textures["Front2"]);
	_AnimationBack.push_back(Settings::textures["Back1"]);
	_AnimationBack.push_back(Settings::textures["Back2"]);
	_AnimationBack.push_back(Settings::textures["Back3"]);
	_AnimationBack.push_back(Settings::textures["Back2"]);

}

float Settings::pos_x(sf::Sprite& spr)
{
	return spr.getPosition().x;
}

float Settings::pos_y(sf::Sprite& spr)
{
	return spr.getPosition().y;
}

void Settings::set_x(float _x, sf::Sprite& sprite)
{
	float _y = sprite.getPosition().y;
	sprite.setPosition(_x, _y);
}
void Settings::set_y(float _y, sf::Sprite& sprite) 
{
	float _x = sprite.getPosition().x;
	sprite.setPosition(_x, _y);
}

void Settings::limit_principal_map(sf::Sprite& sprite)
{
	float ancho = Settings::CHARACTER_WIDTH;
	float alto = Settings::CHARACTER_HEIGHT;

	if (pos_x(sprite) < 160)
	{
		set_x(160 , sprite);
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


