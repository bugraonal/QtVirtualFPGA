#ifndef WSLPROCESS_H
#define WSLPROCESS_H

#include "abstractprocess.h"

class WSLProcess : public AbstractProcess {

public:
    WSLProcess(){};

     QString makeTmpDir(){};
     void runProcess(){};
     void compileProcess(QStringList inputFileNames, QString simDelay, QString itPerCycle){};
     void topModel(){};


};

#endif // WSLPROCESS_H
