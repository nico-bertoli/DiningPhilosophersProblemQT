#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void ShowMainMenu();

private slots:
    void SlotShowPhilosopersPage();

private:
    Ui::Dialog *ui;
};
