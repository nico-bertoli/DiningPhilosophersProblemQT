#include "PhilThreadDeadlockFree.h"
#include "RandomUtils.h"

std::mutex PhilThreadDeadlockFree::philsStatesMutex;
std::array<State,4> PhilThreadDeadlockFree::philsStates;
std::array<std::counting_semaphore<1>,4> PhilThreadDeadlockFree::philsSemaphores
{
    std::counting_semaphore<1>{1},
    std::counting_semaphore<1>{1},
    std::counting_semaphore<1>{1},
    std::counting_semaphore<1>{1}
};

void PhilThreadDeadlockFree::MainThreadSetup()
{
    for(auto& semaphore : philsSemaphores)
        semaphore.release();
}

void PhilThreadDeadlockFree::PhilBehaviour()
{
    SetState(State::Thinking);

    while(mustStop == false)
    {
        //-------------------- think
        double sleepTime = RandomUtils::GetRandomDouble(thinkMinTime,thinkMaxTime);
        threadSleepFuture.wait_for(std::chrono::duration<double>(sleepTime));

        //-------------------- try eat
        SetState(APhilThread::State::HungryNoForks);
        while(state == State::HungryNoForks)
        {
            TryEat();

            if(state == State::HungryNoForks)
                philsSemaphores[index].acquire();
        }
    }
    SetState(State::Terminated);
}

void PhilThreadDeadlockFree::TryEat()
{
    philsStatesMutex.lock();
    if
    (
        state != State::HungryNoForks ||
        philsStates[GetPhilIndexAtDirection(Direction::Right)] == State::Eating ||
        philsStates[GetPhilIndexAtDirection(Direction::Left)] == State::Eating
    )
    {
        philsStatesMutex.unlock();
        return;
    }
    philsStatesMutex.unlock();

    SetState(State::Eating);
    double eatTime = RandomUtils::GetRandomDouble(eatMinTime,eatMaxTime);
    threadSleepFuture.wait_for(std::chrono::duration<double>(eatTime));

    SetState(State::Thinking);

    //wake up neighbours
    philsSemaphores[GetPhilIndexAtDirection(Direction::Right)].release();
    philsSemaphores[GetPhilIndexAtDirection(Direction::Left)].release();
    return;
}

void PhilThreadDeadlockFree::SetState(State newState)
{
    philsStatesMutex.lock();
    APhilThread::SetState(newState);
    philsStates[index] = newState;
    philsStatesMutex.unlock();
}

void PhilThreadDeadlockFree::Stop()
{
    APhilThread::Stop();
}
