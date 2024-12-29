#ifndef PHILTHREAD_H
#define PHILTHREAD_H

#include <future>
#include <atomic>
#include <QObject>
#include "QString"
#include "DirectionUtils.h"
#include "QDebug"

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
    static std::atomic<bool>* forksAvailability;
    static size_t philsCount;

    bool mustStop = false;
    State state = State::Thinking;
    size_t index;
    std::future<void> threadFuture;
    std::mutex forksAvailabilityMutex;

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

    ~PhilThread(){qInfo()<<"thread" << index << "destroyed";}

    State GetState(){return state;}
    QString GetStateString(State state);
    static void SetupPhilsCount(size_t newPhilsCount){philsCount = newPhilsCount;}
    bool IsForkAvailable(Direction dir);
    void Stop(){mustStop = true;}

private:
    void PhilBehaviour(float thinkMinTime, float thinkMaxTime, float eatMinTime, float eatMaxTime);

    size_t GetLeftForkIndex(){return index == 0 ? philsCount - 1 : index -1;}
    size_t GetRightForkIndex(){return index;}
    void SetForkAvailable(Direction dir, bool availability);
    void SetState(State newState);
    void MainThreadSetup();

signals:
    void SignalStateChanged();
    // void SignalDestroyed();
};

#endif // PHILTHREAD_H
