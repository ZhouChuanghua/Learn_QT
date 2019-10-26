#include "qwchartview.h"

#include    <QChartView>
#include <QtDebug>
#include "callout.h"

QWChartView::QWChartView(QWidget *parent)
    : QChartView(parent),
      isClicking(0),
      xOld(0),
      yOld(0),
      m_coordX(0),
      m_coordY(0),
      m_tooltip(0)
{
    this->setDragMode(QGraphicsView::RubberBandDrag);
//    this->setRubberBand(QChartView::RectangleRubberBand);//设置为矩形选择方式
//    this->setRubberBand(QChartView::VerticalRubberBand);
    //this->setRubberBand(QChartView::HorizontalRubberBand);

    this->setMouseTracking(true);//必须开启此功能
    pressflg = 0;

    qDebug()<<"6";
    qDebug()<<xOld;

    m_coordX = new QGraphicsSimpleTextItem(chart());
    m_coordX->setPos(chart()->size().width()/2 - 50, chart()->size().height());
    m_coordX->setText("X: ");
    m_coordY = new QGraphicsSimpleTextItem(chart());
    m_coordY->setPos(chart()->size().width()/2 + 50, chart()->size().height());
    m_coordY->setText("Y: ");
}

QWChartView::~QWChartView()
{

}



void QWChartView::mousePressEvent(QMouseEvent *event)
{//鼠标左键按下，记录beginPoint
    if (event->button()==Qt::LeftButton)
    {
        beginPoint=event->pos();
        pressflg = 1;
    }
    else if(event->button()==Qt::RightButton)
    {
        this->setDragMode(QGraphicsView::ScrollHandDrag);
        isClicking = true;
    }

    qDebug()<<"1";
    QChartView::mousePressEvent(event);
}

void QWChartView::mouseMoveEvent(QMouseEvent *event)
{//鼠标移动事件
    QPoint  point;
    point=event->pos();

    int x, y;

    if (isClicking) {
        if (xOld == 0 && yOld == 0) {

        } else {
            x = event->x() - xOld;
            y = event->y() - yOld;
            chart()->scroll(-x, y);
        }

        xOld = event->x();
        yOld = event->y();

        qDebug()<<"movingchart";

        return;
    }
    qDebug()<<"2";

    emit mouseMovePoint(point);
    QChartView::mouseMoveEvent(event);
}


void QWChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (isClicking) {
        xOld = yOld = 0;
        isClicking = false;
    }

    this->setDragMode(QGraphicsView::RubberBandDrag);
    if (event->button()==Qt::LeftButton)
    { //鼠标左键释放，获取矩形框的endPoint,进行缩放
        endPoint=event->pos();
        QRectF  rectF;
        rectF.setTopLeft(this->beginPoint);
        rectF.setBottomRight(this->endPoint);
        if(pressflg == 1)
        {
            this->chart()->zoomIn(rectF);
        }
        qDebug()<<"41";
        qDebug()<<rectF;
    }
    else if (event->button()==Qt::RightButton)
        //this->chart()->zoomReset(); //鼠标右键释放，resetZoom
        qDebug()<<"3";
    qDebug()<<"4";
    pressflg = 0;
    QChartView::mouseReleaseEvent(event);
}

void QWChartView::keyPressEvent(QKeyEvent *event)
{//按键控制
    qDebug()<<"5";
    switch (event->key()) {
    case Qt::Key_Plus:  //+
        chart()->zoom(1.2);
        break;
    case Qt::Key_Minus:
        chart()->zoom(0.8);
        break;
    case Qt::Key_Left:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, -10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_PageUp:
        chart()->scroll(0, 50);
        break;
    case Qt::Key_PageDown:
        chart()->scroll(0, -50);
        break;
    case Qt::Key_Home:
        chart()->zoomReset();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
//    QGraphicsView::keyPressEvent(event);
}


void QWChartView::mouseDoubleClickEvent(QMouseEvent *event)
{
    assert(event);  // 从pulseview copy, unknown why
    if (event->button()==Qt::LeftButton)
    {
        chart()->zoomReset();
    }
    else if(event->button()==Qt::RightButton)
    {
        // 设置为纵向reset, 横向不变


    }

    qDebug()<<"8";
//    if (event->buttons() & Qt::LeftButton)
//        chart()->zoom(2.0);
//    else if (event->buttons() & Qt::RightButton)
//        chart()->zoom(-2.0);
}


void QWChartView::wheelEvent(QWheelEvent *event)
{
    assert(event);
    //chart()->zoomReset();
    qDebug()<<event->delta();
    qDebug()<<"9";

    if (event->orientation() == Qt::Vertical)
    {
        if (event->modifiers() & Qt::ControlModifier)
        {
            // Vertical scrolling with the control key pressed
            // is intrepretted as vertical scrolling
            //chart()->set_v_offset(-chart()->owner_visual_v_offset() -
            //   (event->delta() * height()) / (8 * 120));
            QValueAxis *axisXX = (QValueAxis*)(chart()->axisX());//父类转子类
            QVariant min = axisXX->min();
            QVariant max = axisXX->max();
            // Vertical scrolling is interpreted as zooming in/out
            //chart()->zoom(2.0);
            chart()->zoom(1 + 0.2*(event->delta() / abs(event->delta())));
            chart()->axisX()->setRange(min, max);
        }
        else
        {
            QValueAxis *axisYY = (QValueAxis*)(chart()->axisY());//父类转子类
            QVariant min = axisYY->min();
            QVariant max = axisYY->max();
            // Vertical scrolling is interpreted as zooming in/out
            //chart()->zoom(2.0);
            chart()->zoom(1 + 0.2*(event->delta() / abs(event->delta())));

            QRectF  rectF(0,1,2,2);
            //rectF.setTopLeft(this->beginPoint);
            //rectF.setBottomRight(this->beginPoint);
            //chart()->setPlotArea(rectF);
            //rectF = chart->axisX();


            chart()->axisY()->setRange(min, max);

            //chart()->axes().
            qDebug()<<(chart()->axisX());
        }
    }
    else if (event->orientation() == Qt::Horizontal)
    {
        // Horizontal scrolling is interpreted as moving left/right
        //chart()->set_scale_offset(chart()->scale(),
        //    event->delta() * chart()->scale() + chart()->offset());
        chart()->zoomReset();
    }
}





void QWChartView::keepCallout()
{
    m_callouts.append(m_tooltip);
    m_tooltip = new Callout(chart());
}

void QWChartView::tooltip(QPointF point, bool state)
{
    qDebug()<<"tooltip";
    if (m_tooltip == 0)
        m_tooltip = new Callout(chart());

    if (state) {
        m_tooltip->setText(QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y()));
        m_tooltip->setAnchor(point);
        m_tooltip->setZValue(11);
        m_tooltip->updateGeometry();
        m_tooltip->show();
    } else {
        m_tooltip->hide();
    }
}


