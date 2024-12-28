#ifndef FORKVIEW_H
#define FORKVIEW_H

#include <QPushButton>
#include "PhilThread.h"
#include "DirectionUtils.h"

using Direction = DirectionUtils::Direction;

class ForkView : public QWidget
{
    Q_OBJECT

//----------------------------------- Fields
private:
    int index;
    bool isInit = false;

    QPushButton* btnFork;
    QPushButton* btnPlaceHolder;

    PhilThread* leftPhilThread;
    PhilThread* rightPhilThread;

//----------------------------------- Methods
public:
    explicit ForkView(QWidget *parent = nullptr);
    void AttachToThreadPhil(PhilThread* philThread, Direction philDirection);

protected:
    void showEvent(QShowEvent *event) override;

private:
    void Init();

private slots:
    void SlotOnThreadStateChanged();
    void SetVisible(bool visibility);
};

#endif // FORKVIEW_H
