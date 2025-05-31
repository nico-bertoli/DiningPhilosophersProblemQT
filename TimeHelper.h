#pragma once
#include "Singleton.h"

#include <chrono>
#include <math.h>

class TimeHelper : public Singleton<TimeHelper>
{
    friend class Singleton;

    //---------------------------------------------------------- Fields
private:
    std::chrono::steady_clock::time_point startTime;

    //---------------------------------------------------------- Methods
public:
    double GetTime() const
    {
        std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = now - startTime;
        return elapsed.count();
    }

private:
    TimeHelper(){startTime = std::chrono::high_resolution_clock::now();}
};
