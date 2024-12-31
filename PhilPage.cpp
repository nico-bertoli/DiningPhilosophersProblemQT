#include "PhilPage.h"
#include "QPushButton"
#include "QtLogging"
#include "PhilThreadHoldAndWait.h"
#include "PhilThreadDeadlockFree.h"
#include "PhilView.h"
#include "ForkView.h"
#include "QFrame"
#include "QGridLayout"
#include "dialog.h"

QString PhilPage::BUTTONS_BACKGROUND_COLOR = " #46474f;";

PhilPage::PhilPage(QWidget *parent): QWidget(parent){ }

void PhilPage::showEvent(QShowEvent *event) { Init(); }

void PhilPage::Init()
{
    static bool isInit = false;
    if(isInit)
        return;

    //link views
    for(int i = 0; i < PHILS_COUNT; ++i){
        philViews[i] = this->findChild<PhilView*>("phil"+QString::number(i));
        assert(philViews[i] != nullptr);
    }
    for(int i = 0; i < PHILS_COUNT; ++i){
        forkViews[i] = this->findChild<ForkView*>("fork"+QString::number(i));
        assert(forkViews[i] != nullptr);
    }

    //force fixed size for grid layout
    QWidget* philsGridPanel = this->findChild<QWidget*>("PhilsGridPanel");
    philsGridPanel->setFixedSize(800,800);
    philsGridPanel->layout()->setAlignment(philsGridPanel->layout()->widget(), Qt::AlignCenter);

    //connect back button
    QPushButton* btnBack = this->findChild<QPushButton*>("btnBack");
    connect(btnBack, &QPushButton::clicked, this, &PhilPage::SlotOnBackButtonClicked);

    isInit = true;
}

void PhilPage::StartSimulation
(
    float minSleepDur,
    float maxSleepDur,
    float minEatDur,
    float maxEatDur,
    Algorithm algorithm
)
{
    for(int i = 0; i < PHILS_COUNT; ++i)
    {
        auto& phil = philThreads[i];

        switch(algorithm)
        {
        case Algorithm::DeadlockFree:
            phil = std::make_shared<PhilThreadDeadlockFree>();
            break;
        case Algorithm::HoldAndWait:
            phil = std::make_shared<PhilThreadHoldAndWait>();
            break;
        }

        philViews[i]->ConnectToPhilThread(phil);
        forkViews[i]->ConnectToPhilThread(phil,Direction::Left);
        int rightForkIndex = i==0 ? PHILS_COUNT-1 : i-1;
        forkViews[rightForkIndex]->ConnectToPhilThread(philThreads[i],Direction::Right);

        phil->Run(i, minSleepDur, maxSleepDur, minEatDur, maxEatDur);
    }
}

void PhilPage::StopSimulation()
{
    for(auto& thread : philThreads)
    {
        if(thread == nullptr)
            continue;

        thread->Terminate();
        thread = nullptr;
    }
}

void PhilPage::SlotOnBackButtonClicked()
{
    StopSimulation();
    dynamic_cast<Dialog*>(this->parent()->parent())->ShowMainMenu();
}



























