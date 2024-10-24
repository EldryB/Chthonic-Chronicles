#pragma once
#include <vector>
#include <tuple>
#include <string>

enum class ResourceTypes
{
    coin,
    wheat,
    bread,
    leather,
    cloth,
    silk,
    stone,
    wood,
    iron,
    gold,
    COUNT
};

class Resources
{
public:
    Resources();

    int getResourceAmount(ResourceTypes resource) const;
    std::string getResourceName(ResourceTypes resource) const;

    void setResourceAmount(ResourceTypes resource, int amount);
    void unlockResource(ResourceTypes resource);
    void addResource(ResourceTypes resource, int amount);
    void subtractResource(ResourceTypes resource, int amount);

private:
    std::vector<std::tuple<std::string, int>> resources;

};
