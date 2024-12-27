#ifndef FORKVIEW_H
#define FORKVIEW_H

#include <QPushButton>
#include "PhilThread.h"
#include "DirectionUtils.h"

using Direction = DirectionUtils::Direction;

class ForkView : public QPushButton
{
    Q_OBJECT

//----------------------------------- Fields
private:
    PhilThread* leftPhilThread;
    PhilThread* rightPhilThread;

//----------------------------------- Methods
public:
    explicit ForkView(QWidget *parent = nullptr);
    void AttachToThreadPhil(PhilThread* philThread, Direction philDirection);

private slots:
    void SlotOnThreadStateChanged();
};

#endif // FORKVIEW_H
