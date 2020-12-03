#include "model.h"

Model::Model(QString tmpDir) : tmpDir(tmpDir)
{
#ifdef _WIN32
    process = WSLProcess();
#elif __linux__
    process = LinuxProcess();
#endif

}

Model::~Model() {

    if (model.state() == QProcess::Running) {
        model.terminate();
        model.close();
    }
    socket->close();
    delete socket;
    socket = nullptr;
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

void Model::compile(QStringList inputFileNames, QString simDelay, QString itPerCycle) {
    process.compileProcess(inputFileNames,simDelay,itPerCycle);
}

void Model::runModel() {
    process.runProcess();
}

void Model::initSocket() {
    // Initialize UDP socket
    socket = new QUdpSocket;
    socket->bind(QHostAddress::LocalHost, 7755);
    connect(socket, &QUdpSocket::readyRead, this, &Model::recvData);

}

void Model::stopModel() {
   process.stopModel();
}

void Model::setDataToSend(QString data) { this->dataSent = data; }
