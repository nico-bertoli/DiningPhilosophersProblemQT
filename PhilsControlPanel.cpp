#include "PhilsControlPanel.h"
#include "PhilsPage.h"

using Algorithm = PhilsPage::Algorithm;

PhilsControlPanel::PhilsControlPanel(QWidget *parent) : QFrame{parent} {}

void PhilsControlPanel::showEvent(QShowEvent *event)
{
    Init();
    RefreshEnabledWidgets(false);
}

void PhilsControlPanel::Init()
{
    if(isInit)
        return;

    //--------------------------------- link widgets
    spinBoxSleepMinDur = this->findChild<QSpinBox*>("spinBoxSleepMinDur");
    spinBoxSleepMaxDur = this->findChild<QSpinBox*>("spinBoxSleepMaxDur");
    spinBoxEatMinDur = this->findChild<QSpinBox*>("spinBoxEatMinDur");
    spinBoxEatMaxDur = this->findChild<QSpinBox*>("spinBoxEatMaxDur");

    btnStartSimulation = this->findChild<QPushButton*>("btnStart");
    btnStopSimulation = this->findChild<QPushButton*>("btnStop");
    btnForceDeadlock = this->findChild<QPushButton*>("btnForceDeadlock");

    comboBoxAlgorithm = this->findChild<QComboBox*>("comboBoxAlgorithm");

    philsPage = dynamic_cast<PhilsPage*>(this->parent());

    //--------------------------------- connections
    connect(btnStartSimulation, &QPushButton::pressed, this, &PhilsControlPanel::SlotOnStartButtonPressed);
    connect(btnStopSimulation, &QPushButton::pressed, this, &PhilsControlPanel::SlotOnStopButtonPressed);
    connect(btnForceDeadlock, &QPushButton::pressed, this, &PhilsControlPanel::SlotOnForceDeadlockButtonPressed);

    connect(spinBoxSleepMinDur, &QSpinBox::valueChanged, this, &PhilsControlPanel::SlotOnSleepMinDurChanged);
    connect(spinBoxSleepMaxDur, &QSpinBox::valueChanged, this, &PhilsControlPanel::SlotOnSleepMaxDurChanged);
    connect(spinBoxEatMinDur, &QSpinBox::valueChanged, this, &PhilsControlPanel::SlotOnEatMinDurChanged);
    connect(spinBoxEatMaxDur, &QSpinBox::valueChanged, this, &PhilsControlPanel::SlotOnEatMaxDurChanged);

    //--------------------------------- customize widgets
    btnStartSimulation->setStyleSheet("QPushButton { background-color: lightgreen; color: black; }");
    btnStopSimulation->setStyleSheet("QPushButton { background-color: lightcoral; color: black; }");

    //--------------------------------- create widget lists
    widgetsToEnableWehnSimulationRunning.push_back(btnStopSimulation);

    widgetsToEnableWehnSimulationStopped.push_back(spinBoxSleepMinDur);
    widgetsToEnableWehnSimulationStopped.push_back(spinBoxSleepMaxDur);
    widgetsToEnableWehnSimulationStopped.push_back(spinBoxEatMinDur);
    widgetsToEnableWehnSimulationStopped.push_back(spinBoxEatMaxDur);
    widgetsToEnableWehnSimulationStopped.push_back(btnStartSimulation);
    widgetsToEnableWehnSimulationStopped.push_back(btnForceDeadlock);
    widgetsToEnableWehnSimulationStopped.push_back(comboBoxAlgorithm);

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

void PhilsControlPanel::RefreshEnabledWidgets(bool isSimulationRunning)
{
    for(auto& widget : widgetsToEnableWehnSimulationRunning)
            widget->setEnabled(isSimulationRunning);

    for(auto& widget : widgetsToEnableWehnSimulationStopped)
            widget->setEnabled(isSimulationRunning == false);
}

void PhilsControlPanel::SlotOnForceDeadlockButtonPressed()
{
    spinBoxSleepMaxDur->setValue(1);
    spinBoxSleepMinDur->setValue(1);
}

void PhilsControlPanel::SlotOnStartButtonPressed()
{
    philsPage->StartSimulation
    (
        spinBoxSleepMinDur->value(),
        spinBoxSleepMaxDur->value(),
        spinBoxEatMinDur->value(),
        spinBoxEatMaxDur->value(),
        static_cast<Algorithm>(comboBoxAlgorithm->currentIndex())
    );
    RefreshEnabledWidgets(true);
}

void PhilsControlPanel::SlotOnStopButtonPressed()
{
    philsPage->StopSimulation();
    RefreshEnabledWidgets(false);
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

