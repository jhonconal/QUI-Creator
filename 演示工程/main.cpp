#include "mainwindow.h"
#include "quiwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QUIWidget qui;
    qui.setStyle(QUIWidget::Style_PSBlack);
    MainWindow w;
    qui.setMainWidget(&w);
    qui.setTitle("3453454");
    qui.setAlignment(Qt::AlignCenter);
    qui.setVisible(QUIWidget::BtnMenu,true);
    qui.show();

    return a.exec();
}
