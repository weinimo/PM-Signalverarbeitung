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
    }
    return bytes_returned;
}

long OsciDriver::sendCmd(QString cmd, double * result)
{
    long bytes_returned = 0;
    int ret = vxi11_send(clink, cmd.toAscii());
    if (cmd.contains("?")) {
        bytes_returned = vxi11_receive(clink, readBuffer, OSCI_RDBUFFERSIZE);
        if (bytes_returned > 0) {
            qDebug() << readBuffer;
            QString tString = readBuffer;
            QStringList tStringList = tString.split(",");
            for (int i = 0; i < tStringList.size(); i++) {
                result[i] = tStringList.at(i).toDouble();       // TODO: Possible out-of-bounds if result is too small
            }
            // TODO Verarbeitung
        }
        else if (bytes_returned == -15) {
            printf("*** [ NOTHING RECEIVED ] ***\n");
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
    int randdly = qrand() % 40;
    int dlyChan = qrand() % 2;
    if (0 == dlyChan)   qDebug() << "randdly " << randdly * (-1);
    else                qDebug() << "randdly " << randdly;

//#pragma omp parallel for
    for (int i = 0; i < SPROC_SAMPLEDATASIZE / 2 - randdly; i++) {
        if (0 == dlyChan) {
            chunk->channels.first[i+randdly] = i % 300;
            chunk->channels.second[i] = i % 300;
        }
        else {
            chunk->channels.first[i] = i % 300;
            chunk->channels.second[i+randdly] = i % 300;
        }
    }
}

void OsciDriver::getSampleData(bufferchunk * const chunk)
{
    memset(readBuffer, 0, OSCI_RDBUFFERSIZE);                                   // Init read buffer
    // TODO
}

