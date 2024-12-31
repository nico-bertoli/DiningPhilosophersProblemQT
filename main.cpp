#include "MainPage.h"

#include <QApplication>

extern QString styleSheet;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyleSheet(styleSheet);

    MainPage w;
    w.setWindowTitle("Multithreading Experiments");
    w.show();
    return a.exec();
}

const char* widgetColor = "#a3a7b8";
const char* disabledWidgetColor = "#373a40";
const char* disabledWidgetTextColor = "#585c66";

QString styleSheet = QString(R"(

QSpinBox { background-color: %1; color: black; }
QSpinBox:Disabled { background-color: %2; color: %3; }
QAbstractItemView { background-color: %1; color: black;}
QAbstractItemView::item:hover { background-color: #ffffff; color: black;}

QPushButton { background-color: %1; color: black; }
QPushButton:Disabled { background-color: %2; color: %3; }
QPushButton:Pressed { background-color: %1; color: black; }

QComboBox { background-color: %1; color: black; }
QComboBox:Disabled { background-color: %2; color: %3; }

)").arg(widgetColor,disabledWidgetColor,disabledWidgetTextColor);
