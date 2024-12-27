#ifndef PHILTHREAD_H
#define PHILTHREAD_H

#include <atomic>

class PhilView;

class PhilThread
{
//-------------------------------------------- Fields
public:
enum class Algorithm{BusyWaiting};

private:
    enum class State{Thinking, Eating, Hungry};
    enum class ForkDir{Left,Right};
    State state = State::Thinking;
    size_t index;

    static size_t philsCount;
    static std::atomic<bool>* forksAvailability;

//-------------------------------------------- Methods
public:
    PhilThread
    (
        PhilView* philView,
        size_t philsCount,
        size_t index,
        float thinkMinTime,
        float thinkMaxTime,
        float eatMinTime,
        float eatMaxTime
    );

private:
    void PhilBehaviour(float thinkMinTime, float thinkMaxTime, float eatMinTime, float eatMaxTime);

    size_t GetLeftForkId(){return index;}
    size_t GetRightForkId(){return (index+1)%philsCount;}
    void SetForkAvailable(ForkDir dir, bool availability);
    bool IsForkAvailable(ForkDir dir);
};

#endif // PHILTHREAD_H
