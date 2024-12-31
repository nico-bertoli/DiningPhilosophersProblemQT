#ifndef RANDOM_UTILS_H
#define RANDOM_UTILS_H

#include <random>

namespace RandomUtils
{
    inline double GetRandomDouble(double min, double max)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }

    inline int GetRandomInt(int minInclusive, int maxInclusive)
    {
        return minInclusive + std::rand() % (maxInclusive - minInclusive + 1);
    }

    inline bool GetRandomBool()
    {
        return GetRandomInt(0, 1) == 0;
    }
}

#endif
