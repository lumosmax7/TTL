#ifndef MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>
#include <QString>
#include<QMessageBox>
#include<QTime>
#include"threadcal.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void portsAvailable();
    void countTime();
//    bool sendData(QString data);
    void sendData();
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_start_clicked();
    void logState();
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QList<QSerialPortInfo> serialPortList;
    QSerialPort *serial;
    QString t1,flag,flagStr,total,logData;
    QTime timeNow,timeCount;
    threadCal *T;
    QThread *thread;
    bool timeflag=false;

signals:
    void startThread();

};
#endif // MAINWINDOW_H
