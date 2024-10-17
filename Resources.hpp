#pragma once
#include <vector>
#include <tuple>
#include <string>

// Enum para identificar los tipos de recursos
enum class Types_of_resources
{
    coin,
    wheat,
    bread,
    leather,
    cloth,
    silk,
    stone,
    wood,
    iron,
    gold,
    COUNT
};

// Clase Resources que gestiona un vector de recursos
class Resources
{
    private:
        // Un vector que almacena tuplas de <nombre, cantidad>
        std::vector<std::tuple<std::string, int>> resources;

    public:
        // Constructor
        Resources();

        // Métodos para acceder a los recursos
        int getResourceAmount(Types_of_resources resource) const;
        std::string getResourceName(Types_of_resources resource) const;

        // Método para cambiar la cantidad de un recurso
        void Resources::setResourceAmount(Types_of_resources resource, int amount);

        void unlockResource(Types_of_resources resource);
        void addResource(Types_of_resources resource, int amount);
        void subtractResource(Types_of_resources resource, int amount);

        // Método para imprimir los recursos desbloqueados
        void printResources() const;
};
