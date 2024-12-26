#include "PhilPage.h"
#include "QPushButton"
#include "QtLogging"

PhilPage::PhilPage(QWidget *parent): QWidget{parent}
{

}

void PhilPage::showEvent(QShowEvent *event)
{
    Init();
}

void PhilPage::Init()
{
    static bool isSetup = false;
    if(isSetup)
        return;

    for(int i = 0; i < PHILS_COUNT; ++i){
        phils[i] = this->findChild<PhilView*>("phil"+QString::number(i));
        assert(phils[i] != nullptr);
    }

    for(int i = 0; i < PHILS_COUNT; ++i){
        forks[i] = this->findChild<QWidget*>("fork"+QString::number(i));
        assert(forks[i] != nullptr);
    }

    QPushButton* btnStart = this->findChild<QPushButton*>("btnStart");
    connect(btnStart, &QPushButton::clicked, this, &PhilPage::SlotOnStartButtonPressed);

    isSetup = true;
}

void PhilPage::SlotOnStartButtonPressed()
{
    qInfo("start pressed");
}
