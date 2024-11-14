#include "JsonManagement.hpp"

void JsonManagement::toJson(nlohmann::json& _j, Player* _fighter)
{
    std::vector<std::tuple<std::string,int>> resources;
    for (size_t i = 0; i < static_cast<int>(ResourceTypes::count); i++)
    {
        resources.push_back(std::make_tuple(_fighter->getResourceName(static_cast<ResourceTypes>(i)),_fighter->getResourceAmoun(static_cast<ResourceTypes>(i))));
    }

    _j = nlohmann::json
    { 
        {"name", std::string{_fighter->getName()}}, 
        {"positionX", _fighter->getSprite()->getPosition().x}, 
        {"positionY", _fighter->getSprite()->getPosition().y},
        {"hp", _fighter->getHp() },
        {"damage", _fighter->getAttackPower() },
        {"initiative", _fighter->getInitiative() },
        {"defense", _fighter->getDefense()},
        {"villagers", _fighter->getVillagers()},
        {std::get<0>(resources[0]), std::get<1>(resources[0])},
        {std::get<0>(resources[1]), std::get<1>(resources[1])},
        {std::get<0>(resources[2]), std::get<1>(resources[2])},
        {std::get<0>(resources[3]), std::get<1>(resources[3])},
        {std::get<0>(resources[4]), std::get<1>(resources[4])},
        {std::get<0>(resources[5]), std::get<1>(resources[5])},
        {std::get<0>(resources[6]), std::get<1>(resources[6])},
        {std::get<0>(resources[7]), std::get<1>(resources[7])},
        {std::get<0>(resources[8]), std::get<1>(resources[8])},
        {std::get<0>(resources[9]), std::get<1>(resources[9])}
    };


}

void JsonManagement::fromJson(nlohmann::json& _j, Player* _fighter)
{
    float posX = _j.at("positionX").get<float>();
    float posY = _j.at("positionY").get<float>();
    float _hp = _j.at("hp").get<float>();
    float _damage = _j.at("damage").get<float>();
    int _init = _j.at("initiative").get<int>();
    int _defense = _j.at("defense").get<int>();
    int _villagers = _j.at("villagers").get<int>();
    std::string _name = _j.at("name").get<std::string>();
    for (int i = 0; i < static_cast<int>(ResourceTypes::count); i++)
    {
        std::string str = _fighter->getResourceName(static_cast<ResourceTypes>(i));
        int num = _j.at(str).get<int>();
        _fighter->setResourceAmoun(static_cast<ResourceTypes>(i),num);
    }
    _fighter->setAttributes(_name, posX, posY, _hp, _damage, _init, _defense, _villagers);
}

void JsonManagement::savePlayerToFile(Player* _fighter, const std::string& filename)
{
    nlohmann::json _j;
    toJson(_j, _fighter);
    std::ofstream file(filename);
    if (file.is_open())
    {
        file << _j.dump(4);  // Escribe el JSON en el archivo con indentación de 4 espacios
        file.close();
    }
    else
    {
        std::cerr << "Error al abrir el archivo para guardar\n";
    }
}

void JsonManagement::loadPlayerFromFile(const std::string& filename, Player* _fighter)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        nlohmann::json _j;
        file >> _j;  // Lee el contenido del archivo en un objeto JSON
        file.close();
        fromJson(_j, _fighter);
    }
    else
    {
        std::cerr << "Error al abrir el archivo para cargar\n";
    }
}
