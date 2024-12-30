#ifndef PHILTHREADNODEADLOCK_H
#define PHILTHREADNODEADLOCK_H

#include <mutex>
#include "APhilThread.h"

using State = APhilThread::State;
using Direction = DirectionUtils::Direction;

//prevents deadlock removing hold and wait
class PhilThreadNoDeadlock : public APhilThread
{
//-------------------------------------------- Fields
private:
    static std::mutex mutex;
    static std::array<std::counting_semaphore<1>,4> philsSemaphores;
    static std::array<PhilThreadNoDeadlock*,4> phils;

//-------------------------------------------- Methods
public:
    void Stop()override;

protected:
    void PhilBehaviour()override;
    void MainThreadSetup() override;

private:
    void Eat();
    void TryEat();
    State GetPhilState(Direction dir);

    void OnThreadSetup()override;
};

#endif // PHILTHREADNODEADLOCK_H
