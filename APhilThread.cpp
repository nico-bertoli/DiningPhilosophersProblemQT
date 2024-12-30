#include "APhilThread.h"
#include "QtLogging"
#include "TimeHelper.h"

double APhilThread::eatMinTime;
double APhilThread::eatMaxTime;
double APhilThread::thinkMinTime;
double APhilThread::thinkMaxTime;

APhilThread::APhilThread(QObject* parent): QObject(parent){ }

void APhilThread::Run
(
    size_t index,
    float thinkMinTime,
    float thinkMaxTime,
    float eatMinTime,
    float eatMaxTime
)
{
    //setup
    this->index = index;
    if(index == 0)
    {
        this->thinkMinTime = thinkMinTime;
        this->thinkMaxTime = thinkMaxTime;
        this->eatMinTime = eatMinTime;
        this->eatMaxTime = eatMaxTime;
        MainThreadSetup();
    }

    OnThreadSetup();

    //run
    threadFuture = std::async
    (
        std::launch::async,
        &APhilThread::PhilBehaviour,
        this
    );
}

QString APhilThread::GetStateString(State state)
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

void APhilThread::SetState(State newState)
{
    if(state == newState)
        return;

    qInfo() << "[phil " << index << "]"<< GetStateString(state) <<" -> "<< GetStateString(newState) << "[" << TimeHelper::Instance().GetTime() << "]";
    state = newState;
    SignalStateChanged();
}

size_t APhilThread::GetForkIndexAtDirection(Direction dir)
{
    if(dir == Direction::Right)
        return index;
    else
        return index == 0 ? PHILS_COUNT -1  : index -1;
}

size_t APhilThread::GetPhilIndexAtDirection(Direction dir)
{
    if(dir == Direction::Right)
        return (index + 1) % PHILS_COUNT;
    else
        return index == 0 ? PHILS_COUNT -1 : index - 1;
}

void APhilThread::Stop()
{
    mustStop = true;
    threadSleepPromise.set_value();
}

bool APhilThread::IsForkAvailable(Direction dir)
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
