#include "model.h"

Model::Model(QString tmpDir) : tmpDir(tmpDir)
{

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
    // This slot will copy the files in the project folder
    // to a temporary folder.
    // It will start the CMake and then Make proceses as
    // QProcesses. Their error messages are forwareded to the
    // console
    QDir tempDir = QDir(tmpDir);
    if (tempDir.entryList().isEmpty()) {
        std::cerr << "No files added" << std::endl;
        return;
    }
    // Move these to mainWindow
    // ui->configFrame->setDisabled(true);
    // ui->StartButton->setDisabled(true);

    QStringList projectFiles = {    ":/projectFiles/projectFiles/CMakeLists.txt",
                                    ":/projectFiles/projectFiles/sim_main.cpp",
                                    ":/projectFiles/projectFiles/UDPClient.hpp"};
    for (auto f : projectFiles) {
        QFile file(f);
        file.copy(tempDir.filePath(f.section("/", -1, -1)));
    }

    for (auto f : inputFileNames) {
        QFile in(f);
        in.copy(tempDir.filePath(f.section("/", -1, -1)));
    }
    QString command = "cmake";
    QStringList args;
    args << "-DSIM_DLY=" + simDelay << "-DIT=" + itPerCycle << ".";
    QProcess cmake;
    cmake.setProcessChannelMode(QProcess::ForwardedErrorChannel);
    cmake.setWorkingDirectory(tempDir.path());
    cmake.start(command, args);
    //while(cmake.state() == QProcess::Running);
    cmake.waitForFinished();
    if (cmake.exitStatus() != QProcess::NormalExit || cmake.exitCode() != 0) {
        std::cerr << "CMake error" << std::endl;
        return;
    }
    //cmake.close();
    command = "cmake";
    args.clear();
    args << "--build" << ".";
    QProcess make;

    make.setProcessChannelMode(QProcess::ForwardedErrorChannel);
    make.setWorkingDirectory(tempDir.path());
    make.start(command, args);
    //while(make.state() == QProcess::Running);
    make.waitForFinished();
    if (make.exitStatus() != QProcess::NormalExit || make.exitCode() != 0) {
        std::cerr << "Make error" << std::endl;
        return;
    }
    //make.terminate();
    cmake.close();
    make.close();


}

void Model::runModel() {

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
        model.close();
    }
    socket->close();
}

void Model::setDataToSend(QString data) { this->dataSent = data; }
