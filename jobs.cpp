#include "jobs.hpp"
#include <iostream>
#include <stdexcept>

// Constructor que inicializa todos los trabajos a -1 (bloqueado)
Jobs::Jobs()
{
    jobs = {
        {"Farmer", -1},  
        {"Baker", -1}    
    };
}

// Método para asignar aldeanos a un trabajo
void Jobs::assign_villagers(JobTypes job, int number)
{
    if (number < 0)
        throw std::invalid_argument("No se puede asignar una cantidad negativa de aldeanos.");

    int &villagers = std::get<1>(jobs[static_cast<int>(job)]);

    // Si el trabajo está bloqueado, no se pueden asignar aldeanos
    if (villagers == -1)
        throw std::invalid_argument("El trabajo está bloqueado y no se pueden asignar aldeanos.");

    villagers += number;
}

// Método para remover aldeanos de un trabajo
void Jobs::remove_villagers(JobTypes job, int number)
{
    if (number < 0)
        throw std::invalid_argument("No se puede remover una cantidad negativa de aldeanos.");

    int &villagers = std::get<1>(jobs[static_cast<int>(job)]);

    // Si el trabajo está bloqueado, no se pueden remover aldeanos
    if (villagers == -1)
        throw std::invalid_argument("El trabajo está bloqueado.");

    if (villagers < number)
        throw std::invalid_argument("No hay suficientes aldeanos asignados.");

    villagers -= number;
}

// Método para desbloquear un trabajo
void Jobs::unlock_job(JobTypes job)
{
    int &villagers = std::get<1>(jobs[static_cast<int>(job)]);
    if (villagers == -1)
    {
        villagers = 0; // Desbloquear asignando 0 aldeanos
    }
}

// Método para recolectar recursos según los aldeanos asignados a los trabajos
void Jobs::collect_resources(Resources &resources)
{
    // Granjero -> genera trigo
    int farmer_villagers = std::get<1>(jobs[static_cast<int>(JobTypes::Farmer)]);
    if (farmer_villagers > 0)
    {
        // Añadimos trigo según la cantidad de aldeanos asignados al trabajo de Granjero
        resources.add_resource(Types_of_resources::wheat, farmer_villagers);
    }

    // Panadero -> convierte trigo en pan
    int baker_villagers = std::get<1>(jobs[static_cast<int>(JobTypes::Baker)]);
    if (baker_villagers > 0)
    {
        // Por cada aldeano asignado a Panadero, intentamos producir pan (requiere 2 de trigo)
        for (int i = 0; i < baker_villagers; ++i)
        {
            if (resources.get_resource(Types_of_resources::wheat) >= 2)
            {
                resources.subtract_resource(Types_of_resources::wheat, 2);
                resources.add_resource(Types_of_resources::bread, 1);
            }
            else
            {
                // Si no hay suficiente trigo, no podemos producir más pan
                break;
            }
        }
    }
}

// Método para imprimir los trabajos desbloqueados y los aldeanos asignados
void Jobs::print_jobs() const
{
    for (const auto& job : jobs)
    {
        const std::string& name = std::get<0>(job);
        int villagers = std::get<1>(job);

        // Solo imprimimos los trabajos desbloqueados (aldeanos >= 0)
        if (villagers >= 0)
        {
            std::cout << name << ": " << villagers << " aldeanos asignados" << std::endl;
        }
    }
}
