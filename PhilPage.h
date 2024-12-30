#ifndef PHILPAGE_H
#define PHILPAGE_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include "ForkView.h"

class PhilView;
class APhilThread;

class PhilPage : public QWidget
{
    Q_OBJECT

template<typename T> using unique_ptr = std::unique_ptr<T>;

//---------------------------------------- Fields
public:
    static QString BUTTONS_BACKGROUND_COLOR;
    enum Algorithm {DeadlockFree, HoldAndWait};

private:
    static const size_t PHILS_COUNT = 4;

    //todo remove raw pointers
    ForkView* forks [PHILS_COUNT];
    PhilView* philViews [PHILS_COUNT];
    std::shared_ptr<APhilThread> philThreads[PHILS_COUNT];
    Algorithm algorithm = Algorithm::DeadlockFree;

//---------------------------------------- Methods
public:
    explicit PhilPage(QWidget *parent = nullptr);
    void StartSimulation(float minSleepDur, float maxSleepDur, float minEatDur, float maxEatDur);
    void StopSimulation();
    void SetAlgorithm(Algorithm algorithm){this->algorithm = algorithm;}

protected:
    void showEvent(QShowEvent *event) override;

private:
    void Init();

private slots:
    void SlotOnBackButtonClicked();
};

#endif // PHILPAGE_H
