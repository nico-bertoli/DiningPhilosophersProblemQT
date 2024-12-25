#include "dialog.h"
#include "./ui_dialog.h"
#include "QPushButton"
#include "QtLogging"


Dialog::Dialog(QWidget *parent):QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);


    //-------------------- buttons connections
    connect(ui->btnPhilosophers,&QPushButton::clicked,this,&Dialog::SlotShowPhilosopersPage);
    connect(ui->btnMainMenu,&QPushButton::clicked,this,&Dialog::SlotShowMainMenu);

    Refresh();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::Refresh()
{
    ui->btnMainMenu->setEnabled(ui->stackedWidget->currentWidget() != ui->pageMainMenu);
}

void Dialog::SlotShowPhilosopersPage()
{
    ui->stackedWidget->setCurrentWidget(ui->pagePhilosophers);
    Refresh();
}

void Dialog::SlotShowMainMenu()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMainMenu);
    Refresh();
}
