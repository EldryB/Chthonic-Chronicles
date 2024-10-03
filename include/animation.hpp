#pragma once
#include <SFML/Graphics.hpp>
#include <settings.hpp>
#include <vector>

struct Animation
{
	 std::vector<sf::Texture> RightAnimation;
	 std::vector<sf::Texture> LeftAnimation;
	 std::vector<sf::Texture> FrontAnimation;
	 std::vector<sf::Texture> BackAnimation;
};

struct Attack_animation
{
	std::vector<sf::Texture> AttackAnimation;
};
