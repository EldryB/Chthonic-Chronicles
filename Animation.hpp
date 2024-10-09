#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Main_Animation
{
	std::vector<sf::Texture> RightAnimation;
	std::vector<sf::Texture> LeftAnimation;
	std::vector<sf::Texture> FrontAnimation;
	std::vector<sf::Texture> BackAnimation;
};



struct Animation_enemy
{
	std::vector<sf::Texture> AttackAnimation;
};

enum class Look
{
	look_up,
	look_down,
	look_left,
	look_right
};