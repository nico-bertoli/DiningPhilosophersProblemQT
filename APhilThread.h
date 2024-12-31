#ifndef APHILTHREAD_H
#define APHILTHREAD_H

#include <future>
#include <QObject>
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
    const size_t PHILS_COUNT = 4;   //todo this should be configurable at runtime
    static double eatMinTime;
    static double eatMaxTime;
    static double thinkMinTime;
    static double thinkMaxTime;

    bool mustTerminate = false;
    State state = State::Thinking;
    size_t index;

    //future linked to the runnig thread
    std::future<void> threadFuture;

    std::promise<void> forceWakeUpPromise;
    std::future<void> sleepFuture = forceWakeUpPromise.get_future();

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
    QString StateToQString(State state);
    bool IsForkAvailable(Direction dir);
    virtual void Terminate();

protected:
    size_t GetForkIndexAtDirection(Direction dir);
    size_t GetPhilIndexAtDirection(Direction dir);
    virtual void SetState(State newState);

private:
     virtual void MainThreadSetup() = 0;
     virtual void PhilBehaviour() = 0;

signals:
    void SignalStateChanged();
};

#endif // APHILTHREAD_H
