#ifndef OSCIDRIVER_H
#define OSCIDRIVER_H

#include <QObject>
#include <QString>

#include "basicdefinitions.h"
#include "vxi11/vxi11_user.h"

#define OSCI_RDBUFFERSIZE 1000000

class OsciDriver: public QObject
{
    Q_OBJECT
public:
    OsciDriver(QString ipaddress, bool demoMode = false);

private:
    CLINK *                 clink;
    bool                    demoMode;
    QString                 ipaddr;
    char                    readBuffer[OSCI_RDBUFFERSIZE];

    void                    getDemoData(bufferchunk * const chunk);
    void                    getSampleData(bufferchunk * const chunk);
    long sendCmd(QString cmd);
    void                    writeOsciSettings();

signals:
    void                    chunkFilled(int chunknum);

public slots:
    void                    fillChunk(int chunknum);
};

#endif // OSCIDRIVER_H
