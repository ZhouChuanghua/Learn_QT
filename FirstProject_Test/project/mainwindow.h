#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void on_pb_receive_clicked();
    void on_pb_send_clicked();
    void on_pb_closecan_clicked();
};

#endif // MAINWINDOW_H
