#include "ForkView.h"
#include "QPushButton"
#include "PhilPage.h"

ForkView::ForkView(QWidget *parent) : QWidget{parent}{ }

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
        SetVisible(true);
    else
        SetVisible(false);
}

void ForkView::SetVisible(bool visibility)
{
    btnFork->setVisible(visibility);
    btnPlaceHolder->setVisible(visibility == false);
}

void ForkView::showEvent(QShowEvent *event)
{
    Init();
    SetVisible(true);
}

void ForkView::Init()
{
    if(isInit)
        return;

    auto a = this->objectName();
    int index = this->objectName().at(4).digitValue();

    btnFork = this->findChild<QPushButton*>("btnFork"+QString::number(index));
    btnPlaceHolder = this->findChild<QPushButton*>("btnPHolderFork"+QString::number(index));

    btnFork->setStyleSheet("background-color:"+PhilPage::BUTTONS_BACKGROUND_COLOR);
    btnPlaceHolder->setStyleSheet("background-color:"+PhilPage::BUTTONS_BACKGROUND_COLOR);

    assert(btnFork != nullptr);
    assert(btnPlaceHolder != nullptr);

    isInit = true;
}
