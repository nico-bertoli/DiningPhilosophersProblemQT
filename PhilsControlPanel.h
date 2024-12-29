#ifndef PHILSCONTROLPANEL_H
#define PHILSCONTROLPANEL_H

#include <QFrame>
#include <QSpinBox>
#include <QPushButton>

class PhilPage;

class PhilsControlPanel : public QFrame
{
    Q_OBJECT
//------------------------------- Fields
private:
    bool isInit = false;

    QSpinBox* spinBoxSleepMinDur;
    QSpinBox* spinBoxSleepMaxDur;
    QSpinBox* spinBoxEatMinDur;
    QSpinBox* spinBoxEatMaxDur;
    QPushButton* btnStartSimulation;
    QPushButton* btnForceDeadlock;
    PhilPage* philPage;

//------------------------------- Methods
public:
    explicit PhilsControlPanel(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *event) override;

private:
    void Init();
    void ForceSpinBoxesValid(QSpinBox* spinBoxValChanged, QSpinBox* spinBoxForceValid, bool mustChangedValBeGreater);

private slots:
    void SlotOnStartButtonPressed();
    void SlotOnForceDeadlockButtonPressed();
    void SlotOnSleepMinDurChanged();
    void SlotOnSleepMaxDurChanged();
    void SlotOnEatMinDurChanged();
    void SlotOnEatMaxDurChanged();
};

#endif // PHILSCONTROLPANEL_H
