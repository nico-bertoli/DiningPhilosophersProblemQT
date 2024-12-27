#include <future>
#include "PhilThread.h"
#include "RandomUtils.h"
#include "TimeHelper.h"
#include "QtLogging"
#include "QDebug"

// bool* PhilThread::forksAvailability = nullptr;
std::atomic<bool>* PhilThread::forksAvailability = nullptr;
size_t PhilThread::philsCount;

PhilThread::PhilThread
(
    PhilView* philView,
    size_t philsCount,
    size_t index,
    float thinkMinTime,
    float thinkMaxTime,
    float eatMinTime,
    float eatMaxTime
)
    : index{index}
{
    philsCount = philsCount;
    if(forksAvailability == nullptr)
        forksAvailability = new std::atomic<bool>[philsCount] {false,false,false,false};

    auto fut = std::async
        (
            std::launch::async,
            &PhilThread::PhilBehaviour,
            this,
            thinkMinTime,
            thinkMaxTime,
            eatMinTime,
            eatMaxTime
        );
}

void PhilThread::PhilBehaviour(float thinkMinTime, float thinkMaxTime, float eatMinTime, float eatMaxTime)
{
    while(true)
    {
        double stopThinkingTime = TimeHelper::Instance().GetTime() + RandomUtils::GetRandomDouble(thinkMinTime,thinkMaxTime);

        while(TimeHelper::Instance().GetTime() < stopThinkingTime)
            {/*think*/}

        SetState(State::Hungry);

        while(IsForkAvailable(ForkDir::Left) == false)
            {/*wait fork*/}
        SetForkAvailable(ForkDir::Left, false);

        while(forksAvailability[GetRightForkId()] == false)
            {/*wait fork*/}
        SetForkAvailable(ForkDir::Right, true);

        SetState(State::Eating);
        double stopEatingTime = TimeHelper::Instance().GetTime() + RandomUtils::GetRandomDouble(eatMinTime,eatMaxTime);
        while(TimeHelper::Instance().GetTime() < stopEatingTime)
            {/*eat*/}

        SetForkAvailable(ForkDir::Left, true);
        SetForkAvailable(ForkDir::Right, true);
    }
}

void PhilThread::SetForkAvailable(ForkDir dir, bool availability)
{
    if(dir == ForkDir::Left)
        forksAvailability[GetLeftForkId()] = availability;
    else
         forksAvailability[GetRightForkId()] = availability;
}

bool PhilThread::IsForkAvailable(ForkDir dir)
{
    return dir==ForkDir::Left ? forksAvailability[GetLeftForkId()] : forksAvailability[GetRightForkId()];
}

void PhilThread::SetState(State newState)
{
    qInfo() << "[phil " << index << "]"<< GetStateString(state) <<" -> "<< GetStateString(newState);
    state = newState;
}

QString PhilThread::GetStateString(State state)
{
    QString stateString = "NOT FOUND";

    switch(state)
    {
    case State::Thinking:
        stateString = "Thinking";
        break;
    case State::Eating:
        stateString = "Eating";
        break;
    case State::Hungry:
        stateString = "Hungry";
        break;
    }

    return stateString;
}

























