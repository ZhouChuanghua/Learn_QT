#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts>
#include "chart.h"
#include "chartview.h"
#include <QtWidgets/QMainWindow>
#include <QtCore/QtMath>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //![1]
        QLineSeries *series = new QLineSeries();
        for (int i = 0; i < 500; i++) {
            QPointF p((qreal) i, qSin(M_PI / 50 * i) * 100);
            p.ry() += qrand() % 20;
            *series << p;
        }
    //![1]

        Chart *chart = new Chart();
//        chart->addSeries(series);
        chart->setTitle("Zoom in/out example");
        chart->setAnimationOptions(QChart::NoAnimation);
        chart->legend()->hide();
        chart->createDefaultAxes();

        ChartView *chartView = new ChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        ui->gridLayout_tab->addWidget(chartView);

}

MainWindow::~MainWindow()
{
    delete ui;
}
