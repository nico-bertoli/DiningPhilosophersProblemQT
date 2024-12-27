#include "PhilPage.h"
#include "QPushButton"
#include "QtLogging"
#include "PhilThread.h"
#include "PhilView.h"

PhilPage::PhilPage(QWidget *parent): QWidget(parent)
{

}

void PhilPage::showEvent(QShowEvent *event)
{
    Init();

    // if(philThreads != nullptr)
    //     for(auto philThread : philThreads)
    //         if(philThread != nullptr)
    //             delete(philThread);
}

void PhilPage::Init()
{
    static bool isSetup = false;
    if(isSetup)
        return;

    for(int i = 0; i < PHILS_COUNT; ++i){
        philViews[i] = this->findChild<PhilView*>("phil"+QString::number(i));
        assert(philViews[i] != nullptr);
    }

    for(int i = 0; i < PHILS_COUNT; ++i){
        forks[i] = this->findChild<QWidget*>("fork"+QString::number(i));
        assert(forks[i] != nullptr);
    }

    QPushButton* btnStart = this->findChild<QPushButton*>("btnStart");
    connect(btnStart, &QPushButton::clicked, this, &PhilPage::SlotOnStartButtonPressed);

    PhilThread::SetupPhilsCount(PHILS_COUNT);

    isSetup = true;
}

void PhilPage::SlotOnStartButtonPressed()
{
    qInfo("start pressed");

    for(int i = 0; i < PHILS_COUNT; ++i)
    {
        qInfo()<<"starting phil "<<i;
        philThreads[i] = new PhilThread(i, 1,5,1,5);
        philViews[i]->AttachToPhilThread(philThreads[i]);
    }
}
