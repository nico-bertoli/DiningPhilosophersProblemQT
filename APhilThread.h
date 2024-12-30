#ifndef APHILTHREAD_H
#define APHILTHREAD_H

#include <future>
#include <atomic>
#include <QObject>
#include <semaphore>
#include "QString"
#include "DirectionUtils.h"
#include "QDebug"

using Direction = DirectionUtils::Direction;

class APhilThread : public QObject
{
    Q_OBJECT

//-------------------------------------------- Fields
public:
    enum class State {Thinking, HungryNoForks, HungryLeftFork, HungryRightFork, Eating, Terminated};
protected:
    bool mustStop = false;
    State state = State::Thinking;
    size_t index;
    std::future<void> threadFuture;
    std::promise<void> forceThreadStopPromise;
//-------------------------------------------- Methods
public:
    explicit APhilThread(QObject* parent = nullptr);

    void Run
    (
        size_t index,
        float thinkMinTime,
        float thinkMaxTime,
        float eatMinTime,
        float eatMaxTime
    );

    State GetState(){return state;}
    QString GetStateString(State state);
    size_t GetIndex(){return index;}
    virtual void Stop() = 0;
    virtual bool IsForkAvailable(Direction dir) = 0;

protected:
    virtual void MainThreadSetup() = 0;
    virtual void PhilBehaviour(float thinkMinTime, float thinkMaxTime, float eatMinTime, float eatMaxTime) = 0;

    size_t GetLeftForkIndex(){return index == 0 ? 3 : index -1;} //todo remove hardcoded philsCount
    size_t GetRightForkIndex(){return index;}

    void SetState(State newState);

signals:
    void SignalStateChanged();
    void SignalDestroyed();
};

#endif // APHILTHREAD_H
