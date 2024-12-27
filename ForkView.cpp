#include "ForkView.h"
#include "QPushButton"
#include "PhilPage.h"

ForkView::ForkView(QWidget *parent) : QPushButton{parent}
{
    setStyleSheet("background-color:"+PhilPage::BUTTONS_BACKGROUND_COLOR);
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
    if(leftPhilThread->IsForkAvailable(Direction::Right) && rightPhilThread->IsForkAvailable(Direction::Left))
        show();
    else
        hide();
}
