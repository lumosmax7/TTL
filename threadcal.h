#ifndef THREADCAL_H
#define THREADCAL_H

#include <QObject>
#include"QThread"
#include"QTime"

class threadCal : public QObject
{
    Q_OBJECT
public:
    explicit threadCal(QObject *parent = nullptr);
    void logState();
    void setFlag(bool isBreak= false);
    int count=0;

signals:
    void logDate();
    void isDone();

private:
    bool isBreak;

};

#endif // THREADCAL_H
