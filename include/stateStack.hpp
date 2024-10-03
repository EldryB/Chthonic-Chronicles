#pragma once
#include <stack>
#include <memory>
#include "stage.hpp"

class StateStack 
{
public:
    void pushStage(std::shared_ptr<Stage> stage);
    void popStage();
    std::shared_ptr<Stage> getCurrentStage();

private:
    std::stack<std::shared_ptr<Stage>> stages;
};