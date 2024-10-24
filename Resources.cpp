#include "Resources.hpp"

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
    setResourceAmount(resource, getResourceAmount(resource) - amount);
}