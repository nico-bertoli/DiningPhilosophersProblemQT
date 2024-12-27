#ifndef PHILTHREAD_H
#define PHILTHREAD_H

#include "PhilView.h"

class PhilThread
{
//-------------------------------------------- Fields
public:
enum class Algorithm{BusyWaiting};

private:
    enum class State{Thinking, Eating, Hungry};
    State state = State::Thinking;

//-------------------------------------------- Methods
public:
    PhilThread(PhilView* philView, Algorithm algorithm, float thinkMinTime, float thinkMaxTime, float eatMinTime, float eatMaxTime);

private:
    static void PhilBehaviour(Algorithm algorithm, float thinkMinTime, float thinkMaxTime, float eatMinTime, float eatMaxTime);
};

#endif // PHILTHREAD_H
