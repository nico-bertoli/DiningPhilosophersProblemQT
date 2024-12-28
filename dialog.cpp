#include "dialog.h"
#include "./ui_dialog.h"
#include "QPushButton"
#include "QtLogging"


Dialog::Dialog(QWidget *parent):QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->btnPhilosophers,&QPushButton::clicked,this,&Dialog::SlotShowPhilosopersPage);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::SlotShowPhilosopersPage()
{
    ui->stackedWidget->setCurrentWidget(ui->pagePhilosophers);
}

void Dialog::ShowMainMenu()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMainMenu);
}
