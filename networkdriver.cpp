#include "networkdriver.h"

#include <QtEndian>


NetworkDriver::NetworkDriver(QString netIP, int netPort)
    : groupAddress(netIP), netPort(netPort), pktCounter(0)
{
}

void NetworkDriver::sendData(procdata data)
{
    data.fields.packetCounter      = pktCounter++;

    QByteArray databytes;
    databytes.append((char*)data.bytes, 8); //TOFIX: cast

    udpSocket.writeDatagram(databytes, groupAddress, netPort);
}

