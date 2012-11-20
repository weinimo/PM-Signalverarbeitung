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
    void                    chunkFilled(bufferchunk * sampledata);

public slots:
    void                    fillChunk(bufferchunk *chunk);
};

#endif // OSCIDRIVER_H
