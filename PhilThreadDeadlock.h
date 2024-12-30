#ifndef PHILTHREADDEADLOCK_H
#define PHILTHREADDEADLOCK_H

#include "APhilThread.h"

class PhilView;

class PhilThreadDeadlock : public APhilThread
{

//-------------------------------------------- Fields
private:
    static std::array<std::counting_semaphore<1>,4> forksSemaphores;

//-------------------------------------------- Methods
public:
    void Stop()override;

protected:
    void PhilBehaviour()override;
    void MainThreadSetup() override;

private:
    void CatchFork(Direction dir);
    void PutDownFork(Direction dir);
    void PutDownForks();
};

#endif // PHILTHREADDEADLOCK_H
