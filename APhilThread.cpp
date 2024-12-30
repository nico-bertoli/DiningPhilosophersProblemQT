#include "APhilThread.h"
#include "QtLogging"
#include "TimeHelper.h"

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
    this->index = index;

    if(index == 0)
        MainThreadSetup();

    threadFuture = std::async
    (
        std::launch::async,
        &APhilThread::PhilBehaviour,
        this,
        thinkMinTime,
        thinkMaxTime,
        eatMinTime,
        eatMaxTime
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
