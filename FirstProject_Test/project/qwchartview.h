﻿#ifndef QWCHARTVIEW_H
#define QWCHARTVIEW_H


#include    <QtCharts>  //必须这么设置
QT_CHARTS_USE_NAMESPACE     //必须这么设置


class QWChartView : public QChartView
{
    Q_OBJECT

private:
    QPoint  beginPoint; //选择矩形区的起点
    QPoint  endPoint;  //选择矩形区的终点
    int pressflg;       // 避免点击到lineseries上面之后, 无法产生chart::press事件, 造成缩放错误.

protected:


    void mouseDoubleClickEvent(QMouseEvent *event);


    void wheelEvent(QWheelEvent *event);


public:
    void mousePressEvent(QMouseEvent *event); //鼠标左键按下
    void mouseMoveEvent(QMouseEvent *event); //鼠标移动
    void mouseReleaseEvent(QMouseEvent *event); //鼠标释放左键
    void keyPressEvent(QKeyEvent *event); //按键事件


    explicit QWChartView(QWidget *parent = 0);
    ~QWChartView();

signals:
    void mouseMovePoint(QPoint point); //鼠标移动信号，在mouseMoveEvent()事件中触发
};

#endif // QWCHARTVIEW_H
