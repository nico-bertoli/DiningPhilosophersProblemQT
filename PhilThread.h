#ifndef PHILTHREAD_H
#define PHILTHREAD_H

#include <future>
#include <atomic>
#include <QObject>
#include "QString"
#include "DirectionUtils.h"

class PhilView;

using Direction = DirectionUtils::Direction;

class PhilThread : public QObject
{
    Q_OBJECT
//-------------------------------------------- Fields
public:
enum class Algorithm{BusyWaiting};
enum class State {Thinking, HungryNoForks, HungryLeftFork, HungryRightFork, Eating};
// enum class ForkDir{Left,Right};

private:
    State state = State::Thinking;
    size_t index;

    static size_t philsCount;
    static std::atomic<bool>* forksAvailability;

    std::future<void> future;

//-------------------------------------------- Methods
public:
    explicit PhilThread
    (
        size_t index,
        float thinkMinTime,
        float thinkMaxTime,
        float eatMinTime,
        float eatMaxTime,
        QObject* parent = nullptr
    );

    State GetState(){return state;}
    QString GetStateString(State state);
    static void SetupPhilsCount(size_t newPhilsCount){philsCount = newPhilsCount;}
    bool IsForkAvailable(Direction dir);

private:
    void PhilBehaviour(float thinkMinTime, float thinkMaxTime, float eatMinTime, float eatMaxTime);

    size_t GetLeftForkId(){return index;}
    size_t GetRightForkId(){return (index+1)%philsCount;}
    void SetForkAvailable(Direction dir, bool availability);
    void SetState(State newState);
    void MainThreadSetup();

signals:
    void SignalStateChanged();
};

#endif // PHILTHREAD_H
