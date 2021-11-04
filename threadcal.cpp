#include "threadcal.h"

threadCal::threadCal(QObject *parent) : QObject(parent)
{

}

void threadCal::logState(){
    while(isBreak==false){
        if(count>9){
            isBreak=true;
            emit isDone();
        }
        QThread::sleep(1);
        count++;
        emit logDate();

    }
}

void threadCal::setFlag(bool flag){
    isBreak=flag;
}
