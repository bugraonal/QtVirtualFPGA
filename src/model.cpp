#include "model.h"

Model::Model()
{

}

void Model::recvData() {
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

void Model::process(QString tmpDir) {

    // this slot will be triggered after the model has been compiled.
    // It will start the model as a QProcess
    //QProcess model(this);
    model.setProcessChannelMode(QProcess::ForwardedChannels);
    model.setWorkingDirectory(tmpDir);
    model.setEnvironment(QProcess::systemEnvironment());
    QString command = tmpDir;
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
}

void Model::initSocket() {
    // Initialize UDP socket
    socket = new QUdpSocket;
    socket->bind(QHostAddress::LocalHost, 7755);
    connect(socket, &QUdpSocket::readyRead, this, &Model::recvData);

}

void Model::stopModel() {
    if (model.state() == QProcess::Running) {
        model.terminate();
    }
}

void Model::setDataToSend(QString data) { this->dataSent = data; }
