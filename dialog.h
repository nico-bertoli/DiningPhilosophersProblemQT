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

private:
    void Refresh();

private slots:
    void SlotShowPhilosopersPage();
    void SlotShowMainMenu();

private:
    Ui::Dialog *ui;
};
