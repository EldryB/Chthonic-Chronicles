#include <SFML/Graphics.hpp>

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

void Jobs::processJob(Resources &resources, JobTypes job, ResourceTypes inputResource, int inputAmount, ResourceTypes outputResource, int outputAmount) const
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
    processJob(resources, JobTypes::coinMaker, ResourceTypes::gold, 1, ResourceTypes::coin, 11);

    // Granjero -> genera trigo    
    processJob(resources, JobTypes::farmer, ResourceTypes::coin, 0, ResourceTypes::wheat, 1);

    // Panadero -> convierte trigo en pan
    processJob(resources, JobTypes::baker, ResourceTypes::wheat, 2, ResourceTypes::bread, 1);

    // Curtidor -> genera cuero    
    processJob(resources, JobTypes::tanner, ResourceTypes::bread, 2, ResourceTypes::leather, 1);

    // Tejedor -> genera tela    
    processJob(resources, JobTypes::weaver, ResourceTypes::bread, 1, ResourceTypes::cloth, 1);

    // Agricultor de seda -> genera seda    
    processJob(resources, JobTypes::silkFarmer, ResourceTypes::cloth, 15, ResourceTypes::silk, 1);

    // Cantero -> genera piedra    
    processJob(resources, JobTypes::stoneMason, ResourceTypes::bread, 1, ResourceTypes::stone, 3);

    // Leñador -> genera madera    
    processJob(resources, JobTypes::woodcutter, ResourceTypes::bread, 1, ResourceTypes::wood, 3);

    // Minero de hierro -> genera hierro    
    processJob(resources, JobTypes::ironMiner, ResourceTypes::bread, 2, ResourceTypes::iron, 1);

    // Minero de oro -> genera oro    
    processJob(resources, JobTypes::goldMiner, ResourceTypes::bread, 10, ResourceTypes::gold, 1);
}

void Jobs::printJobs(sf::RenderWindow& window, sf::Font& font) const
{
    // Configuración de texto para mostrar trabajos
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24); // Tamaño del texto
    text.setFillColor(sf::Color::White); // Color del texto

    // Recorrer los trabajos y mostrarlos
    for (size_t i = 0; i < jobs.size(); ++i) {
        std::string jobName = std::get<0>(jobs[i]); // Obtener el nombre del trabajo
        int assignedVillagers = std::get<1>(jobs[i]); // Obtener los aldeanos asignados

        // Configurar el texto para mostrar el trabajo
        text.setString(jobName + " - Assigned Villagers: " + std::to_string(assignedVillagers));
        text.setPosition(50, 50 + i * 30); // Posiciona el texto (cambia el 50 y 30 según sea necesario)

        // Dibujar el texto en la ventana
        window.draw(text);
    }
}