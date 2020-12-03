#ifndef WSLPROCESS_H
#define WSLPROCESS_H

#include "abstractprocess.h"

class WSLProcess : public AbstractProcess {

public:
    WSLProcess();

    virtual QString makeTmpDir();
    virtual void runProcess();
    virtual void compileProcess(QStringList inputFileNames, QString simDelay, QString itPerCycle);
    virtual void topModel();


};

#endif // WSLPROCESS_H
