#include <chrono>
#include "PhilThread.h"
#include "RandomUtils.h"
#include "TimeHelper.h"
#include "QtLogging"
#include "QDebug"

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

    threadFuture = std::async
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
    if(forksAvailability == nullptr)
        forksAvailability = new std::atomic<bool>[philsCount];

    for(int i = 0; i<philsCount; ++i)
        forksAvailability[i] = true;
}

void PhilThread::PhilBehaviour(float thinkMinTime, float thinkMaxTime, float eatMinTime, float eatMaxTime)
{
    while(mustStop == false)
    {
        //--------------------think
        SetState(State::Thinking);
        double sleepTime = RandomUtils::GetRandomDouble(thinkMinTime,thinkMaxTime);
        std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));

        //--------------------catch left fork
        SetState(State::HungryNoForks);
        while(IsForkAvailable(Direction::Left) == false)
            std::this_thread::sleep_for(std::chrono::duration<double>(0.1));
        SetForkAvailable(Direction::Left, false);

        //grant deadlock if philosophers wait for the same time
        std::this_thread::sleep_for(std::chrono::duration<double>(0.1));

        //--------------------catch right fork
        SetState(State::HungryLeftFork);
        while(IsForkAvailable(Direction::Right) == false)
            std::this_thread::sleep_for(std::chrono::duration<double>(0.1));
        SetForkAvailable(Direction::Right, false);

        //--------------------eat
        SetState(State::Eating);
        double eatTime = mustStop ? 0 : RandomUtils::GetRandomDouble(thinkMinTime,thinkMaxTime);
        std::this_thread::sleep_for(std::chrono::duration<double>(eatTime));
        SetForkAvailable(Direction::Left, true);
        SetForkAvailable(Direction::Right, true);
    }

    SetState(State::Terminated);
}

void PhilThread::SetForkAvailable(Direction dir, bool availability)
{
    if(dir == Direction::Left)
        forksAvailability[GetLeftForkIndex()] = availability;
    else
         forksAvailability[GetRightForkIndex()] = availability;
}

bool PhilThread::IsForkAvailable(Direction dir)
{
    return dir==Direction::Left ? forksAvailability[GetLeftForkIndex()] : forksAvailability[GetRightForkIndex()];
}

void PhilThread::SetState(State newState)
{
    if(state == newState)
        return;

    qInfo() << "[phil " << index << "]"<< GetStateString(state) <<" -> "<< GetStateString(newState) << "[" << TimeHelper::Instance().GetTime() << "]";
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
    case State::Terminated:
        stateString = "Terminated";
        break;
    }

    return stateString;
}

























