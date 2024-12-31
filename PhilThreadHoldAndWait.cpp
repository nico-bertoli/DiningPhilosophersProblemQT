#include <chrono>
#include "PhilThreadHoldAndWait.h"
#include "RandomUtils.h"
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
    while(mustTerminate == false)
    {
        //-------------------- think
        SetState(State::Thinking);
        double sleepTime = RandomUtils::GetRandomDouble(thinkMinTime,thinkMaxTime);
        sleepFuture.wait_for(std::chrono::duration<double>(sleepTime));

        //-------------------- catch left fork
        SetState(State::HungryNoForks);
        CatchFork(Direction::Left);

        //grant deadlock if philosophers wait for the same time
        std::this_thread::sleep_for(std::chrono::duration<double>(0.1));

        //-------------------- catch right fork
        SetState(State::HungryLeftFork);
        CatchFork(Direction::Right);

        //-------------------- eat
        SetState(State::Eating);
        double eatTime = RandomUtils::GetRandomDouble(thinkMinTime,thinkMaxTime);
        sleepFuture.wait_for(std::chrono::duration<double>(eatTime));
        PutDownForks();
    }
    SetState(State::Terminated);
}

void PhilThreadHoldAndWait::Terminate()
{
    APhilThread::Terminate();
    for(auto& sem : forksSemaphores)
        sem.release();
}

void PhilThreadHoldAndWait::CatchFork(Direction dir)
{
    forksSemaphores[GetForkIndexAtDirection(dir)].acquire();
}

void PhilThreadHoldAndWait::PutDownFork(Direction dir)
{
    forksSemaphores[GetForkIndexAtDirection(dir)].release();
}

void PhilThreadHoldAndWait::PutDownForks()
{
    PutDownFork(Direction::Left);
    PutDownFork(Direction::Right);
}
