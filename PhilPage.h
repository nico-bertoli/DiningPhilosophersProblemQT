#ifndef PHILPAGE_H
#define PHILPAGE_H

#include <QObject>
#include <QWidget>
#include "ForkView.h"

class PhilView;
class PhilThread;

class PhilPage : public QWidget
{
    Q_OBJECT

template<typename T> using unique_ptr = std::unique_ptr<T>;

//---------------------------------------- Fields
public:
    static QString BUTTONS_BACKGROUND_COLOR;
private:
    static const size_t PHILS_COUNT = 4;

    //todo remove raw pointers
    ForkView* forks [PHILS_COUNT];
    PhilView* philViews [PHILS_COUNT];
    PhilThread* philThreads[PHILS_COUNT];

//---------------------------------------- Methods
public:
    explicit PhilPage(QWidget *parent = nullptr);
    void StartSimulation(float minSleepDur, float maxSleepDur, float minEatDur, float maxEatDur);

protected:
    void showEvent(QShowEvent *event) override;

private:
    void Init();
};

#endif // PHILPAGE_H
