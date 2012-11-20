#ifndef OSCIDRIVER_H
#define OSCIDRIVER_H

#include <QObject>

#include "basicdefinitions.h"

class OsciDriver: public QObject
{
    Q_OBJECT
public:
    OsciDriver(bool demoMode = false);

private:
    bool                    demoMode;
    void                    writeOsciSettings();
    void                    getDemoData(bufferchunk * const chunk);
    void                    getSampleData(bufferchunk * const chunk);

signals:
    void                    chunkFilled(int chunknum);

public slots:
    void                    fillChunk(int chunknum);
};

#endif // OSCIDRIVER_H
