#include "MainPage.h"
#include "./ui_MainPage.h"
#include "QPushButton"
#include "QtLogging"

MainPage::MainPage(QWidget *parent):QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->btnPhilosophers,&QPushButton::clicked,this,&MainPage::SlotShowPhilosopersPage);
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::SlotShowPhilosopersPage()
{
    ui->stackedWidget->setCurrentWidget(ui->pagePhilosophers);
}

void MainPage::ShowMainMenu()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMainMenu);
}
