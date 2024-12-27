#ifndef PHILTHREAD_H
#define PHILTHREAD_H

#include <future>
#include <atomic>
#include "QString"

class PhilView;

class PhilThread
{
//-------------------------------------------- Fields
public:
enum class Algorithm{BusyWaiting};

private:
    enum class State {Thinking, HungryNoForks, HungryLeftFork, HungryRightFork, Eating};
    enum class ForkDir{Left,Right};
    State state = State::Thinking;
    size_t index;

    static size_t philsCount;
    static std::atomic<bool>* forksAvailability;

    std::future<void> future;

//-------------------------------------------- Methods
public:
    PhilThread
    (
        PhilView* philView,
        size_t index,
        float thinkMinTime,
        float thinkMaxTime,
        float eatMinTime,
        float eatMaxTime
    );

    static void SetupPhilsCount(size_t newPhilsCount){philsCount = newPhilsCount;}

private:
    void PhilBehaviour(float thinkMinTime, float thinkMaxTime, float eatMinTime, float eatMaxTime);

    size_t GetLeftForkId(){return index;}
    size_t GetRightForkId(){return (index+1)%philsCount;}
    void SetForkAvailable(ForkDir dir, bool availability);
    bool IsForkAvailable(ForkDir dir);

    void SetState(State newState);
    QString GetStateString(State state);

    void MainThreadSetup();
};

#endif // PHILTHREAD_H
