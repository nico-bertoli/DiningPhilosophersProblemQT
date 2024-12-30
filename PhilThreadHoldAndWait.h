#ifndef PHILTHREADHOLDANDWAIT_H
#define PHILTHREADHOLDANDWAIT_H

#include "APhilThread.h"

class PhilView;

class PhilThreadHoldAndWait : public APhilThread
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

#endif // PHILTHREADHOLDANDWAIT_H
