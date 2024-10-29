#pragma once
#include <iostream>
#include <random>

class Dice
{
public:
    Dice();

    int roll(int sides);

private:
    std::mt19937 generator;
};