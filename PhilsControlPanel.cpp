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

    spinBoxSleepMinDur = this->findChild<QSpinBox*>("spinBoxSleepMinDur");
    spinBoxSleepMaxDur = this->findChild<QSpinBox*>("spinBoxSleepMaxDur");
    spinBoxEatMinDur = this->findChild<QSpinBox*>("spinBoxEatMinDur");
    spinBoxEatMaxDur = this->findChild<QSpinBox*>("spinBoxEatMaxDur");

    btnStartSimulation = this->findChild<QPushButton*>("btnStart");
    btnStopSimulation = this->findChild<QPushButton*>("btnStop");
    btnForceDeadlock = this->findChild<QPushButton*>("btnForceDeadlock");

    philPage = dynamic_cast<PhilPage*>(this->parent());

    connect(btnStartSimulation, &QPushButton::pressed, this, &PhilsControlPanel::SlotOnStartButtonPressed);
    connect(btnStopSimulation, &QPushButton::pressed, this, &PhilsControlPanel::SlotOnStopButtonPressed);
    connect(btnForceDeadlock, &QPushButton::pressed, this, &PhilsControlPanel::SlotOnForceDeadlockButtonPressed);

    connect(spinBoxSleepMinDur, &QSpinBox::valueChanged, this, &PhilsControlPanel::SlotOnSleepMinDurChanged);
    connect(spinBoxSleepMaxDur, &QSpinBox::valueChanged, this, &PhilsControlPanel::SlotOnSleepMaxDurChanged);
    connect(spinBoxEatMinDur, &QSpinBox::valueChanged, this, &PhilsControlPanel::SlotOnEatMinDurChanged);
    connect(spinBoxEatMaxDur, &QSpinBox::valueChanged, this, &PhilsControlPanel::SlotOnEatMaxDurChanged);

    isInit = true;
}

void PhilsControlPanel::ForceSpinBoxesValid(QSpinBox* spinBoxValChanged, QSpinBox* spinBoxForceValid, bool forceOtherGreater)
{
    int newVal = spinBoxValChanged->value();
    if(forceOtherGreater)
    {
        if(newVal > spinBoxForceValid->value())
            spinBoxForceValid->setValue(newVal);
    }
    else //other must be < spinBoxValChanged
    {
        if(newVal < spinBoxForceValid->value())
            spinBoxForceValid->setValue(newVal);
    }
}

void PhilsControlPanel::SlotOnForceDeadlockButtonPressed()
{
    spinBoxSleepMaxDur->setValue(1);
    spinBoxSleepMinDur->setValue(1);
}

void PhilsControlPanel::SlotOnStartButtonPressed()
{
    philPage->StartSimulation
        (
            spinBoxSleepMinDur->value(),
            spinBoxSleepMaxDur->value(),
            spinBoxEatMinDur->value(),
            spinBoxEatMaxDur->value()
            );
}

void PhilsControlPanel::SlotOnStopButtonPressed()
{
    philPage->StopSimulation();
}

void PhilsControlPanel::SlotOnSleepMinDurChanged()
{
    ForceSpinBoxesValid(spinBoxSleepMinDur,spinBoxSleepMaxDur,true);
}

void PhilsControlPanel::SlotOnSleepMaxDurChanged()
{
    ForceSpinBoxesValid(spinBoxSleepMaxDur,spinBoxSleepMinDur,false);
}

void PhilsControlPanel::SlotOnEatMinDurChanged()
{
    ForceSpinBoxesValid(spinBoxEatMinDur,spinBoxEatMaxDur,true);
}
void PhilsControlPanel::SlotOnEatMaxDurChanged()
{
    ForceSpinBoxesValid(spinBoxEatMaxDur,spinBoxEatMinDur,false);
}

