#include "Jobs.hpp"

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

int Jobs::getJobAmount(JobTypes job) const
{
    return std::get<1>(jobs[static_cast<int>(job)]);
}

void Jobs::setJobAmount(JobTypes job, int amount)
{
    std::get<1>(jobs[static_cast<int>(job)]) = amount;
}

std::string Jobs::getJobName(JobTypes job) const
{
    return std::get<0>(jobs[static_cast<int>(job)]);
}

void Jobs::assignVillagers(JobTypes job)
{
    setJobAmount(job, getJobAmount(job) + 1);
}

void Jobs::removeVillagers(JobTypes job)
{
    if (getJobAmount(job) > 0)
    {
        setJobAmount(job, getJobAmount(job) - 1);
    }
}

void Jobs::unlockJob(JobTypes job)
{
    if (getJobAmount(job) == -1)
    {
        setJobAmount(job, 0);
    }
}

void Jobs::processJob(Resources& resources, JobTypes job, ResourceTypes inputResource, int inputAmount, ResourceTypes outputResource, int outputAmount) const
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

void Jobs::collectResources(Resources& resources)
{
    processJob(resources, JobTypes::coinMaker, ResourceTypes::gold, 1, ResourceTypes::coin, 11);

    processJob(resources, JobTypes::farmer, ResourceTypes::coin, 0, ResourceTypes::wheat, 1);

    processJob(resources, JobTypes::baker, ResourceTypes::wheat, 2, ResourceTypes::bread, 1);

    processJob(resources, JobTypes::tanner, ResourceTypes::bread, 2, ResourceTypes::leather, 1);

    processJob(resources, JobTypes::weaver, ResourceTypes::bread, 1, ResourceTypes::cloth, 1);

    processJob(resources, JobTypes::silkFarmer, ResourceTypes::cloth, 15, ResourceTypes::silk, 1);

    processJob(resources, JobTypes::stoneMason, ResourceTypes::bread, 1, ResourceTypes::stone, 3);

    processJob(resources, JobTypes::woodCutter, ResourceTypes::bread, 1, ResourceTypes::wood, 3);

    processJob(resources, JobTypes::ironMiner, ResourceTypes::bread, 2, ResourceTypes::iron, 1);

    processJob(resources, JobTypes::goldMiner, ResourceTypes::bread, 10, ResourceTypes::gold, 1);
}