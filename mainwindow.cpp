#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    portsAvailable();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::portsAvailable (){
    serialPortList = QSerialPortInfo::availablePorts();
    for(int i=0;i<serialPortList.length();i++){
        ui->portList->addItem((QString)serialPortList[i].portName());
    }
}


void MainWindow::on_pushButton_clicked()
{
    ui->portList->clear();
    portsAvailable();
}


void MainWindow::on_pushButton_2_clicked()
{
     QString  selectPort= ui->portList->currentText();;
     serial->setPortName(selectPort);
     serial->setBaudRate(9600);
     serial->setDataBits(QSerialPort::Data8);
     serial->setParity(QSerialPort::NoParity);
     serial->setStopBits(QSerialPort::OneStop);
     serial->setFlowControl(QSerialPort::NoFlowControl);

// here may comes problems
     if(!serial->open(QIODevice::ReadWrite)){
         QMessageBox::critical(NULL,"Tips","fail to open port");
     }
     else{
         qDebug()<<"open successfully";
     }

}


void MainWindow::on_pushButton_3_clicked()
{
    serial->close();
}



void MainWindow::on_start_clicked()
{
    t1= ui->t1->text();
    t2= ui->t2->text();
    t3= ui->t3->text();
    if(ui->pan->isChecked()){
        flag = PAN;
    }
    if(ui->rotate->isChecked()){
        flag= ROTATE;
    }
    countTime();
}

// write a thread to make it delay 1s;
void MainWindow::countTime(){
    static int i=0;
    i++;
    ui->lcdNumber->display(i);

}

