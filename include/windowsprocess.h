#ifndef WINDOWSPROCESS_H
#define WINDOWSPROCESS_H

#include "abstractprocess.h"

class WindowsProcess : public AbstractProcess {

public:
    WindowsProcess();

    virtual QString makeTmpDir();
    virtual void runProcess();
    virtual void compileProcess(QStringList inputFileNames, QString simDelay, QString itPerCycle);
    virtual void topModel();


};

#endif // WINDOWSPROCESS_H
