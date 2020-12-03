#ifndef LINUXPROCESS_H
#define LINUXPROCESS_H

#include "abstractprocess.h"

class LinuxProcess : public AbstractProcess {

public:
     LinuxProcess(){};
     QString makeTmpDir(){};
     void runProcess(){};
     void compileProcess(QStringList inputFileNames, QString simDelay, QString itPerCycle){};
     void topModel(){};


};

#endif // LINUXPROCESS_H
