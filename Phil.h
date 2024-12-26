#ifndef PHIL_H
#define PHIL_H

#include <QWidget>
#include <QPushButton>

class Phil : public QWidget
{
    Q_OBJECT

//--------------------------------- Fields
    int index;
    QWidget* forkPrev;
    QWidget* forkNext;
    QPushButton* btnPhil;

//--------------------------------- Methods
public:
    explicit Phil(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *event) override;

private:
    void Init();

signals:
};

#endif // PHIL_H
