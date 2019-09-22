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

#include <iostream>

#include "ControlCAN.H"
#pragma comment(lib,"controlcan.lib")


QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


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
