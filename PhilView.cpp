#include "PhilView.h"
#include "PhilThread.h"
#include "PhilPage.h"
#include <QtLogging>

PhilView::PhilView(QWidget *parent):QWidget{parent}
{

}

void PhilView::AttachToPhilThread(PhilThread* philThread)
{
    this->philThread = philThread;
    connect(philThread, &PhilThread::SignalStateChanged, this, &PhilView::SlotOnThreadStateChanged);
}

void PhilView::SlotOnThreadStateChanged()
{
    PhilThread::State state = philThread->GetState();

    QIcon icon;
    switch(state)
    {
    case PhilThread::State::Thinking:
        forkLeft->hide();
        forkRight->hide();
        icon.addPixmap(QPixmap(":/philosophers/res/philosophers/Thinking.png"), QIcon::Disabled);
        break;
    case PhilThread::State::HungryNoForks:
        forkLeft->hide();
        forkRight->hide();
        icon.addPixmap(QPixmap(":/philosophers/res/philosophers/Hungry.png"), QIcon::Disabled);
        break;
    case PhilThread::State::HungryLeftFork:
        forkLeft->hide();
        forkRight->show();
        icon.addPixmap(QPixmap(":/philosophers/res/philosophers/Hungry.png"), QIcon::Disabled);
        break;
    case PhilThread::State::HungryRightFork:
        forkLeft->show();
        forkRight->hide();
        icon.addPixmap(QPixmap(":/philosophers/res/philosophers/Hungry.png"), QIcon::Disabled);
    case PhilThread::State::Eating:
        forkLeft->show();
        forkRight->show();
        icon.addPixmap(QPixmap(":/philosophers/res/philosophers/Eating.png"), QIcon::Disabled);
        break;
    }
    btnPhil->setIcon(icon);
}

void PhilView::showEvent(QShowEvent *event)
{
    Init();

    forkRight->hide();
    forkLeft->hide();
}

void PhilView::Init()
{
    if(isInit)
        return;

    int index = this->objectName().at(4).digitValue();

    assert(index != -1);

    btnPhil = this->findChild<QPushButton*>("btnPhil"+QString::number(index));
    forkRight = this->findChild<QWidget*>("forkRight"+QString::number(index));
    forkLeft = this->findChild<QWidget*>("forkLeft"+QString::number(index));

    assert(btnPhil != nullptr);
    assert(forkRight != nullptr);
    assert(forkLeft != nullptr);

    btnPhil->setStyleSheet("background-color:"+PhilPage::BUTTONS_BACKGROUND_COLOR);
    forkRight->setStyleSheet("background-color:"+PhilPage::BUTTONS_BACKGROUND_COLOR);
    forkLeft->setStyleSheet("background-color:"+PhilPage::BUTTONS_BACKGROUND_COLOR);

    isInit = true;
}
