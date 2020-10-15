#ifndef MODELTHREAD_H
#define MODELTHREAD_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QTemporaryDir>


#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>

class ModelWorker : public QObject
{
    Q_OBJECT

private:
    bool modelRunning = 0;
    QString dataSent = "0 0";
    QUdpSocket *socket;
//    QProcess model;

    void initSocket();
    void resetButtonData();

public slots:
    void doWork(const QString &parameter);
    void getDataToSend(QString data);
    void stopModel();
    void recvData();

signals:
    void resultReady(const QString &result);
    void parseDataReceived(QString data);
};

class ModelController : public QObject
{
    Q_OBJECT
    QThread workerThread;
    ModelWorker *worker;
public:
    ModelController();
    ~ModelController();
public slots:
    void handleDataReceived(QString);
    void handleDataToSend(QString data);
    void handleStopModel();
signals:
    void operate(const QString &);
    void stopModel();
    void sendDataReceived(QString);
    void sendDataToSend(QString data);
};


#endif // MODELTHREAD_H
