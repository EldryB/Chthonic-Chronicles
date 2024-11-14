#pragma once

#include "nlohmann/json.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include <fstream>

class JsonManagement
{
public:

	void toJson(nlohmann::json& _j, Player* _fighter);

	void fromJson(nlohmann::json& j, Player* _fighter);

	void savePlayerToFile(Player* _fighter, const std::string& filename);

	void loadPlayerFromFile(const std::string& filename, Player* _fighter);




private:


};

