#include <chrono>
#include "PhilThreadHoldAndWait.h"
#include "RandomUtils.h"
#include "TimeHelper.h"
#include "QtLogging"
#include "QDebug"

std::array<std::counting_semaphore<1>, 4> PhilThreadHoldAndWait::forksSemaphores{
    std::counting_semaphore<1>{1},
    std::counting_semaphore<1>{1},
    std::counting_semaphore<1>{1},
    std::counting_semaphore<1>{1}
};

void PhilThreadHoldAndWait::MainThreadSetup()
{
    for(auto& semaphore : forksSemaphores)
        semaphore.release();
}

void PhilThreadHoldAndWait::PhilBehaviour()
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

void PhilThreadHoldAndWait::Stop()
{
    APhilThread::Stop();
    for(auto& sem : forksSemaphores)
        sem.release();
}

void PhilThreadHoldAndWait::CatchFork(Direction dir)
{
    auto& sem = forksSemaphores[GetForkIndexAtDirection(dir)];
    sem.acquire();
}

void PhilThreadHoldAndWait::PutDownFork(Direction dir)
{
    auto& sem = forksSemaphores[GetForkIndexAtDirection(dir)];
    sem.release();
}

void PhilThreadHoldAndWait::PutDownForks()
{
    PutDownFork(Direction::Left);
    PutDownFork(Direction::Right);
}
