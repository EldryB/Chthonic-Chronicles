#include "Resources.hpp"
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
int Resources::getResourceAmount(Types_of_resources resource) const
{
    return std::get<1>(resources[static_cast<int>(resource)]);
}

// Método para obtener el nombre de un recurso
std::string Resources::getResourceName(Types_of_resources resource) const
{
    return std::get<0>(resources[static_cast<int>(resource)]);
}

// Método para cambiar la cantidad de un recurso
void Resources::setResourceAmount(Types_of_resources resource, int amount)
{
    std::get<1>(resources[static_cast<int>(resource)]) = amount;
}

// Método para desbloquear un recurso (si está bloqueado, lo establece en 0)
void Resources::unlockResource(Types_of_resources resource)
{
    if (getResourceAmount(resource) == -1)
    {
        setResourceAmount(resource, 0);
    }
}

// Método para agregar a la cantidad de un recurso
void Resources::addResource(Types_of_resources resource, int amount)
{
    if (amount < 0)
    {
        throw std::invalid_argument("No se puede agregar una cantidad negativa.");
    }
    int current_amount = getResourceAmount(resource);
    setResourceAmount(resource, current_amount + amount);
}

// Método para restar a la cantidad de un recurso
void Resources::subtractResource(Types_of_resources resource, int amount)
{
    if (amount < 0)
    {
        throw std::invalid_argument("No se puede restar una cantidad negativa.");
    }
    int current_amount = getResourceAmount(resource);
    
    // No permitir que baje de 0
    if (current_amount < amount)
    {
        setResourceAmount(resource, 0);
    }
    else
    {
        setResourceAmount(resource, current_amount - amount);
    }
}

// Método para imprimir los recursos desbloqueados y sus cantidades
void Resources::printResources() const
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
