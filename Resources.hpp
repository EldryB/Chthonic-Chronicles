#pragma once
#include <vector>
#include <tuple>
#include <string>

// Enum para identificar los tipos de recursos
enum class ResourceTypes
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
        int getResourceAmount(ResourceTypes resource) const;
        std::string getResourceName(ResourceTypes resource) const;

        // Método para cambiar la cantidad de un recurso
        void setResourceAmount(ResourceTypes resource, int amount);

        void unlockResource(ResourceTypes resource);
        void addResource(ResourceTypes resource, int amount);
        void subtractResource(ResourceTypes resource, int amount);

        // Método para imprimir los recursos desbloqueados
        void printResources() const;
};
