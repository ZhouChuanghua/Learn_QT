#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts>

#include <QtWidgets/QMainWindow>
#include <QtCore/QtMath>
#include <QtCharts/QValueAxis>

#include <iostream>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QBarCategoryAxis>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>

#include "chart.h"
#include "chartview.h"
#include "callout.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//private:
    Ui::MainWindow *ui;

    //在tab3上
    QChartView *chartView;
    QChart *chart;
    QLineSeries *series0;
    QLineSeries *series1;
    QLineSeries *series2;

    QLabel  *labXYValue; //状态栏显示文字标签

    bool    openTextByStream(const QString& aFileName);
    bool    openTextDATA_ByStream(const QString &aFileName);



    // 在tab4上
    Chart *m_chart;
    QList<QLineSeries *> m_series;
    //QLineSeries *m_series;

    ChartView *m_chartView;


    // 在tab3上
    QGraphicsSimpleTextItem *m_coordX;
    QGraphicsSimpleTextItem *m_coordY;

    Callout *m_tooltip;
    QList<Callout *> m_callouts;


private slots:
    // 在tab1上
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void on_pb_receive_clicked();
    void on_pb_send_clicked();
    void on_pb_closecan_clicked();

    // 在tab3上
    void on_pb_addchart_clicked();
    void on_pb_addchart2_clicked();
    void on_pb_tab3_1_clicked();

    void on_LegendMarkerClicked(); //图例单击

    void on_mouseMovePoint(QPoint point); //鼠标移动事件，自定义槽函数

    void on_actZoomReset_triggered(); //工具栏按钮，原始大小

    void on_actZoomIn_triggered(); //工具栏按钮，放大

    void on_actZoomOut_triggered(); //工具栏按钮，缩小

    void on_actOpen_TextStream_triggered();

    void on_pb_cv_clicked();
	
    // 在tab4上
	void addSeries();
    void removeSeries();
    void connectMarkers();
    void disconnectMarkers();

    void handleMarkerClicked();

    // 在tab3上
    void keepCallout();
    void tooltip(QPointF point, bool state);


    void on_pb_enlargeview_clicked();
};

#endif // MAINWINDOW_H
