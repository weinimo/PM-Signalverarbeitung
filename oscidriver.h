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
    void                    getDemoData(int32_t * const sampledata, int32_t datasize);
    void                    getSampleData(int const channel, int32_t * const sampledata,
                                          int32_t datasize);

signals:
    void                    chunkFilled(bufferchunk * sampledata);

public slots:
    void                    fillChunk(bufferchunk * const chunk);
};

#endif // OSCIDRIVER_H
