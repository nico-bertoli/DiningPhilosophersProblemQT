#ifndef PHILSPAGE_H
#define PHILSPAGE_H

#include <QWidget>

class PhilView;
class APhilThread;
class ForkView;

class PhilsPage : public QWidget
{
    Q_OBJECT

//---------------------------------------- Fields
public:
    static QString SIMULATION_ITEMS_BACKGROUND_COLOR;
    enum Algorithm {DeadlockFree, HoldAndWait};

private:
    static const size_t PHILS_COUNT = 4;

    ForkView* forkViews [PHILS_COUNT];
    PhilView* philViews [PHILS_COUNT];
    std::shared_ptr<APhilThread> philThreads[PHILS_COUNT];

//---------------------------------------- Methods
public:
    explicit PhilsPage(QWidget *parent = nullptr);
    void StopSimulation();
    void StartSimulation
    (
        float minSleepDur,
        float maxSleepDur,
        float minEatDur,
        float maxEatDur,
        Algorithm algorithm
    );

protected:
    void showEvent(QShowEvent *event) override;

private:
    void Init();

private slots:
    void SlotOnBackButtonClicked();
};

#endif // PHILSPAGE_H
