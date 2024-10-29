#include "Dice.hpp"

Dice::Dice()
{
    std::random_device random;
    generator.seed(random());
}

int Dice::roll(int sides)
{
    std::uniform_int_distribution<int> distribution(1, sides);
    return distribution(generator);
}





