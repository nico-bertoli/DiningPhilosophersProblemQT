#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class MainPage : public QDialog
{
    Q_OBJECT

public:
    MainPage(QWidget *parent = nullptr);
    ~MainPage();

    void ShowMainMenu();

private slots:
    void SlotShowPhilosopersPage();

private:
    Ui::Dialog *ui;
};
