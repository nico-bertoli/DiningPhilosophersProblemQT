#ifndef PHILTHREAD_H
#define PHILTHREAD_H

#include "APhilThread.h"

class PhilView;

class PhilThread : public APhilThread
{

//-------------------------------------------- Fields
private:
    static std::array<std::counting_semaphore<1>,4> forksSemaphores;

//-------------------------------------------- Methods
public:
    // using APhilThread::APhilThread;
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

#endif // PHILTHREAD_H
