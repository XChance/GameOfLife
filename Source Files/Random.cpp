#include "../Header Files/Random.h"

#include <ctime>

//Returns static Random object
Random& Random::get()
{
    static Random r;
    return r;
}

//Creates seed for random
Random::Random()
{
    rng.seed ((unsigned)std::time(nullptr));
}

//Returns int within a certain range
int Random::intInRange(int low, int high)
{
    std::uniform_int_distribution<int> dist(low, high);
    return dist(rng);
}

//Returns float within a certain range
float Random::floatInRange(float low, float high)
{
    std::uniform_real_distribution<float> dist(low, high);
    return dist(rng);
}