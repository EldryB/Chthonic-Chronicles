#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class CurrentStage
{
	MainStage,
	Combat,
	Lvl1R1,
	Lvl1R2,
	Lvl1R3,
	Lvl1R4,
	Lvl1R5,
	Lvl1R6,
	Lvl1R7,
	Lvl1R8,
	Lvl1R9
};

enum class CurrentState
{
	MainMenu,
	Game,
	PauseMenu,
	JobMenu,
	Fight,
	LostFight
};

struct Settings
{
	static const std::string ASSETS_PATH;
	static const std::string TEXTURES_PATH;

	static constexpr int WINDOW_WIDTH{ 1020 };
	static constexpr int WINDOW_HEIGHT{ 617 };
	static constexpr int VIRTUAL_WIDTH{ 1020 * 4 / 5 };
	static constexpr int VIRTUAL_HEIGHT{ 617 * 4 / 5 };
	static constexpr float MOVEMENT_SPEED{ 120.5f };
};

