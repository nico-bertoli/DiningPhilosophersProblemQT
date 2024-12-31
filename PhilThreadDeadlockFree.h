#ifndef PHILTHREADDEADLOCKFREE_H
#define PHILTHREADDEADLOCKFREE_H

#include <mutex>
#include <semaphore>
#include "APhilThread.h"

using State = APhilThread::State;
using Direction = DirectionUtils::Direction;

class PhilThreadDeadlockFree : public APhilThread
{
//-------------------------------------------- Fields
private:
    static std::mutex philsStatesMutex;
    static std::array<State,4> philsStates;
    //each phil can sleep on its index semaphore
    static std::array<std::counting_semaphore<1>,4> philsSemaphores;

//-------------------------------------------- Methods

private:
    void PhilBehaviour()override;
    void MainThreadSetup() override;
    void SetState(State newState)override;
    void TryEat();
};

#endif // PHILTHREADDEADLOCKFREE_H
