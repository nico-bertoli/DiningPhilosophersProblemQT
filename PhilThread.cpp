#include <chrono>
#include "PhilThread.h"
#include "RandomUtils.h"
#include "TimeHelper.h"
#include "QtLogging"
#include "QDebug"

std::array<std::counting_semaphore<1>, 4> PhilThread::forksSemaphores{
    std::counting_semaphore<1>{1},  // Initialize with count 1 (each fork is available initially)
    std::counting_semaphore<1>{1},
    std::counting_semaphore<1>{1},
    std::counting_semaphore<1>{1}
};

void PhilThread::MainThreadSetup()
{
    for(auto& semaphore : forksSemaphores)
        semaphore.release();
}

void PhilThread::PhilBehaviour(float thinkMinTime, float thinkMaxTime, float eatMinTime, float eatMaxTime)
{
    std::future<void> forceThreadStopFuture = forceThreadStopPromise.get_future();
    while(mustStop == false)
    {
        //--------------------think
        SetState(State::Thinking);
        double sleepTime = RandomUtils::GetRandomDouble(thinkMinTime,thinkMaxTime);
        forceThreadStopFuture.wait_for(std::chrono::duration<double>(sleepTime));

        //--------------------catch left fork
        SetState(State::HungryNoForks);
        CatchFork(Direction::Left);

        //grant deadlock if philosophers wait for the same time
        std::this_thread::sleep_for(std::chrono::duration<double>(mustStop ? 0 : 0.1));

        //--------------------catch right fork
        SetState(State::HungryLeftFork);
        CatchFork(Direction::Right);

        //--------------------eat
        SetState(State::Eating);
        // double eatTime = false ? 0 : RandomUtils::GetRandomDouble(thinkMinTime,thinkMaxTime);
        double eatTime = RandomUtils::GetRandomDouble(thinkMinTime,thinkMaxTime);
        forceThreadStopFuture.wait_for(std::chrono::duration<double>(eatTime));
        PutDownForks();
    }
    SetState(State::Terminated);
}

bool PhilThread::IsForkAvailable(Direction dir)
{
    switch(state)
    {
    case State::Thinking:
    case State::HungryNoForks:
    case State::Terminated:
        return true;
    case State::HungryLeftFork:
        return dir != Direction::Left;
    case State::HungryRightFork:
    case State::Eating:
        return false;
        break;
    default:
        throw std::invalid_argument("State not recognized: " + GetStateString(state).toStdString());
    }
}

void PhilThread::Stop()
{
    mustStop = true;
    forceThreadStopPromise.set_value();
    for(auto& sem : forksSemaphores)
        sem.release();
}

void PhilThread::CatchFork(Direction dir)
{
    auto& sem = dir == Direction::Right ? forksSemaphores[GetRightForkIndex()] : forksSemaphores[GetLeftForkIndex()];
    sem.acquire();
}

void PhilThread::PutDownFork(Direction dir)
{
    auto& sem = dir == Direction::Right ? forksSemaphores[GetRightForkIndex()] : forksSemaphores[GetLeftForkIndex()];
    sem.release();
}

void PhilThread::PutDownForks()
{
    PutDownFork(Direction::Left);
    PutDownFork(Direction::Right);
}
