#include "Resources.hpp"

Resources::Resources()
{
    resources = {
        {"Coin", 0},
        {"Wheat", 0},
        {"Bread", 0},
        {"Leather", 0},
        {"Cloth", 0},
        {"Silk", 0},
        {"Stone", 0},
        {"Wood", 0},
        {"Iron", 0},
        {"Gold", 0}
    };
}

int Resources::getResourceAmount(ResourceTypes resource) const
{
    return std::get<1>(resources[static_cast<int>(resource)]);
}

std::string Resources::getResourceName(ResourceTypes resource) const
{
    return std::get<0>(resources[static_cast<int>(resource)]);
}

void Resources::setResourceAmount(ResourceTypes resource, int amount)
{
    std::get<1>(resources[static_cast<int>(resource)]) = amount;
}

void Resources::unlockResource(ResourceTypes resource)
{
    if (getResourceAmount(resource) == -1)
    {
        setResourceAmount(resource, 0);
    }
}

void Resources::addResource(ResourceTypes resource, int amount)
{
    setResourceAmount(resource, getResourceAmount(resource) + amount);
}

void Resources::subtractResource(ResourceTypes resource, int amount)
{
    if (getResourceAmount(resource) - amount >= 0)
    {
        setResourceAmount(resource, getResourceAmount(resource) - amount);
    }
}