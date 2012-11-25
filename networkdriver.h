#ifndef NETWORKDRIVER_H
#define NETWORKDRIVER_H

#include "basicdefinitions.h"

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QUdpSocket>

class NetworkDriver
{
public:
    NetworkDriver(QString netIP, int netPort);
    void                    sendData(procdata data);

private:
    QHostAddress            groupAddress;
    int                     netPort;
    int                     pktCounter;
    QUdpSocket              udpSocket;
};

#endif // NETWORKDRIVER_H
