#include "APhilThread.h"
#include "QtLogging"
#include "TimeHelper.h"

using DirectionUtils::Direction;

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
    //---------------- setup
    this->index = index;
    if(index == 0)
    {
        this->thinkMinTime = thinkMinTime;
        this->thinkMaxTime = thinkMaxTime;
        this->eatMinTime = eatMinTime;
        this->eatMaxTime = eatMaxTime;
        MainThreadSetup();
    };

    //---------------- run
    threadFuture = std::async
    (
        std::launch::async,
        &APhilThread::PhilBehaviour,
        this
    );
}

void APhilThread::SetState(State newState)
{
    if(state == newState)
        return;

    qInfo() << "[phil " << index << "]"<< StateToQString(state) <<" -> "<< StateToQString(newState) << "[" << TimeHelper::Instance().GetTime() << "]";
    state = newState;
    SignalStateChanged();
}

size_t APhilThread::GetForkIndexAtDirection(Direction dir)
{
    if(dir == Direction::Right)
        return index;
    else
        return index == 0 ? PHILS_COUNT-1  : index -1;
}

size_t APhilThread::GetPhilIndexAtDirection(Direction dir)
{
    if(dir == Direction::Right)
        return (index + 1) % PHILS_COUNT;
    else
        return index == 0 ? PHILS_COUNT -1 : index - 1;
}

void APhilThread::Terminate()
{
    mustTerminate = true;
    forceWakeUpPromise.set_value();
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

    default:
        throw std::invalid_argument("State not recognized: " + StateToQString(state).toStdString());
    }
}

QString APhilThread::StateToQString(State state)
{
    switch(state)
    {
    case State::Thinking:
        return "Thinking";
        break;
    case State::Eating:
        return "Eating";
        break;
    case State::HungryNoForks:
        return "Hungry";
        break;
    case State::HungryLeftFork:
        return "HungryLeftFork";
        break;
    case State::HungryRightFork:
        return "HungryRightFork";
        break;
    case State::Terminated:
        return "Terminated";
        break;
    }

    return "NOT_FOUND";
}
