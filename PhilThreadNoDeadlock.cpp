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
        philsStates[GetNeighbourIndexAtDirection(Direction::Right)] == State::Eating ||
        philsStates[GetNeighbourIndexAtDirection(Direction::Left)] == State::Eating
    )
    {
        qInfo() << index << "couldn't eat: "<<APhilThread::GetStateString(state).toStdString()<<", "<<APhilThread::GetStateString( philsStates[GetNeighbourIndexAtDirection(Direction::Right)]).toStdString()<<", "<< APhilThread::GetStateString(philsStates[GetNeighbourIndexAtDirection(Direction::Left)]).toStdString();
        philsStatesMutex.unlock();
        return;
    }
    philsStatesMutex.unlock();

    SetState(State::Eating);
    double eatTime = RandomUtils::GetRandomDouble(eatMinTime,eatMaxTime);
    qInfo()<<"thread"<< index <<" eating for "<< eatTime;
    threadSleepFuture.wait_for(std::chrono::duration<double>(eatTime));
    qInfo()<<"thread"<< index <<" eat ended";

    SetState(State::Thinking);

    //wake up neighbours
    philsSemaphores[GetNeighbourIndexAtDirection(Direction::Right)].release();
    philsSemaphores[GetNeighbourIndexAtDirection(Direction::Left)].release();
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
