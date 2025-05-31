#ifndef PHILTHREADCHANDYMISRA_H
#define PHILTHREADCHANDYMISRA_H

#include <mutex>
#include <semaphore>
#include "APhilThread.h"

class PhilThreadChandyMisra : public APhilThread
{
//-------------------------------------------- Fields
private:
    static inline std::mutex philsStatesMutex;
    static inline std::array<State,4> philsStates;

    //each phil can sleep on its index semaphore
    static inline std::array<std::counting_semaphore<1>,4> philsSemaphores
    {
        std::counting_semaphore<1>{1},
        std::counting_semaphore<1>{1},
        std::counting_semaphore<1>{1},
        std::counting_semaphore<1>{1}
    };

//-------------------------------------------- Methods

private:
    void PhilBehaviour()override;
    void MainThreadSetup() override;
    void SetState(State newState)override;
    void TryEat();
};

#endif // PHILTHREADCHANDYMISRA_H
