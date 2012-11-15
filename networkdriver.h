#ifndef NETWORKDRIVER_H
#define NETWORKDRIVER_H

#include "basicdefinitions.h"

class NetworkDriver
{
public:
    NetworkDriver();
    void sendData(procdata data);

private:
    void assemblePacket(procdata data);
};

#endif // NETWORKDRIVER_H
