#include "PhilThreadChandyMisra.h"
#include "RandomUtils.h"

using State = APhilThread::State;
using Direction = DirectionUtils::Direction;

void PhilThreadChandyMisra::MainThreadSetup()
{
    for(auto& semaphore : philsSemaphores)
        semaphore.release();
}

void PhilThreadChandyMisra::PhilBehaviour()
{
    SetState(State::Thinking);

    while(mustTerminate == false)
    {
        //-------------------- think
        double sleepTime = RandomUtils::GetRandomDouble(thinkMinTime,thinkMaxTime);
        sleepFuture.wait_for(std::chrono::duration<double>(sleepTime));

        //-------------------- try eat
        SetState(APhilThread::State::HungryNoForks);
        while(state == State::HungryNoForks)
        {
            TryEat();

            //if eat failed, sleeps until a neighbour wakes it up
            if(state == State::HungryNoForks)
                philsSemaphores[index].acquire();
        }
    }
    SetState(State::Terminated);
}

void PhilThreadChandyMisra::TryEat()
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
    sleepFuture.wait_for(std::chrono::duration<double>(eatTime));

    SetState(State::Thinking);

    //try to wake up neighbours
    philsSemaphores[GetPhilIndexAtDirection(Direction::Right)].release();
    philsSemaphores[GetPhilIndexAtDirection(Direction::Left)].release();
    return;
}

void PhilThreadChandyMisra::SetState(State newState)
{
    philsStatesMutex.lock();
    APhilThread::SetState(newState);
    philsStates[index] = newState;
    philsStatesMutex.unlock();
}
