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
    static double eatMinTime;
    static double eatMaxTime;
    static double thinkMinTime;
    static double thinkMaxTime;

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
    bool IsForkAvailable(Direction dir);
    virtual void Stop();

protected:
    virtual void MainThreadSetup() = 0;
    virtual void PhilBehaviour() = 0;
    size_t GetNeighbourIndexAtDirection(Direction dir);
    void SetState(State newState);

private:
    virtual void OnThreadSetup(){};

signals:
    void SignalStateChanged();
    void SignalDestroyed();
};

#endif // APHILTHREAD_H
