#include "PhilThread.h"
#include "RandomUtils.h"
#include "TimeHelper.h"
#include "QtLogging"
#include "QDebug"

// bool* PhilThread::forksAvailability = nullptr;
std::atomic<bool>* PhilThread::forksAvailability = nullptr;
size_t PhilThread::philsCount = 0;

PhilThread::PhilThread
(
    size_t index,
    float thinkMinTime,
    float thinkMaxTime,
    float eatMinTime,
    float eatMaxTime,
    QObject* parent
)
    : QObject(parent), index(index)
{
    if(index == 0)
        MainThreadSetup();

    future = std::async
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

void PhilThread::MainThreadSetup()
{
    assert(index == 0);

    if(forksAvailability == nullptr)
        forksAvailability = new std::atomic<bool>[philsCount];

    for(int i = 0; i<philsCount; ++i)
        forksAvailability[i] = true;
}

void PhilThread::PhilBehaviour(float thinkMinTime, float thinkMaxTime, float eatMinTime, float eatMaxTime)
{
    while(true)
    {
        SetState(State::Thinking);
        double stopThinkingTime = TimeHelper::Instance().GetTime() + RandomUtils::GetRandomDouble(thinkMinTime,thinkMaxTime);

        while(TimeHelper::Instance().GetTime() < stopThinkingTime)
            {/*think*/}

        SetState(State::HungryNoForks);
        while(IsForkAvailable(Direction::Left) == false)
            {/*wait fork*/}
        SetForkAvailable(Direction::Left, false);

        SetState(State::HungryLeftFork);
        while(forksAvailability[GetRightForkId()] == false)
            {/*wait fork*/}
        SetForkAvailable(Direction::Right, true);

        SetState(State::Eating);
        double stopEatingTime = TimeHelper::Instance().GetTime() + RandomUtils::GetRandomDouble(eatMinTime,eatMaxTime);
        while(TimeHelper::Instance().GetTime() < stopEatingTime)
            {/*eat*/}

        SetForkAvailable(Direction::Left, true);
        SetForkAvailable(Direction::Right, true);
    }
}

void PhilThread::SetForkAvailable(Direction dir, bool availability)
{
    if(dir == Direction::Left)
        forksAvailability[GetLeftForkId()] = availability;
    else
         forksAvailability[GetRightForkId()] = availability;
}

bool PhilThread::IsForkAvailable(Direction dir)
{
    return dir==Direction::Left ? forksAvailability[GetLeftForkId()] : forksAvailability[GetRightForkId()];
}

void PhilThread::SetState(State newState)
{
    if(state == newState)
        return;

    qInfo() << "[phil " << index << "]"<< GetStateString(state) <<" -> "<< GetStateString(newState);
    state = newState;
    SignalStateChanged();
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
    case State::HungryNoForks:
        stateString = "Hungry";
        break;
    case State::HungryLeftFork:
        stateString = "HungryLeftFork";
        break;
    case State::HungryRightFork:
        stateString = "HungryRightFork";
        break;
    }

    return stateString;
}

























