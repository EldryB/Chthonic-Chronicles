#pragma once

#include "nlohmann/json.hpp"
#include "Fighter.hpp"
#include <fstream>

class JsonManagement
{
public:

	void toJson(nlohmann::json& _j, Fighter* _fighter);

	void fromJson(nlohmann::json& j, Fighter* _fighter);

	void savePlayerToFile(Fighter* _fighter, const std::string& filename);

	void loadPlayerFromFile(const std::string& filename, Fighter* _fighter);




private:


};

