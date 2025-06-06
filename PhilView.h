#ifndef PHILVIEW_H
#define PHILVIEW_H

#include <QWidget>
#include <QPushButton>
#include "DirectionUtils.h"

class APhilThread;

class PhilView : public QWidget
{
    Q_OBJECT

//--------------------------------- Fields
    bool isInit = false;
    int index;

    QWidget* forkRight;
    QWidget* forkLeft;
    QPushButton* btnPhil;
    QWidget* forkRightPlaceHolder;
    QWidget* forkLeftPlaceHolder;

    std::shared_ptr<APhilThread> philThread;

//--------------------------------- Methods
public:
    explicit PhilView(QWidget *parent = nullptr);
    void ConnectToPhilThread(std::shared_ptr<APhilThread> philThread);
    void DisconnectFromPhilThread();

protected:
    void showEvent(QShowEvent *event) override;

private:
    void Init();
    void ShowFork(DirectionUtils::Direction direction, bool show);

private slots:
    void SlotOnThreadStateChanged();
};

#endif // PHILVIEW_H
