#ifndef GAME_OF_LIFE_RANDOM_H
#define GAME_OF_LIFE_RANDOM_H

#include <random>

//Class for getting random numbers
//Used for cell movement and initial Creature spawning
class Random
{
public:
    static Random& get();

    Random (const Random& other) = delete;
    Random& operator = (const Random& other) = delete;

    int intInRange(int low, int high);
    float floatInRange(float low, float high);

private:
    Random();

    std::mt19937 rng;
};


#endif //GAME_OF_LIFE_RANDOM_H