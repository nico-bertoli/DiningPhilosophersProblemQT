#include <chrono>
#include "PhilThreadDeadlock.h"
#include "RandomUtils.h"
#include "TimeHelper.h"
#include "QtLogging"
#include "QDebug"

std::array<std::counting_semaphore<1>, 4> PhilThreadDeadlock::forksSemaphores{
    std::counting_semaphore<1>{1},
    std::counting_semaphore<1>{1},
    std::counting_semaphore<1>{1},
    std::counting_semaphore<1>{1}
};

void PhilThreadDeadlock::MainThreadSetup()
{
    for(auto& semaphore : forksSemaphores)
        semaphore.release();
}

void PhilThreadDeadlock::PhilBehaviour()
{
    while(mustStop == false)
    {
        //--------------------think
        SetState(State::Thinking);
        double sleepTime = RandomUtils::GetRandomDouble(thinkMinTime,thinkMaxTime);
        threadSleepFuture.wait_for(std::chrono::duration<double>(sleepTime));

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
        double eatTime = RandomUtils::GetRandomDouble(thinkMinTime,thinkMaxTime);
        threadSleepFuture.wait_for(std::chrono::duration<double>(eatTime));
        PutDownForks();
    }
    SetState(State::Terminated);
}

void PhilThreadDeadlock::Stop()
{
    APhilThread::Stop();
    for(auto& sem : forksSemaphores)
        sem.release();
}

void PhilThreadDeadlock::CatchFork(Direction dir)
{
    auto& sem = forksSemaphores[GetForkIndexAtDirection(dir)];
    sem.acquire();
}

void PhilThreadDeadlock::PutDownFork(Direction dir)
{
    auto& sem = forksSemaphores[GetForkIndexAtDirection(dir)];
    sem.release();
}

void PhilThreadDeadlock::PutDownForks()
{
    PutDownFork(Direction::Left);
    PutDownFork(Direction::Right);
}
