#include <stateStack.hpp>

void StateStack::pushStage(std::shared_ptr<Stage> stage)
{
    stages.push(stage);
}

void StateStack::popStage()
{
    if (!stages.empty())
    {
        stages.pop();
    }
}

std::shared_ptr<Stage> StateStack::getCurrentStage()
{
    if (!stages.empty())
    {
        return stages.top();
    }

    return nullptr;
}