#include "PhilThreadNoDeadlock.h"
#include "RandomUtils.h"

std::mutex PhilThreadNoDeadlock::mutex;
std::array<PhilThreadNoDeadlock*,4> PhilThreadNoDeadlock::phils;
std::array<std::counting_semaphore<1>,4> PhilThreadNoDeadlock::philsSemaphores
{
    std::counting_semaphore<1>{1},
    std::counting_semaphore<1>{1},
    std::counting_semaphore<1>{1},
    std::counting_semaphore<1>{1}
};

void PhilThreadNoDeadlock::OnThreadSetup()
{
    phils[index] = this;
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

    //todo try make this a variable
    std::future<void> forceThreadStopFuture = forceThreadStopPromise.get_future();
    SetState(State::Thinking);

    while(mustStop == false)
    {
        //--------------------think
        double sleepTime = RandomUtils::GetRandomDouble(thinkMinTime,thinkMaxTime);
        forceThreadStopFuture.wait_for(std::chrono::duration<double>(sleepTime));

        // //--------------------catch forks
        Eat();
        // PutDownForks();
    }
    SetState(State::Terminated);
}

void PhilThreadNoDeadlock::Eat()
{
    SetState(APhilThread::State::HungryNoForks);
    while(state == State::HungryNoForks)
    {
        // mutex.lock();
        TryEat();
        // mutex.unlock();

        if(state == State::HungryNoForks)
        {
            qInfo()<<"thread"<< index <<"sleeping on semaphore";
            philsSemaphores[index].acquire();
        }
    }
}

void PhilThreadNoDeadlock::TryEat()
{
    if(state != State::HungryNoForks || GetPhilState(Direction::Right) == State::Eating || GetPhilState(Direction::Left) == State::Eating)
        return;

    SetState(State::Eating);
    double eatTime = RandomUtils::GetRandomDouble(eatMinTime,eatMaxTime);
    qInfo()<<"thread"<< index <<" eating for "<< eatTime;
    std::future<void> forceThreadStopFuture = forceThreadStopPromise.get_future();
    forceThreadStopFuture.wait_for(std::chrono::duration<double>(eatTime));
    qInfo()<<"thread"<< index <<" eat ended";

    SetState(State::Thinking);

    //wake up neighbours
    philsSemaphores[GetNeighbourIndexAtDirection(Direction::Right)].release();
    philsSemaphores[GetNeighbourIndexAtDirection(Direction::Left)].release();
    return;
}

void PhilThreadNoDeadlock::Stop()
{
    APhilThread::Stop();
}

State PhilThreadNoDeadlock::GetPhilState(Direction dir)
{
    size_t index = GetNeighbourIndexAtDirection(dir);
    return phils[index]->GetState();
}
