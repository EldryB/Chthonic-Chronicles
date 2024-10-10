#include "resources.hpp"
#include <iostream>
#include <stdexcept>

// Constructor que inicializa todos los recursos a -1 (bloqueado)
Resources::Resources()
{
    resources = {
        {"Coin", -1},
        {"Wheat", -1},
        {"Bread", -1},
        {"Leather", -1},
        {"Cloth", -1},
        {"Silk", -1},
        {"Stone", -1},
        {"Wood", -1},
        {"Iron", -1},
        {"Gold", -1}
    };
}

// Método para obtener la cantidad de un recurso
int Resources::get_resource(Types_of_resources resource) const
{
    return std::get<1>(resources[static_cast<int>(resource)]);
}

// Método para desbloquear un recurso (si está bloqueado, lo establece en 0)
void Resources::unlock_resource(Types_of_resources resource)
{
    if (std::get<1>(resources[static_cast<int>(resource)]) == -1)
    {
        std::get<1>(resources[static_cast<int>(resource)]) = 0;
    }
}

// Método para agregar a la cantidad de un recurso
void Resources::add_resource(Types_of_resources resource, int amount)
{
    if (amount < 0)
    {
        throw std::invalid_argument("No se puede agregar una cantidad negativa.");
    }        
    int &current_amount = std::get<1>(resources[static_cast<int>(resource)]);
    
    current_amount += amount;
}

// Método para restar a la cantidad de un recurso
void Resources::subtract_resource(Types_of_resources resource, int amount)
{
    if (amount < 0)
    {
        throw std::invalid_argument("No se puede restar una cantidad negativa.");
    }
    int &current_amount = std::get<1>(resources[static_cast<int>(resource)]);
    
    // No permitir que baje de 0
    if (current_amount < amount)
    {
        current_amount = 0;
    }
    else
    {
        current_amount -= amount;
    }
}

// Método para imprimir los recursos desbloqueados y sus cantidades
void Resources::print_resources() const
{
    for (const auto& resource : resources)
    {
        const std::string& name = std::get<0>(resource);
        int amount = std::get<1>(resource);

        // Solo imprimimos los recursos desbloqueados (>= 0)
        if (amount >= 0)
        {
            std::cout << name << ": " << amount << std::endl;
        }
    }
}
