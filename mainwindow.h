#ifndef MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>
#include <QString>
#include<QMessageBox>
#define PAN 0
#define ROTATE 1

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
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_start_clicked();






private:
    Ui::MainWindow *ui;
    QList<QSerialPortInfo> serialPortList;
    QSerialPort *serial;
    QString t1,t2,t3;
    int flag;


};
#endif // MAINWINDOW_H
