#ifndef FORKVIEW_H
#define FORKVIEW_H

#include <QPushButton>
#include "DirectionUtils.h"

using Direction = DirectionUtils::Direction;

class APhilThread;

class ForkView : public QWidget
{
    Q_OBJECT

//----------------------------------- Fields
private:
    int index;
    bool isInit = false;

    QPushButton* btnFork;
    QPushButton* btnPlaceHolder;

    std::shared_ptr<APhilThread> leftPhilThread;
    std::shared_ptr<APhilThread> rightPhilThread;

//----------------------------------- Methods
public:
    explicit ForkView(QWidget *parent = nullptr);
    void ConnectToPhilThread(std::shared_ptr<APhilThread> philThread, Direction philDirection);

protected:
    void showEvent(QShowEvent *event) override;

private:
    bool ShouldBeVisible();
    void Init();
    void TryDisconnectFromPhilThreads();

private slots:
    void SlotOnThreadStateChanged();
    void SetVisible(bool visibility);
};

#endif // FORKVIEW_H
