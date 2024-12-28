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

    QSpinBox* speenBoxSleepMinDur;
    QSpinBox* speenBoxSleepMaxDur;
    QSpinBox* speenBoxEatMinDur;
    QSpinBox* speenBoxEatMaxDur;
    QPushButton* btnStartSimulation;
    PhilPage* philPage;

//------------------------------- Methods
public:
    explicit PhilsControlPanel(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *event) override;

private:
    void Init();

private slots:
    void SlotOnStartButtonPressed();
};

#endif // PHILSCONTROLPANEL_H
