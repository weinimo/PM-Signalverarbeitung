#include "oscidriver.h"
#include "signalprocdispatcher.h"
#include "vxi11/vxi11_user.h"

OsciDriver::OsciDriver(QString ipaddress, bool demoMode):
    demoMode(demoMode), ipaddr(ipaddress)
{
    if (!demoMode) {
        clink = new CLINK;
        int ret = vxi11_open_device(ipaddr.toAscii(), clink);

        if (ret != 0) {
            printf("Error: could not open device %s, quitting\n",ipaddr.toAscii().data());
            exit(2);
        }
        writeOsciSettings();
    }
}


void OsciDriver::writeOsciSettings()
{
    //sendCmd("AUTOSCALE");
    sendCmd("TIMEBASE:SCALE 5e-9");
}

long OsciDriver::sendCmd(QString cmd)
{
    long bytes_returned = 0;
    int ret = vxi11_send(clink, cmd.toAscii());
    if (cmd.contains("?")) {
        bytes_returned = vxi11_receive(clink, readBuffer, OSCI_RDBUFFERSIZE);
        if (bytes_returned > 0) {
            qDebug() << readBuffer;
        }
        else if (bytes_returned == -15) {
            printf("*** [ NOTHING RECEIVED ] ***\n");
        }
        qDebug() << "DEBUG: Do not call sendCmd(QString) with a command containing a ?";
    }
    char opcbuf[10] = "         ";
    while (true) { // Wait for "Operation Complete" TODO: verfeinern
        usleep(1000);
        vxi11_send_and_receive(clink, "*OPC?", opcbuf, 10, 1000);
        if (opcbuf[0] == '1') {
            break;
        }
    }
    return bytes_returned;
}

long OsciDriver::sendCmd(QString cmd, double * result, int resultsize)
{
    long bytes_returned = 0;
    int ret = vxi11_send(clink, cmd.toAscii());
    if (cmd.contains("?")) {
        bytes_returned = vxi11_receive(clink, readBuffer, OSCI_RDBUFFERSIZE);
        if (bytes_returned > 0) {
            //qDebug() << readBuffer;
            QString tString = readBuffer;
            QStringList tStringList = tString.split(",");
            for (int i = 0; i < tStringList.size(); i++) {
                if (i == resultsize) {
                    break;                                                      // Prevent writing over buffer chunk array bounds.
                }
                //TODO: Equalization is now done by XCorrCalc: result[i] = 1E5 * tStringList.at(i).toDouble();
                result[i] = tStringList.at(i).toDouble();
            }
        }
        else if (bytes_returned == -15) {
            printf("*** [ NOTHING RECEIVED ] ***\n");
        }
    }
    char opcbuf[10] = "         ";
    while (true) { // Wait for "Operation Complete" TODO: verfeinern
        usleep(1000);
        vxi11_send_and_receive(clink, "*OPC?", opcbuf, 10, 1000);
        if (opcbuf[0] == '1') {
            break;
        }
    }
    return bytes_returned;
}

void OsciDriver::fillChunk(int chunknum)
{
    if (demoMode)
        getDemoData(SignalProcDispatcher::getBufferChunk(chunknum));
    else
        getSampleData(SignalProcDispatcher::getBufferChunk(chunknum));
    emit chunkFilled(chunknum);
}

/**
 * TOTEST
 * @brief OsciDriver::getDemoData
 * @param chunk
 */
void OsciDriver::getDemoData(bufferchunk * const chunk)
{
    // simulate a random delay
    int randdly = qrand() % 100;
    int dlyChan = qrand() % 2;
    if (0 == dlyChan)   qDebug() << "randdly " << randdly * (-1);
    else                qDebug() << "randdly " << randdly;

//#pragma omp parallel for
    for (int i = 0; i < SPROC_SAMPLEDATASIZE / 2 - randdly; i++) {
        if (0 == dlyChan) {
            chunk->channels.first[i+randdly] = (i % 250) * 1E-3;
            chunk->channels.second[i] = (i % 250) * 1E-3;
        }
        else {
            chunk->channels.first[i] = (i % 250) * 1E-3;
            chunk->channels.second[i+randdly] = (i % 250) * 1E-3;
        }
    }
}

void OsciDriver::getSampleData(bufferchunk * const chunk)
{
    memset(readBuffer, 0, OSCI_RDBUFFERSIZE);                                   // Init read buffer
    sendCmd("SING");
    sendCmd("CHAN1:DATA?", chunk->channels.first, SPROC_SAMPLEDATASIZE / 2);
    sendCmd("CHAN2:DATA?", chunk->channels.second, SPROC_SAMPLEDATASIZE / 2);
    //sendCmd("RUN");
}

