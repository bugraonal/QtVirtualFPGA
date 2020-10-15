#include "modelthread.h"


void ModelWorker::initSocket() {
    // Initialize UDP socket
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 7755);
    connect(socket, &QUdpSocket::readyRead, this, &ModelWorker::recvData);

}

void ModelWorker::recvData() {
    // This slot will be triggered when a UDP datagram is received
    // A response will be sent and the data received will be sent (with a signal)
    // to the main thread for parsing
    char dat[100];
    QNetworkDatagram datagram;
    while(socket->hasPendingDatagrams()) {
        datagram = socket->receiveDatagram();
        strcpy(dat, datagram.data().data());
    }
    socket->writeDatagram(dataSent.toStdString().c_str(), 5, datagram.senderAddress(), datagram.senderPort());

    emit parseDataReceived(QString(dat));
}

void ModelWorker::doWork(const QString &parameter) {
    // this slot will be triggered after the model has been compiled.
    // It will start the model as a QProcess
    QProcess model(this);
    model.setProcessChannelMode(QProcess::ForwardedChannels);
    model.setWorkingDirectory(parameter);
    model.setEnvironment(QProcess::systemEnvironment());
    QString command = parameter;
    command.append("/VirtualFPGAProject");
    std::cout << "Running project file at: " <<
                 command.toStdString() << std::endl;
    QStringList args;
    args.clear();

    connect(&model, &QProcess::errorOccurred, [&](){
        std::cout << "Error ocurred: " << model.errorString().toStdString() << std::endl;});

    initSocket();

    model.start(command, args);
    model.waitForStarted();
    if (model.state() == QProcess::Running)
        modelRunning = 1;
    else {
        std::cerr << "Model error:" << model.error() << std::endl;
        return;
    }
    modelRunning = 1;
    while (modelRunning) {
        //std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    if (model.state() == QProcess::Running) {
        model.terminate();
    }
}

void ModelWorker::stopModel() { modelRunning = false; }

void ModelWorker::getDataToSend(QString data) { dataSent = data; }

ModelController::ModelController() {
    worker = new ModelWorker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &ModelController::operate, worker, &ModelWorker::doWork);
    connect(worker, &ModelWorker::parseDataReceived, this, &ModelController::handleDataReceived, Qt::QueuedConnection);
    connect(this, &ModelController::sendDataToSend, worker, &ModelWorker::getDataToSend);
    connect(this, &ModelController::stopModel, worker, &ModelWorker::stopModel);
    workerThread.start();
}

ModelController::~ModelController() {
    workerThread.quit();
    workerThread.wait();
}

void ModelController::handleDataReceived(QString data) { emit sendDataReceived(data); }
void ModelController::handleDataToSend(QString data) { emit sendDataToSend(data); }
void ModelController::handleStopModel() { emit SIGNAL(this->stopModel()); }
