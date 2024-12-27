#include "ForkView.h"
#include "QPushButton"

ForkView::ForkView(QWidget *parent) : QPushButton{parent}
{

}

void ForkView::AttachToThreadPhil(PhilThread* philThread, Direction philDirection)
{
    if(philDirection == Direction::Right)
        rightPhilThread = philThread;
    else
        leftPhilThread = philThread;

    connect(philThread, &PhilThread::SignalStateChanged, this, &ForkView::SlotOnThreadStateChanged);
}

void ForkView::SlotOnThreadStateChanged()
{
    Direction updatedPhilDir = sender() == leftPhilThread ? Direction::Left : Direction::Right;
    PhilThread* updatedPhil = updatedPhilDir == Direction::Right ? rightPhilThread : leftPhilThread;

    qInfo() << "sender is right: " << (updatedPhilDir == Direction::Right);

    if(updatedPhil->IsForkAvailable(DirectionUtils::GetOppositeDirection(updatedPhilDir)))
        show();
    else
        hide();
}
