#pragma once
#include "Singleton.h"

#include <chrono>
#include <math.h>

using time_point = std::chrono::steady_clock::time_point;
using hr_clock = std::chrono::high_resolution_clock;

class TimeHelper : public Singleton<TimeHelper>
{
    friend class Singleton;

    //---------------------------------------------------------- Fields
private:
    time_point startTime;

    //---------------------------------------------------------- Methods
public:
    double GetTime() const
    {
        time_point now = hr_clock::now();
        std::chrono::duration<double> elapsed = now - startTime;
        return elapsed.count();
    }

private:
    TimeHelper(){startTime = hr_clock::now();}
};
