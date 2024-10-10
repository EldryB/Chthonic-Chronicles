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
        int get_resource(Types_of_resources resource) const;
        void unlock_resource(Types_of_resources resource);
        void add_resource(Types_of_resources resource, int amount);
        void subtract_resource(Types_of_resources resource, int amount);

        // Método para imprimir los recursos desbloqueados
        void print_resources() const;
};
