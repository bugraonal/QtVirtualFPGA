#ifndef WINDOWSPROCESS_H
#define WINDOWSPROCESS_H

#include "abstractprocess.h"

class WindowsProcess : public AbstractProcess {

public:
    WindowsProcess(){};

     QString makeTmpDir(){};
     void runProcess(){};
     void compileProcess(QStringList inputFileNames, QString simDelay, QString itPerCycle){};
     void topModel(){};


};

#endif // WINDOWSPROCESS_H
