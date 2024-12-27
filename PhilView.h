#ifndef PHILVIEW_H
#define PHILVIEW_H

#include <QWidget>
#include <QPushButton>

class PhilThread;

class PhilView : public QWidget
{
    Q_OBJECT

//--------------------------------- Fields
    bool isInit = false;
    int index;
    QWidget* forkPrev;
    QWidget* forkNext;
    QPushButton* btnPhil;

    PhilThread* philThread;

//--------------------------------- Methods
public:
    explicit PhilView(QWidget *parent = nullptr);
    void AttachToPhilThread(PhilThread* philThread);

protected:
    void showEvent(QShowEvent *event) override;

private:
    void Init();

private slots:
    void SlotOnThreadStateChanged();
};

#endif // PHILVIEW_H
