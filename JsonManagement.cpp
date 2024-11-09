#include "JsonManagement.hpp"

void JsonManagement::toJson(nlohmann::json& _j, Fighter* _fighter)
{
    _j = nlohmann::json
    { 
        {"name", std::string{_fighter->getName()}}, 
        {"positionX", _fighter->getSprite()->getPosition().x}, 
        {"positionY", _fighter->getSprite()->getPosition().y},
        {"hp", _fighter->getHp() },
        {"damage", _fighter->getAttackPower() }
    
    };
}

void JsonManagement::fromJson(nlohmann::json& _j, Fighter* _fighter)
{
    float posX = _j.at("positionX").get<float>();
    float posY = _j.at("positionY").get<float>();
    float _hp = _j.at("hp").get<float>();
    float _damage = _j.at("damage").get<float>();
    std::string _name = _j.at("name").get<std::string>();

    _fighter->setAttributes(posX, posY, _name, _hp, _damage);

}

void JsonManagement::savePlayerToFile(Fighter* _fighter, const std::string& filename)
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

void JsonManagement::loadPlayerFromFile(const std::string& filename, Fighter* _fighter)
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
