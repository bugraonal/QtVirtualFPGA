#ifndef LINUXPROCESS_H
#define LINUXPROCESS_H

#include "abstractprocess.h"

class LinuxProcess : public AbstractProcess {

public:
    LinuxProcess();
    virtual QString makeTmpDir();
    virtual void runProcess();
    virtual void compileProcess(QStringList inputFileNames, QString simDelay, QString itPerCycle);
    virtual void topModel();


};

#endif // LINUXPROCESS_H
