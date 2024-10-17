#include "Jobs.hpp"
#include <iostream>
#include <stdexcept>

// Constructor que inicializa todos los trabajos a -1 (bloqueado)
Jobs::Jobs()
{
    jobs = {
        {"Coin Maker", -1},
        {"Farmer", -1},
        {"Baker", -1},
        {"Tanner", -1},
        {"Weaver", -1},
        {"Silk Farmer", -1},
        {"Stone Mason", -1},
        {"Woodcutter", -1},
        {"Iron Miner", -1},
        {"Gold Miner", -1}
    };

}

// Método para obtener la cantidad de aldeanos en un trabajo
int Jobs::getJobAmount(JobTypes job) const
{
    return std::get<1>(jobs[static_cast<int>(job)]);
}

// Método para obtener el nombre de un recurso
std::string Jobs::getJobName(JobTypes job) const
{
    return std::get<0>(jobs[static_cast<int>(job)]);
}

// Método para cambiar la cantidad de aldeanos en un trabajo
void Jobs::setJobAmount(JobTypes job, int amount)
{
    std::get<1>(jobs[static_cast<int>(job)]) = amount;
}

// Método para asignar aldeanos a un trabajo
void Jobs::assignVillagers(JobTypes job, int number)
{
    if (number < 0)
    {
        throw std::invalid_argument("No se puede asignar una cantidad negativa de aldeanos.");
    }

    // Si el trabajo está bloqueado, no se pueden asignar aldeanos
    if (getJobAmount(job) == -1)
    {
        throw std::invalid_argument("El trabajo está bloqueado y no se pueden asignar aldeanos.");
    }

    setJobAmount(job, getJobAmount(job) + number);
}

// Método para remover aldeanos de un trabajo
void Jobs::removeVillagers(JobTypes job, int number)
{
    if (number < 0)
    {
        throw std::invalid_argument("No se puede remover una cantidad negativa de aldeanos.");
    }

    // Si el trabajo está bloqueado, no se pueden remover aldeanos
    if (getJobAmount(job) == -1)
    {
        throw std::invalid_argument("El trabajo está bloqueado.");
    }

    if (getJobAmount(job) < number)
    {
        throw std::invalid_argument("No hay suficientes aldeanos asignados.");
    }

    setJobAmount(job, getJobAmount(job) - number);
}

// Método para desbloquear un trabajo
void Jobs::unlockJob(JobTypes job)
{
    if (getJobAmount(job) == -1)
    {
        setJobAmount(job, 0);
    }
}

void Jobs::processJob(Resources &resources, JobTypes job, Types_of_resources inputResource, int inputAmount, Types_of_resources outputResource, int outputAmount) const
{
    if (getJobAmount(job) > 0)
    {
        for (int i = 0; i < getJobAmount(job); ++i)
        {
            if (resources.getResourceAmount(inputResource) >= inputAmount)
            {
                resources.subtractResource(inputResource, inputAmount);
                resources.addResource(outputResource, outputAmount);
            }
            else
            {
                break;
            }
        }
    }
}

// Método para recolectar recursos según los aldeanos asignados a los trabajos
void Jobs::collectResources(Resources &resources)
{
    // Generador de monedas -> genera monedas    
    processJob(resources, JobTypes::coinMaker, Types_of_resources::gold, 1, Types_of_resources::coin, 11);

    // Granjero -> genera trigo    
    processJob(resources, JobTypes::farmer, Types_of_resources::coin, 0, Types_of_resources::wheat, 1);

    // Panadero -> convierte trigo en pan
    processJob(resources, JobTypes::baker, Types_of_resources::wheat, 2, Types_of_resources::bread, 1);

    // Curtidor -> genera cuero    
    processJob(resources, JobTypes::tanner, Types_of_resources::bread, 2, Types_of_resources::leather, 1);

    // Tejedor -> genera tela    
    processJob(resources, JobTypes::weaver, Types_of_resources::bread, 1, Types_of_resources::cloth, 1);

    // Agricultor de seda -> genera seda    
    processJob(resources, JobTypes::silkFarmer, Types_of_resources::cloth, 15, Types_of_resources::silk, 1);

    // Cantero -> genera piedra    
    processJob(resources, JobTypes::stoneMason, Types_of_resources::bread, 1, Types_of_resources::stone, 3);

    // Leñador -> genera madera    
    processJob(resources, JobTypes::woodcutter, Types_of_resources::bread, 1, Types_of_resources::wood, 3);

    // Minero de hierro -> genera hierro    
    processJob(resources, JobTypes::ironMiner, Types_of_resources::bread, 2, Types_of_resources::iron, 1);

    // Minero de oro -> genera oro    
    processJob(resources, JobTypes::goldMiner, Types_of_resources::bread, 10, Types_of_resources::gold, 1);
}
