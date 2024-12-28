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
    spinBoxEatMinDur = this->findChild<QSpinBox*>("spinBoxEatMinDur");
    spinBoxEatMaxDur = this->findChild<QSpinBox*>("spinBoxEatMaxDur");
    btnStartSimulation = this->findChild<QPushButton*>("btnStart");
    philPage = dynamic_cast<PhilPage*>(this->parent());

    assert(philPage != nullptr);

    connect(btnStartSimulation, &QPushButton::pressed, this, &PhilsControlPanel::SlotOnStartButtonPressed);

    isInit = true;
}

void PhilsControlPanel::SlotOnStartButtonPressed()
{
    philPage->StartSimulation
    (
        speenBoxSleepMinDur->value(),
        speenBoxSleepMaxDur->value(),
        spinBoxEatMinDur->value(),
        spinBoxEatMaxDur->value()
    );
}

