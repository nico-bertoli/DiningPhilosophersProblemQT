#include "PhilThreadNoDeadlock.h"
#include "RandomUtils.h"

std::mutex PhilThreadNoDeadlock::philsStatesMutex;
std::array<State,4> PhilThreadNoDeadlock::philsStates;
std::array<std::counting_semaphore<1>,4> PhilThreadNoDeadlock::philsSemaphores
{
    std::counting_semaphore<1>{1},
    std::counting_semaphore<1>{1},
    std::counting_semaphore<1>{1},
    std::counting_semaphore<1>{1}
};

void PhilThreadNoDeadlock::OnThreadSetup()
{
    // todo delete
}

void PhilThreadNoDeadlock::MainThreadSetup()
{
    for(auto& semaphore : philsSemaphores)
        semaphore.release();
}

void PhilThreadNoDeadlock::PhilBehaviour()
{
    this->eatMinTime = eatMinTime;
    this->eatMaxTime = eatMaxTime;

    SetState(State::Thinking);

    while(mustStop == false)
    {
        //--------------------think
        double sleepTime = RandomUtils::GetRandomDouble(thinkMinTime,thinkMaxTime);
        threadSleepFuture.wait_for(std::chrono::duration<double>(sleepTime));

        Eat();
    }
    SetState(State::Terminated);
}

void PhilThreadNoDeadlock::Eat()
{
    SetState(APhilThread::State::HungryNoForks);
    while(state == State::HungryNoForks)
    {
        TryEat();

        if(state == State::HungryNoForks)
            philsSemaphores[index].acquire();
    }
}

void PhilThreadNoDeadlock::TryEat()
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

void PhilThreadNoDeadlock::SetState(State newState)
{
    philsStatesMutex.lock();
    APhilThread::SetState(newState);
    philsStates[index] = newState;
    philsStatesMutex.unlock();
}

void PhilThreadNoDeadlock::Stop()
{
    APhilThread::Stop();
}
