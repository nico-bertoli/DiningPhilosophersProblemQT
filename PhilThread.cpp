#include <future>
#include "PhilThread.h"
#include "RandomUtils.h"
#include "TimeHelper.h"

PhilThread::PhilThread(PhilView* philView, Algorithm algorithm, float thinkMinTime, float thinkMaxTime, float eatMinTime, float eatMaxTime)
{
    auto fut = std::async
        (
            std::launch::async,
            &PhilThread::PhilBehaviour,
            algorithm,
            thinkMinTime,
            thinkMaxTime,
            eatMinTime,
            eatMaxTime
        );
}

void PhilThread::PhilBehaviour(Algorithm algorithm, float thinkMinTime, float thinkMaxTime, float eatMinTime, float eatMaxTime)
{
    while(true)
    {
        double stopThinkingTime = RandomUtils::GetRandomDouble(thinkMinTime,thinkMaxTime);

        while(TimeHelper::Instance().GetTime() < stopThinkingTime)
            {/*think*/}

        //     prendi(i)
        //     prendi((i+1)%5)
        //     mangia()
        //     posa((i+1)%5)
        //     posa(i)

    }
}
