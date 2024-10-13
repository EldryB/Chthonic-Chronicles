#pragma once

#include <vector>
#include <stack>
#include <unordered_map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct Settings
{
	static const std::string ASSETS_PATH;
	static const std::string TEXTURES_PATH;

	static constexpr int WINDOW_WIDTH{ 1080 };
	static constexpr int WINDOW_HEIGHT{ 617 };
	static constexpr int VIRTUAL_WIDTH{ 1080 * 4 / 5 };
	static constexpr int VIRTUAL_HEIGHT{ 617 * 4 / 5 };
	static constexpr float ENTITY_WIDTH{ 46.f };
	static constexpr float ENTITY_HEIGHT{ 46.f };
	static constexpr float MOVEMENT_SPEED{ 160.5f };


};

