#include "PhilPage.h"
#include "QPushButton"
#include "QtLogging"
#include "PhilThreadDeadlock.h"
#include "PhilThreadNoDeadLock.h"
#include "PhilView.h"
#include "QFrame"
#include "QGridLayout"
#include "dialog.h"

QString PhilPage::BUTTONS_BACKGROUND_COLOR = " #46474f;";

PhilPage::PhilPage(QWidget *parent): QWidget(parent)
{

}

void PhilPage::showEvent(QShowEvent *event)
{
    Init();
}

void PhilPage::Init()
{
    static bool isInit = false;
    if(isInit)
        return;

    for(int i = 0; i < PHILS_COUNT; ++i){
        philViews[i] = this->findChild<PhilView*>("phil"+QString::number(i));
        assert(philViews[i] != nullptr);
    }

    for(int i = 0; i < PHILS_COUNT; ++i){
        forks[i] = this->findChild<ForkView*>("fork"+QString::number(i));
        assert(forks[i] != nullptr);
    }

    //force fixed size for grid layout
    QWidget* philsGridPanel = this->findChild<QWidget*>("PhilsGridPanel");
    philsGridPanel->setFixedSize(800,800);
    philsGridPanel->layout()->setAlignment(philsGridPanel->layout()->widget(), Qt::AlignCenter);

    //todo check this is needed
    auto rootLayout = this->layout();
    for (int i = 0; i < rootLayout->count(); ++i)
    {
        QLayoutItem *item = rootLayout->itemAt(i);
        if (item->widget())
            rootLayout->setAlignment(item->widget(), Qt::AlignCenter);
    }

    QPushButton* btnBack = this->findChild<QPushButton*>("btnBack");
    connect(btnBack, &QPushButton::clicked, this, &PhilPage::SlotOnBackButtonClicked);

    isInit = true;
}

void PhilPage::StartSimulation(float minSleepDur, float maxSleepDur, float minEatDur, float maxEatDur)
{
    for(int i = 0; i < PHILS_COUNT; ++i)
    {
        switch(algorithm)
        {
        case Algorithm::DeadlockFree:
            philThreads[i] = std::make_shared<PhilThreadNoDeadlock>();
            break;
        case Algorithm::HoldAndWait:
            philThreads[i] = std::make_shared<PhilThreadDeadlock>();
            break;
        }

        philViews[i]->AttachToPhilThread(philThreads[i]);
        forks[i]->AttachToPhilThread(philThreads[i],Direction::Left);
        int rightForkIndex = i==0 ? PHILS_COUNT-1 : i-1;
        forks[rightForkIndex]->AttachToPhilThread(philThreads[i],Direction::Right);

        philThreads[i]->Run(i, minSleepDur, maxSleepDur, minEatDur, maxEatDur);
    }
}

void PhilPage::StopSimulation()
{
    for(auto& thread : philThreads)
    {
        thread->Stop();
        thread = nullptr;
    }
}

void PhilPage::SlotOnBackButtonClicked()
{
    StopSimulation();
    dynamic_cast<Dialog*>(this->parent()->parent())->ShowMainMenu();
}



























