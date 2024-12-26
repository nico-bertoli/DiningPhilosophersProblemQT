#include "PhilPage.h"
#include "QPushButton"

PhilPage::PhilPage(QWidget *parent): QWidget{parent}
{

}

void PhilPage::showEvent(QShowEvent *event)
{
    QObject* phil = this->findChild<QObject*>("phil1");
    if (phil != nullptr)
        qInfo("trovato");
    else
        qInfo("non trovato");

    QWidget* fork12 = this->findChild<QWidget*>("fork12");
    if (fork12 != nullptr)
        qInfo("fork12 trovata");
    else
        qInfo("fork12 non trovata");
}


