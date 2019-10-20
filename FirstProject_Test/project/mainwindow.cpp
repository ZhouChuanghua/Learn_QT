#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts>
//#include "chart.h"
//#include "chartview.h"
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

#include    "qwchartview.h"




#include "ControlCAN.H"
#pragma comment(lib,"controlcan.lib")


QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //chartView = new QChartView();
    //ui->grid_tab2->addWidget(chartView, 1, 0);

    chart = new QChart();
    //chartView->setChart(chart);

    ui->gv_tab3->setChart(chart);
    // Set the title and show legend
    chart->setTitle("Legendmarker example (click on legend)");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignLeft);

    ui->gv_tab3->setRenderHint(QPainter::Antialiasing);


    series0 = new QLineSeries();
    series0->setUseOpenGL(true);
    series1 = new QLineSeries();
    series1->setUseOpenGL(true);

    chart->addSeries(series0);
    chart->addSeries(series1);

    //connect(series0, &QLineSeries::pressed, ui->gv_tab3, &QWChartView::mousePressEvent);


//    QLineSeries *series100[100];
//    for(int i = 0; i < 100; i++)
//    {
//        series100[i] = new QLineSeries();
//        //series100[i] = ;
//        chart->addSeries(series100[i]);

//    }

    // connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    VCI_INIT_CONFIG init_config;
    VCI_BOARD_INFO infor;

    int status = 0;

    ui->listWidget_printzz->addItem("sdfsf");
    //ui->listWidget_printzz->moveCursor();

    status = VCI_OpenDevice(4,0,0);
    if(status == STATUS_OK)
    {
    //    ui->
        VCI_ReadBoardInfo(4,0,&infor);
        std::cout<<"Open: OK"<<std::endl;
        ui->label_canopen->setText("Can Open OK");

    }
    else
    {
        std::cout<<("Open failed: ")<<std::endl;
        ui->label_canopen->setText("Can Open failed");
        return;
    }
    init_config.AccCode = 0;
    init_config.AccMask = 0xffffffff;
    init_config.Filter = 0;
    init_config.Mode = 0;
    init_config.Timing0 = (UCHAR)1;
    init_config.Timing1 = (UCHAR)0x1c;

    status = VCI_InitCAN(4,0,0,&init_config);
    if(status == STATUS_OK)
    {
        std::cout<<"Init: OK"<<std::endl;
        ui->label_canopen->setText("Can INITED OK");
    }
    else
    {
        std::cout<<"Init: failed"<<std::endl;
        ui->label_canopen->setText("Can INITED failed");
    }
    VCI_ReadBoardInfo(4,0,&infor);



}

void MainWindow::on_pushButton_2_clicked()
{
    if(VCI_StartCAN(4,0,0) == 1)
    {
        std::cout<<"Start: OK"<<std::endl;
        ui->label_canopen->setText("Can INITED");
    }
}

void MainWindow::on_pb_receive_clicked()
{
    VCI_CAN_OBJ* frameinfo;
    VCI_ERR_INFO errinfo;
    int len=1;
    int i=0;
    QString str = "";
    QString strall = "";

    unsigned long Num = VCI_GetReceiveNum(4,0,0);

    if(Num > 0)
    {
        frameinfo = new VCI_CAN_OBJ[Num];

        std::cout<<"Receive: YES "<<std::endl;

        len = VCI_Receive(4,0,0,frameinfo,Num,200);

        if(len<=0)
        {
            //注意：如果没有读到数据则必须调用此函数来读取出当前的错误码，
            //千万不能省略这一步（即使你可能不想知道错误码是什么）
            VCI_ReadErrInfo(4,0,0,&errinfo);
        }
        else
        {
            std::cout<<"Receive: YES2 "<<std::endl;
            for(i = 0; i < Num; i++)
            {
                strall = str.setNum(frameinfo[i].Data[0], 16) + " ";
                strall += str.setNum(frameinfo[i].Data[1], 16) + " ";
                strall += str.setNum(frameinfo[i].Data[2], 16) + " ";
                strall += str.setNum(frameinfo[i].Data[3], 16) + " ";
                strall += str.setNum(frameinfo[i].Data[4], 16) + " ";
                strall += str.setNum(frameinfo[i].Data[5], 16) + " ";
                strall += str.setNum(frameinfo[i].Data[6], 16) + " ";
                strall += str.setNum(frameinfo[i].Data[7], 16);

                ui->listWidget_Data->addItem(strall);
                ui->listWidget_Data->scrollToBottom();
            }
        }
    }
    else {
        std::cout<<"Receive: NONE "<<std::endl;
    }


}

void MainWindow::on_pb_send_clicked()
{
    int nSendNum = 10;
    VCI_CAN_OBJ *frameinfo = new VCI_CAN_OBJ[nSendNum];

    for (int i = 0; i<nSendNum; i++)
    {
        frameinfo[i].DataLen = 8;

        frameinfo[i].Data[0] = i;

        frameinfo[i].RemoteFlag = 0;
        frameinfo[i].ExternFlag = 0;

        frameinfo[i].ID = 0x00000080;
        frameinfo[i].SendType = 0;
    }

    if(VCI_Transmit(4,0,0,frameinfo,nSendNum) != 0)
    {
        std::cout<<"Send: OK"<<std::endl;
    }
}

void MainWindow::on_pb_closecan_clicked()
{
    int status = 0;
    status = VCI_CloseDevice(4,0);
    std::cout<<("Can Closed: ")<<std::endl;
    std::cout<<(status)<<std::endl;
    ui->label_canopen->setText("Can Closed");

}

void MainWindow::on_pb_addchart_clicked()
{

}

void MainWindow::on_pb_addchart2_clicked()
{

}

void MainWindow::on_pb_tab3_1_clicked()
{
    qreal t = 0, y1, y2, intv = 0.1;
    int cnt = 200;
    for(int i = 0; i < cnt; i++)
    {
        y1 = qSin(t+30);
        series0->append(t, y1);
        y2 = qSin(t + 60);
        series1->append(t, y2);
        t += intv;
    }

    //创建坐标轴
        QValueAxis *axisX = new QValueAxis; //X 轴
        axisX->setRange(0, 10); //设置坐标轴范围
    //    axisX->setLabelFormat("%.1f"); //标签格式
    //    axisX->setTickCount(11); //主分隔个数
    //    axisX->setMinorTickCount(4);
        axisX->setTitleText("time(secs)"); //标题
    //    axisX->setGridLineVisible(false);

        QValueAxis *axisY = new QValueAxis; //Y 轴
        axisY->setRange(-2, 2);
        axisY->setTitleText("value");
    //    axisY->setTickCount(5);
    //    axisY->setMinorTickCount(4);
    //    axisY->setLabelFormat("%.2f"); //标签格式
    //    axisY->setGridLineVisible(false);

        chart->setAxisX(axisX, series0); //为序列设置坐标轴
        chart->setAxisY(axisY, series0); //

        chart->setAxisX(axisX, series1); //为序列设置坐标轴
        chart->setAxisY(axisY, series1); //

        foreach (QLegendMarker* marker, chart->legend()->markers()) {
            QObject::disconnect(marker, SIGNAL(clicked()), this, SLOT(on_LegendMarkerClicked()));
            QObject::connect(marker, SIGNAL(clicked()), this, SLOT(on_LegendMarkerClicked()));
        }



}



void MainWindow::on_LegendMarkerClicked()
{
    QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());

    switch (marker->type())
    {
        case QLegendMarker::LegendMarkerTypeXY:
        {
            marker->series()->setVisible(!marker->series()->isVisible());
            marker->setVisible(true);
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
            break;
        }
        default:
            break;
    }


}




void MainWindow::on_mouseMovePoint(QPoint point)
{ //鼠标移动响应
    QPointF pt=ui->gv_tab3->chart()->mapToValue(point); //转换为图表的数值
    labXYValue->setText(QString::asprintf("X=%.1f,Y=%.2f",pt.x(),pt.y())); //状态栏显示
}

void MainWindow::on_actZoomReset_triggered()
{ //恢复原始大小
    ui->gv_tab3->chart()->zoomReset();
}

void MainWindow::on_actZoomIn_triggered()
{//放大
    ui->gv_tab3->chart()->zoom(1.2);
}

void MainWindow::on_actZoomOut_triggered()
{//缩小
    ui->gv_tab3->chart()->zoom(0.8);
}


bool MainWindow::openTextByStream(const QString &aFileName)
{
    //用 QTextStream打开文本文件
    QFile   aFile(aFileName);

    if (!aFile.exists()) //文件不存在
        return false;

    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream aStream(&aFile); //用文本流读取文件
    aStream.setAutoDetectUnicode(true); //自动检测Unicode,才能正常显示文档内的汉字



    QString read_data = aStream.readAll();
    //QString read_data = aStream.readLine();
    ui->textEditStream->setPlainText(read_data);

    QStringList tempOption = read_data.split("\n");         //每行以\n区分

    // 允许config最大行数为5000行. 做config的时候注意这里.
    QStringList tempbar[5000];

    for(int i = 0 ; i < tempOption.count() ; i++)
    {
         tempbar[i] = tempOption.at(i).split(","); //一行中的单元格以，区分
    }

//    ui->textEditStream->clear();//清空
//    while (!aStream.atEnd())
//    {
//        str=aStream.readLine();//读取文件的一行
//        ui->textEditStream->appendPlainText(str); //添加到文本框显示
//    }

    aFile.close();//关闭文件
    ui->tabWidget->setCurrentIndex(1);
    return  true;
}



void MainWindow::on_actOpen_TextStream_triggered()
{ //打开文件
    QString curPath=QDir::currentPath();//获取系统当前目录
    //调用打开文件对话框打开一个文件
    QString aFileName=QFileDialog::getOpenFileName(this,"打开一个文件",curPath,
                 "程序文件(*.h *cpp *txt *csv);;文本文件(*.txt);;所有文件(*.*)");

    if (aFileName.isEmpty())
        return; //如果未选择文件，退出
    openTextByStream(aFileName); //打开文件

}



bool MainWindow::openTextDATA_ByStream(const QString &aFileName)
{
    //用 QTextStream打开文本文件
    QFile   aFile(aFileName);

    if (!aFile.exists()) //文件不存在
        return false;

    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream aStream(&aFile); //用文本流读取文件
    aStream.setAutoDetectUnicode(true); //自动检测Unicode,才能正常显示文档内的汉字



    QString read_data = aStream.readAll();
    //QString read_data = aStream.readLine();
    ui->textEditStream->setPlainText(read_data);

    QStringList tempOption = read_data.split("\n");         //每行以\n区分

    // 允许data最大行数为50000行.
    QStringList tempbar[50000];
    QString dstr[50000];
    int datacount = tempOption.count() - 1;
    for(int i = 1 ; i < datacount; i++)
    {
        tempbar[i] = tempOption.at(i).split("\t"); //一行中的单元格以，区分
        dstr[i] = tempbar[i].at(2);
    }

    int value[50000];
    for(int i = 1 ; i < datacount; i++)
    {
        QString  str = dstr[i].mid(65, 2) + dstr[i].mid(62, 2);//[62] + dstr[11][63];//tempbar[41][2].at(66);

        value[i] = str.toInt(NULL, 16);

         qDebug()<<str;
        // qDebug()<<value[i];
    }

//    ui->textEditStream->clear();//清空
//    while (!aStream.atEnd())
//    {
//        str=aStream.readLine();//读取文件的一行
//        ui->textEditStream->appendPlainText(str); //添加到文本框显示
//    }

    aFile.close();//关闭文件
    ui->tabWidget->setCurrentIndex(1);

    series2 = new QLineSeries();
    qreal t = 0, y1, intv = 0.1;
    for(int i = 0; i < datacount; i++)
    {
        y1 = value[i];
        series2->append(t, y1);
        t += intv;
    }


    series2->setUseOpenGL(true);
    chart->addSeries(series2);

    return  true;
}


void MainWindow::on_pb_cv_clicked()
{
    //打开文件
    QString curPath=QDir::currentPath();//获取系统当前目录
    //调用打开文件对话框打开一个文件
    QString aFileName=QFileDialog::getOpenFileName(this,"打开一个文件",curPath,
                 "程序文件(*.h *cpp *txt *csv);;文本文件(*.txt);;所有文件(*.*)");

    if (aFileName.isEmpty())
        return; //如果未选择文件，退出
    openTextDATA_ByStream(aFileName); //打开文件

}
