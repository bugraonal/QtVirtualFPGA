#include "wslprocess.h"

WSLProcess::WSLProcess()
{

}

QString WSLProcess::makeTmpDir()
{
    QString command;
    QStringList args;
    command = "wsl";
    args << "-- mktemp -t VirtualFPGA-XXXXX -d" <<;
    process.start(command,args);
    process.waitForFinished();
    process.setProcessChannelMode(QProcess::SeparateChannels);
    auto stdoutput = process.readAllStandardOutput();
    return QString(stdoutput);
}

void runProcess()
{
    process.setProcessChannelMode(QProcess::ForwardedChannels);
    process.setWorkingDirectory(tmpDir);
    process.setEnvironment(QProcess::systemEnvironment());
    QString command = "wsl";
    QStringList args;
    args << "-- " + tmpdir + "/VirtualFPGAProject";

    std::cout << "Running project file at: " <<
                 command.toStdString() << std::endl;

    connect(&process, &QProcess::errorOccurred, [&](){
        std::cout << "Error ocurred: " << process.errorString().toStdString() << std::endl;});

//  initSocket(); // TODO: moved to main window

    process.start(command, args);
    process.waitForStarted();
    if (process.state() != QProcess::Running)
       {
        std::cerr << "Model error:" << process.error() << std::endl;
        return;
    }


}
void compileProcess(QStringList inputFileNames, QString simDelay, QString itPerCycle)
{
    QDir tempDir = QDir(makeTmpDir());
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
    copyFiles(projectFiles);
    copyFiles(inputFileNames);

    QString command = "wsl";
    QStringList args;
    args << "-- cmake"<<"-DSIM_DLY=" + simDelay << "-DIT=" + itPerCycle << ".";
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
    command = "wsl";
    args.clear();
    args << "-- cmake --build" << ".";

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

void stopModel()
{
    if (process.state() == QProcess::Running) {
        process.terminate();
        process.close();
    }

}

void copyFiles(QStringList files)
{
    QString command;
    QStringList args;
    command ="wsl";

    for(auto f : files)
    {
        args.clear();
        args << "-- cp /mnt/" + f.toStdString();
        process.start(command,args);
        process.waitForFinished();
    }


}
