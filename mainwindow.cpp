#include "mainwindow.h"
#include "ui_mainwindow.h"
#define PAN '0'
#define ROTATE '1'

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    portsAvailable();
    serial = new QSerialPort(this);
    T = new threadCal;
    thread =new QThread(this);
    T->moveToThread(thread);

    connect(T,&threadCal::logDate,this,&MainWindow::logState);
    connect(this,&MainWindow::startThread,T,&threadCal::logState);
    connect(T,&threadCal::isDone,this,&MainWindow::sendData);


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
     QString  selectPort= ui->portList->currentText();
     serial->setPortName(selectPort);
     serial->setBaudRate(9600);
     serial->setDataBits(QSerialPort::Data8);
     serial->setParity(QSerialPort::NoParity);
     serial->setStopBits(QSerialPort::OneStop);
     serial->setFlowControl(QSerialPort::NoFlowControl);
     if(!serial->open(QIODevice::ReadWrite)){
         QMessageBox::critical(NULL,"Tips","Fail to open the port");
     }
     else{
         ui->textBrowser->append("Open Successfully");
     }

}


void MainWindow::on_pushButton_3_clicked()
{

    if(serial->portName()==""){
        QMessageBox::critical(NULL,"Tips","Port isn't opened.");
    }
    else{
        serial->close();}

}



void MainWindow::on_start_clicked()
{

   if(thread->isRunning()==true){
       return;
   }
   thread->start();
   T->setFlag(false);
   emit startThread();



}


void MainWindow::logState(){
    t1= ui->t1->text();
    if(ui->pan->isChecked()){
        flag = PAN;
        flagStr="panning";
    }
    if(ui->rotate->isChecked()){
        flag= ROTATE;
        flagStr="rotating";
    }
    if(timeflag==false){
        timeCount.start();
        timeflag=true;
    }
    timeNow = QTime::currentTime();
    QString count;
    int tmp;
    tmp = 10 - timeCount.elapsed()/1000;
    count = QString::number(tmp);
    logData ="["+ timeNow.toString()+"]"+" Starting , after"+ count  +"s init, T1 is "+t1+" ms and mode is "+ flagStr+".";
    ui->textBrowser->append(logData);

}

void MainWindow::on_pushButton_4_clicked()
{
    ui->textBrowser->clear();
}


void MainWindow::sendData(){
    t1= ui->t1->text();
    if(ui->pan->isChecked()){
        flag = PAN;
        flagStr="panning";
    }
    if(ui->rotate->isChecked()){
        flag= ROTATE;
        flagStr="rotating";
    }
   total= t1+' '+flag;
   serial->write(total.toUtf8());
}

void MainWindow::on_pushButton_5_clicked()
{
    if(thread->isRunning()==false){
        return;
    }
    T->setFlag(true);
    thread->quit();
    thread->wait();
}

