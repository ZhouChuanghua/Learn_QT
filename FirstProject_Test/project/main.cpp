#include "mainwindow.h"
#include <QApplication>
#include "chart.h"
#include "chartview.h"
#include <QtWidgets/QMainWindow>
#include <QtCore/QtMath>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    //w.grabGesture(Qt::PanGesture);
    //w.grabGesture(Qt::PinchGesture);


    w.show();

    return a.exec();
}
