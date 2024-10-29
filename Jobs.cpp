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

void Jobs::collectResources(Resources& resources, JobTypes _jobs)
{
    switch (_jobs)
    {
    case JobTypes::coinMaker:  processJob(resources, JobTypes::coinMaker, ResourceTypes::gold, 1, ResourceTypes::coin, 11);
        break;

    case JobTypes::farmer:  processJob(resources, JobTypes::farmer, ResourceTypes::coin, 0, ResourceTypes::wheat, 1);
        break;

    case JobTypes::baker:  processJob(resources, JobTypes::baker, ResourceTypes::wheat, 2, ResourceTypes::bread, 1);
        break;

    case JobTypes::tanner:  processJob(resources, JobTypes::tanner, ResourceTypes::bread, 2, ResourceTypes::leather, 1);
        break;

    case JobTypes::weaver:  processJob(resources, JobTypes::weaver, ResourceTypes::bread, 1, ResourceTypes::cloth, 1);
        break;

    case JobTypes::silkFarmer:  processJob(resources, JobTypes::silkFarmer, ResourceTypes::cloth, 15, ResourceTypes::silk, 1);
        break;

    case JobTypes::stoneMason:  processJob(resources, JobTypes::stoneMason, ResourceTypes::bread, 1, ResourceTypes::stone, 3);
        break;

    case JobTypes::woodCutter:  processJob(resources, JobTypes::woodCutter, ResourceTypes::bread, 1, ResourceTypes::wood, 3);
        break;

    case JobTypes::ironMiner:  processJob(resources, JobTypes::ironMiner, ResourceTypes::bread, 2, ResourceTypes::iron, 1);
        break;

    case JobTypes::goldMiner:  processJob(resources, JobTypes::goldMiner, ResourceTypes::bread, 10, ResourceTypes::gold, 1);
        break;

    default:
        break;
    }
}