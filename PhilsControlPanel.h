#ifndef PHILSCONTROLPANEL_H
#define PHILSCONTROLPANEL_H

#include <QFrame>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <list>
#include <QWidget>
#include "PhilsPage.h"

class PhilsControlPanel : public QFrame
{
    Q_OBJECT
//------------------------------- Fields
private:
    bool isInit = false;
    PhilsPage* philsPage;

    QSpinBox* spinBoxSleepMinDur;
    QSpinBox* spinBoxSleepMaxDur;
    QSpinBox* spinBoxEatMinDur;
    QSpinBox* spinBoxEatMaxDur;

    QPushButton* btnStartSimulation;
    QPushButton* btnStopSimulation;
    QPushButton* btnForceDeadlock;

    QComboBox* comboBoxAlgorithm;

    std::list<QWidget*> widgetsToEnableWehnSimulationRunning;
    std::list<QWidget*> widgetsToEnableWehnSimulationStopped;

//------------------------------- Methods
public:
    explicit PhilsControlPanel(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *event) override;

private:
    void Init();
    void ForceSpinBoxesValid(QSpinBox* spinBoxValChanged, QSpinBox* spinBoxForceValid, bool mustChangedValBeGreater);
    void RefreshEnabledWidgets(bool isSimulationRunning);

private slots:
    void SlotOnStartButtonPressed();
    void SlotOnStopButtonPressed();
    void SlotOnForceDeadlockButtonPressed();

    void SlotOnSleepMinDurChanged();
    void SlotOnSleepMaxDurChanged();
    void SlotOnEatMinDurChanged();
    void SlotOnEatMaxDurChanged();
};

#endif // PHILSCONTROLPANEL_H
