#include "networkdriver.h"

#include <arpa/inet.h>
#include <QDebug>

NetworkDriver::NetworkDriver(QString netIP, int netPort)
    : groupAddress(netIP), netPort(netPort), pktCounter(0)
{
}

void NetworkDriver::sendData(procdata data)
{
    data.fields.packetCounter      = pktCounter++;

    data.halfwords[1] = htons(data.halfwords[1]);                               // Correct byte order
    data.halfwords[2] = htons(data.halfwords[2]);
    data.halfwords[3] = htons(data.halfwords[3]);

    QByteArray databytes;
    databytes.append((char*)data.bytes, 8); //TOFIX: cast

    udpSocket.writeDatagram(databytes, groupAddress, netPort);
}

