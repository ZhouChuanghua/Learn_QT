#include "mainwindow.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtCore/QDebug>
#include <QtCharts/QLegend>
#include <QtWidgets/QFormLayout>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QLineSeries>
#include <QtCharts/QXYLegendMarker>
#include <QtCore/QtMath>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include "iostream"
#include "QTextStream"
#include "chart.h"
#include "chartview.h"
#include <QtCore/QRandomGenerator>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

MainWindow::MainWindow()
{
    setWindowTitle(tr("window2"));
//![1]
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < 500; i++) {
        QPointF p((qreal) i, qSin(M_PI / 50 * i) * 100);
        p.ry() += QRandomGenerator::global()->bounded(20);
        *series << p;
    }
    QLineSeries *series2 = new QLineSeries();
    for (int i = 0; i < 500; i++) {
        QPointF p((qreal) i, qSin(M_PI / 100 * i) * 100);
        p.ry() += QRandomGenerator::global()->bounded(20);
        *series2 << p;
    }
//![1]

    Chart *chart = new Chart();
    series->setName("series1");
    series->setUseOpenGL(true);
    chart->addSeries(series);
    series2->setUseOpenGL(true);
    chart->addSeries(series2);
    chart->setTitle("Zoom in/out example");
    chart->setAnimationOptions(QChart::NoAnimation);
    chart->legend()->setAlignment(Qt::AlignLeft);
    chart->legend()->show();
    chart->createDefaultAxes();

    ChartView *chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    setCentralWidget(chartView);
    std::cout << "tet";

}


