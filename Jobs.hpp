#pragma once
#include "Resources.hpp"
#include <vector>
#include <tuple>
#include <string>

// Enum para los tipos de trabajos
enum class JobTypes
{
    coinMaker,
    farmer,
    baker,
    tanner,
    weaver,
    silkFarmer,
    stoneMason,
    woodcutter,
    ironMiner,
    goldMiner,
    COUNT
};

class Jobs
{
private:
    // Un vector que almacena tuplas de <nombre del trabajo, aldeanos asignados>
    std::vector<std::tuple<std::string, int>> jobs;

public:
    // Constructor
    Jobs();

    // Métodos para obtener cantidad y nombre de los trabajos
    int Jobs::getJobAmount(JobTypes job) const;
    std::string Jobs::getJobName(JobTypes job) const;

    // Métodos para asignar aldeanos a un trabajo
    void assignVillagers(JobTypes job, int number);
    void removeVillagers(JobTypes job, int number);

    // Método para desbloquear un trabajo
    void unlockJob(JobTypes job);

    // Métodos para realizar la recolección de recursos basados en los trabajos
    void Jobs::processJob(Resources &resources, JobTypes job, Types_of_resources inputResource, int inputAmount, Types_of_resources outputResource, int outputAmount) const;
    void collectResources(Resources &resources);

    // Método para imprimir los trabajos desbloqueados y sus aldeanos
    void printJobs() const;
};
