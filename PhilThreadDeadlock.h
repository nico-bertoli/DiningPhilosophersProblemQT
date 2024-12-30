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
    bool IsForkAvailable(Direction dir) override;

protected:
    void PhilBehaviour(float thinkMinTime, float thinkMaxTime, float eatMinTime, float eatMaxTime)override;
    void MainThreadSetup() override;

private:
    void CatchFork(Direction dir);
    void PutDownFork(Direction dir);
    void PutDownForks();
};

#endif // PHILTHREADDEADLOCK_H
