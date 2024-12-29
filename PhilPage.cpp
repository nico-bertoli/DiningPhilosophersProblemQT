#include "PhilPage.h"
#include "QPushButton"
#include "QtLogging"
#include "PhilThread.h"
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
        forks[i] = this->findChild<ForkView*>("fork"+QString::number(i));
        assert(forks[i] != nullptr);
    }

    PhilThread::SetupPhilsCount(PHILS_COUNT);

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

    isSetup = true;
}

void PhilPage::StartSimulation(float minSleepDur, float maxSleepDur, float minEatDur, float maxEatDur)
{
    for(int i = 0; i < PHILS_COUNT; ++i)
    {
        philThreads[i] = std::make_shared<PhilThread>(i, minSleepDur, maxSleepDur, minEatDur, maxEatDur);
        philViews[i]->AttachToPhilThread(philThreads[i]);
        forks[i]->AttachToPhilThread(philThreads[i],Direction::Left);
        int rightForkIndex = i==0 ? PHILS_COUNT-1 : i-1;
        forks[rightForkIndex]->AttachToPhilThread(philThreads[i],Direction::Right);
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



























