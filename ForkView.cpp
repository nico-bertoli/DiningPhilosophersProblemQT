#include "ForkView.h"
#include "QPushButton"
#include "PhilsPage.h"
#include "APhilThread.h"

using State = APhilThread::State;
using DirectionUtils::Direction;

ForkView::ForkView(QWidget *parent) : QWidget{parent}{ }

void ForkView::showEvent(QShowEvent *event)
{
    Init();
    SetVisible(true);
}

void ForkView::Init()
{
    if(isInit)
        return;

    int index = this->objectName().at(4).digitValue();

    btnFork = this->findChild<QPushButton*>("btnFork"+QString::number(index));
    btnPlaceHolder = this->findChild<QPushButton*>("btnPHolderFork"+QString::number(index));

    btnFork->setStyleSheet("background-color:"+PhilsPage::SIMULATION_ITEMS_BACKGROUND_COLOR);
    btnPlaceHolder->setStyleSheet("background-color:"+PhilsPage::SIMULATION_ITEMS_BACKGROUND_COLOR);

    assert(btnFork != nullptr);
    assert(btnPlaceHolder != nullptr);

    isInit = true;
}

void ForkView::ConnectToPhilThread(std::shared_ptr<APhilThread> philThread, Direction philDirection)
{
    if(philDirection == Direction::Right)
        rightPhilThread = philThread;
    else
        leftPhilThread = philThread;

    connect(philThread.get(), &APhilThread::SignalStateChanged, this, &ForkView::SlotOnThreadStateChanged);
}

void ForkView::SlotOnThreadStateChanged()
{
    SetVisible(ShouldBeVisible());
    TryDisconnectFromPhilThreads();
}

bool ForkView::ShouldBeVisible()
{
    return (leftPhilThread == nullptr || leftPhilThread->IsForkAvailable(Direction::Right)) &&
           (rightPhilThread == nullptr || rightPhilThread->IsForkAvailable(Direction::Left));
}

void ForkView::TryDisconnectFromPhilThreads()
{
    if(leftPhilThread != nullptr && leftPhilThread->GetState() == State::Terminated)
    {
        disconnect(leftPhilThread.get(), &APhilThread::SignalStateChanged, this, &ForkView::SlotOnThreadStateChanged);
        leftPhilThread = nullptr;
    }
    if(rightPhilThread != nullptr && rightPhilThread->GetState() == State::Terminated)
    {
        disconnect(rightPhilThread.get(), &APhilThread::SignalStateChanged, this, &ForkView::SlotOnThreadStateChanged);
        rightPhilThread = nullptr;
    }
}

void ForkView::SetVisible(bool visibility)
{
    btnFork->setVisible(visibility);
    btnPlaceHolder->setVisible(visibility == false);
}
