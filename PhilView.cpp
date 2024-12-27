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
        forkNext->hide();
        forkPrev->hide();
        icon.addPixmap(QPixmap(":/philosophers/res/philosophers/Eating.png"), QIcon::Disabled);
        break;
    case PhilThread::State::HungryNoForks:
        forkNext->hide();
        forkPrev->hide();
        icon.addPixmap(QPixmap(":/philosophers/res/philosophers/Hungry.png"), QIcon::Disabled);
        break;
    case PhilThread::State::HungryLeftFork:
        forkNext->hide();
        forkPrev->show();
        icon.addPixmap(QPixmap(":/philosophers/res/philosophers/Hungry.png"), QIcon::Disabled);
        break;
    case PhilThread::State::HungryRightFork:
        forkNext->show();
        forkPrev->hide();
        icon.addPixmap(QPixmap(":/philosophers/res/philosophers/Hungry.png"), QIcon::Disabled);
    case PhilThread::State::Eating:
        forkNext->show();
        forkPrev->show();
        icon.addPixmap(QPixmap(":/philosophers/res/philosophers/Eating.png"), QIcon::Disabled);
        break;
    }
    btnPhil->setIcon(icon);
}

void PhilView::showEvent(QShowEvent *event)
{
    Init();

    forkPrev->hide();
    forkNext->hide();
}

void PhilView::Init()
{
    if(isInit)
        return;

    int index = this->objectName().at(4).digitValue();

    assert(index != -1);

    btnPhil = this->findChild<QPushButton*>("btnPhil"+QString::number(index));
    forkPrev = this->findChild<QWidget*>("forkPrev"+QString::number(index));
    forkNext = this->findChild<QWidget*>("forkNext"+QString::number(index));

    assert(btnPhil != nullptr);
    assert(forkPrev != nullptr);
    assert(forkNext != nullptr);

    btnPhil->setStyleSheet("background-color:"+PhilPage::BUTTONS_BACKGROUND_COLOR);
    forkPrev->setStyleSheet("background-color:"+PhilPage::BUTTONS_BACKGROUND_COLOR);
    forkNext->setStyleSheet("background-color:"+PhilPage::BUTTONS_BACKGROUND_COLOR);

    isInit = true;
}
