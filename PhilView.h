#ifndef PHILVIEW_H
#define PHILVIEW_H

#include <QWidget>
#include <QPushButton>

class PhilView : public QWidget
{
    Q_OBJECT

//--------------------------------- Fields
    bool isInit = false;
    int index;
    QWidget* forkPrev;
    QWidget* forkNext;
    QPushButton* btnPhil;

//--------------------------------- Methods
public:
    explicit PhilView(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *event) override;

private:
    void Init();

signals:
};

#endif // PHILVIEW_H
