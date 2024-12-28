#include "PhilsControlPanel.h"
#include "PhilPage.h"

PhilsControlPanel::PhilsControlPanel(QWidget *parent) : QFrame{parent} {}

void PhilsControlPanel::showEvent(QShowEvent *event)
{
    Init();
}

void PhilsControlPanel::Init()
{
    if(isInit)
        return;

    speenBoxSleepMinDur = this->findChild<QSpinBox*>("spinBoxSleepMinDur");
    speenBoxSleepMaxDur = this->findChild<QSpinBox*>("spinBoxSleepMaxDur");
    speenBoxEatMinDur = this->findChild<QSpinBox*>("speenBoxEatMinDur");
    speenBoxEatMaxDur = this->findChild<QSpinBox*>("speenBoxEatMaxDur");
    btnStartSimulation = this->findChild<QPushButton*>("btnStart");
    philPage = dynamic_cast<PhilPage*>(this->parent());

    assert(philPage != nullptr);

    connect(btnStartSimulation, &QPushButton::pressed, this, &PhilsControlPanel::SlotOnStartButtonPressed);

    isInit = true;
}

void PhilsControlPanel::SlotOnStartButtonPressed()
{
    philPage->StartSimulation(1,2,1,2);
}

