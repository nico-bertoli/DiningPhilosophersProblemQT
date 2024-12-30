#include "dialog.h"

#include <QApplication>

extern QString styleSheet;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyleSheet(styleSheet);

    Dialog w;
    w.show();
    return a.exec();
}

const char* defaultWidgetColor = "#a3a7b8";

QString styleSheet = QString(R"(

QSpinBox { background-color: %1; color: black; }
QAbstractItemView { background-color: %1; color: black;}
QAbstractItemView::item:hover { background-color: #ffffff; color: black;}

QPushButton { background-color: %1; color: black; }
QPushButton:hover { background-color: #ffffff; color: black;}

QComboBox { background-color: %1; color: black; }

)").arg(defaultWidgetColor);
