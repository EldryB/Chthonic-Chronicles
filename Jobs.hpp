#pragma once
#include "Resources.hpp"
#include <vector>
#include <tuple>
#include <string>

enum class JobTypes
{
    coinMaker,
    farmer,
    baker,
    tanner,
    weaver,
    silkFarmer,
    stoneMason,
    woodCutter,
    ironMiner,
    goldMiner,
    count
};

class Jobs
{
public:
    Jobs();

    int getJobAmount(JobTypes job) const;
    void setJobAmount(JobTypes job, int amount);

    std::string getJobName(JobTypes job) const;
    void assignVillagers(JobTypes job);
    void removeVillagers(JobTypes job);
    void unlockJob(JobTypes job);

    void processJob(Resources &resources, JobTypes job, ResourceTypes inputResource, int inputAmount, ResourceTypes outputResource, int outputAmount) const;
    void collectResources(Resources &resources);

private:
    std::vector<std::tuple<std::string, int>> jobs;
};
