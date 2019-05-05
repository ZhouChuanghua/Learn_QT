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
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow()
{
//    setWindowTitle(tr("window2"));
//![1]
//    QLineSeries *series = new QLineSeries();
//    for (int i = 0; i < 500; i++) {
//        QPointF p((qreal) i, qSin(M_PI / 50 * i) * 100);
//        p.ry() += QRandomGenerator::global()->bounded(20);
//        *series << p;
//    }
//    QLineSeries *series2 = new QLineSeries();
//    for (int i = 0; i < 500; i++) {
//        QPointF p((qreal) i, qSin(M_PI / 100 * i) * 100);
//        p.ry() += QRandomGenerator::global()->bounded(20);
//        *series2 << p;
//    }
//![1]

//    Chart *chart = new Chart();
//    series->setName("series1");
//    series->setUseOpenGL(true);
//    chart->addSeries(series);
//    series2->setUseOpenGL(true);
//    chart->addSeries(series2);
//    chart->setTitle("Zoom in/out example");
//    chart->setAnimationOptions(QChart::NoAnimation);
//    chart->legend()->setAlignment(Qt::AlignLeft);
//    chart->legend()->show();
//    chart->createDefaultAxes();

//    ChartView *chartView = new ChartView(chart);
//    chartView->setRenderHint(QPainter::Antialiasing);

//    setCentralWidget(chartView); // 此处注释掉
    std::cout << "tet";


    // Create chart view with the chart
    m_chart = new Chart();
    m_chartView = new ChartView(m_chart, this);

    // Create layout for grid and detached legend
//    m_mainLayout = new QGridLayout();
//    m_mainLayout->addWidget(m_chartView, 0, 1, 3, 1);
//    setLayout(m_mainLayout);

    setCentralWidget(m_chartView);

    // Add few series
    addSeries();
    addSeries();
    addSeries();
    addSeries();

    connectMarkers();

    // Set the title and show legend
    m_chart->setTitle("Legendmarker example (click on legend)");
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignLeft);

    m_chartView->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::addSeries()
{
    QLineSeries *series = new QLineSeries();
    m_series.append(series);

    series->setName(QString("line " + QString::number(m_series.count())));

    // Make some sine wave for data
    QList<QPointF> data;
    int offset = m_chart->series().count();
    for (int i = 0; i < 360; i++) {
        qreal x = offset * 20 + i;
        qreal xd = QRandomGenerator::global()->bounded(5);
        data.append(QPointF(i, qSin(qDegreesToRadians(x)) + xd ));
    }

    series->append(data);
    series->setUseOpenGL(true);
    m_chart->addSeries(series);

    if (m_series.count() == 1)
        m_chart->createDefaultAxes();
}

void MainWindow::removeSeries()
{
    // Remove last series from chart
    if (m_series.count() > 0) {
        QLineSeries *series = m_series.last();
        m_chart->removeSeries(series);
        m_series.removeLast();
        delete series;
    }
}

void MainWindow::connectMarkers()
{
//![1]
    // Connect all markers to handler
    const auto markers = m_chart->legend()->markers();
    for (QLegendMarker *marker : markers) {
        // Disconnect possible existing connection to avoid multiple connections
        QObject::disconnect(marker, &QLegendMarker::clicked,
                            this, &MainWindow::handleMarkerClicked);
        QObject::connect(marker, &QLegendMarker::clicked, this, &MainWindow::handleMarkerClicked);
    }
//![1]
}

void MainWindow::disconnectMarkers()
{
////![2]
//    const auto markers = m_chart->legend()->markers();
//    for (QLegendMarker *marker : markers) {
//        QObject::disconnect(marker, &QLegendMarker::clicked,
//                            this, &MainWidget::handleMarkerClicked);
//    }
////![2]
}

void MainWindow::handleMarkerClicked()
{
//![3]
    QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());
    Q_ASSERT(marker);
//![3]

//![4]
    switch (marker->type())
//![4]
    {
        case QLegendMarker::LegendMarkerTypeXY:
        {
//![5]
            // Toggle visibility of series
            marker->series()->setVisible(!marker->series()->isVisible());

            // Turn legend marker back to visible, since hiding series also hides the marker
            // and we don't want it to happen now.
            marker->setVisible(true);
//![5]

//![6]
            // Dim the marker, if series is not visible
            qreal alpha = 1.0;

            if (!marker->series()->isVisible())
                alpha = 0.5;

            QColor color;
            QBrush brush = marker->labelBrush();
            color = brush.color();
            color.setAlphaF(alpha);
            brush.setColor(color);
            marker->setLabelBrush(brush);

            brush = marker->brush();
            color = brush.color();
            color.setAlphaF(alpha);
            brush.setColor(color);
            marker->setBrush(brush);

            QPen pen = marker->pen();
            color = pen.color();
            color.setAlphaF(alpha);
            pen.setColor(color);
            marker->setPen(pen);

//![6]
            break;
        }

        default:
        {
            qDebug() << "Unknown marker type";
            break;
        }
    }
}


