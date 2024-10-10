#pragma once
#include "resources.hpp"
#include <vector>
#include <tuple>
#include <string>

// Enum para los tipos de trabajos
enum class JobTypes
{
    Farmer,   
    Baker,    
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

    // Métodos para asignar aldeanos a un trabajo
    void assign_villagers(JobTypes job, int number);
    void remove_villagers(JobTypes job, int number);

    // Método para desbloquear un trabajo
    void unlock_job(JobTypes job);

    // Método para realizar la recolección de recursos basados en los trabajos
    void collect_resources(Resources &resources);

    // Método para imprimir los trabajos desbloqueados y sus aldeanos
    void print_jobs() const;
};
