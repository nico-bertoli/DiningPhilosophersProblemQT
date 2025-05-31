#include "PhilView.h"
#include "APhilThread.h"
#include "PhilsPage.h"
#include <QtLogging>

using State = APhilThread::State;
using DirectionUtils::Direction;

PhilView::PhilView(QWidget *parent):QWidget{parent} { }

void PhilView::ConnectToPhilThread(std::shared_ptr<APhilThread> philThread)
{
    this->philThread = philThread;
    connect(philThread.get(), &APhilThread::SignalStateChanged, this, &PhilView::SlotOnThreadStateChanged);
}

void PhilView::DisconnectFromPhilThread()
{
    assert(philThread->GetState() == State::Terminated);
    disconnect(philThread.get(), &APhilThread::SignalStateChanged, this, &PhilView::SlotOnThreadStateChanged);
    philThread = nullptr;
}

void PhilView::SlotOnThreadStateChanged()
{
    if(philThread == nullptr)
        return;
    State state = philThread->GetState();

    QIcon icon;
    switch(state)
    {
    case State::Thinking:
    case State::Terminated:
        ShowFork(Direction::Left,false);
        ShowFork(Direction::Right,false);
        icon.addPixmap(QPixmap(":/philosophers/res/philosophers/Thinking.png"), QIcon::Disabled);
        if(state == State::Terminated)
             DisconnectFromPhilThread();
        break;

    case State::HungryNoForks:
        ShowFork(Direction::Left,false);
        ShowFork(Direction::Right,false);
        icon.addPixmap(QPixmap(":/philosophers/res/philosophers/Hungry.png"), QIcon::Disabled);
        break;

    case State::HungryLeftFork:
        ShowFork(Direction::Left,false);
        ShowFork(Direction::Right,true);
        icon.addPixmap(QPixmap(":/philosophers/res/philosophers/Hungry.png"), QIcon::Disabled);
        break;

    case State::HungryRightFork:
        ShowFork(Direction::Left,true);
        ShowFork(Direction::Right,false);
        icon.addPixmap(QPixmap(":/philosophers/res/philosophers/Hungry.png"), QIcon::Disabled);

    case State::Eating:
        ShowFork(Direction::Left,true);
        ShowFork(Direction::Right,true);
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

    //link widgets
    btnPhil = this->findChild<QPushButton*>("btnPhil"+QString::number(index));
    forkRight = this->findChild<QWidget*>("forkRight"+QString::number(index));
    forkLeft = this->findChild<QWidget*>("forkLeft"+QString::number(index));
    forkRightPlaceHolder = this->findChild<QWidget*>("forkRightPlaceHolder"+QString::number(index));
    forkLeftPlaceHolder = this->findChild<QWidget*>("forkLeftPlaceHolder"+QString::number(index));

    //set background color
    btnPhil->setStyleSheet("background-color:"+PhilsPage::SIMULATION_ITEMS_BACKGROUND_COLOR);
    forkRight->setStyleSheet("background-color:"+PhilsPage::SIMULATION_ITEMS_BACKGROUND_COLOR);
    forkLeft->setStyleSheet("background-color:"+PhilsPage::SIMULATION_ITEMS_BACKGROUND_COLOR);
    forkRightPlaceHolder->setStyleSheet("background-color:"+PhilsPage::SIMULATION_ITEMS_BACKGROUND_COLOR);
    forkLeftPlaceHolder->setStyleSheet("background-color:"+PhilsPage::SIMULATION_ITEMS_BACKGROUND_COLOR);

    isInit = true;
}

void PhilView::ShowFork(Direction direction, bool show)
{
    auto& fork = direction == Direction::Right ? forkRight : forkLeft;
    auto& placeHolder = direction == Direction::Right ? forkRightPlaceHolder : forkLeftPlaceHolder;

    fork->setVisible(show);
    placeHolder->setVisible(show == false);
}
