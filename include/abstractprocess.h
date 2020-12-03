#ifndef ABSTRACTPROCESS_H
#define ABSTRACTPROCESS_H

#include <QProcess>
#include <QDir>
#include <QTemporaryDir>

class AbstractProcess {

public:
    AbstractProcess(){};

    virtual QString makeTmpDir(){};
    virtual void runProcess(){};
    virtual void compileProcess(QStringList inputFileNames, QString simDelay, QString itPerCycle){};
    virtual void topModel(){};

private:
    QProcess process;
    QString tmpDir;
};

#endif // ABSTRACTPROCESS_H
