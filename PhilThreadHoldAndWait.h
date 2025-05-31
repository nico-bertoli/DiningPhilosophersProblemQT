#ifndef PHILTHREADHOLDANDWAIT_H
#define PHILTHREADHOLDANDWAIT_H

#include <semaphore>
#include "APhilThread.h"

class PhilView;

class PhilThreadHoldAndWait : public APhilThread
{

//-------------------------------------------- Fields
private:
    static std::array<std::counting_semaphore<1>,4> forksSemaphores;

//-------------------------------------------- Methods
public:
    void Terminate()override;

private:
    void PhilBehaviour()override;
    void MainThreadSetup() override;
    void CatchFork(DirectionUtils::Direction dir);
    void PutDownFork(DirectionUtils::Direction dir);
    void PutDownForks();
};

#endif // PHILTHREADHOLDANDWAIT_H
