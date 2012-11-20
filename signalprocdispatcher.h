#ifndef SIGNALPROCDISPATCHER_H
#define SIGNALPROCDISPATCHER_H

#include <QtCore>

#include "basicdefinitions.h"
#include "signalprocworker.h"
#include "networkdriver.h"
#include "oscidriver.h"

class SignalProcDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit                SignalProcDispatcher(QObject *parent, int clientID, bool demoMode);
    static bufferchunk *    getUsedBufferChunk();
    static void             freeUsedBufferChunk(bufferchunk * const chunk, procdata data);

    NetworkDriver           netDriver;//TODO
    OsciDriver              osciDriver;

    QTimer                  osciPoller;

    void                    setup();

private:
    int const               clientID;
    int const               nWorkerThreads;
    uint32_t                pktCounter;
    bufferchunk             sampleBuffer[SPROC_NBUFFERCHUNKS];
    bool                    usedBufferChunks[SPROC_NBUFFERCHUNKS];

    QSemaphore              freeBuffer;
    QMutex                  m;
    QSemaphore              usedBuffer;

    void                    getDataFromOsci();

signals:
    void                    chunkReadyForFilling(bufferchunk * chunk);

public slots:
    void                    procChunk(bufferchunk *chunk);
    void                    pollOsciForData();
    //void                    sendToGui(procdata data, bufferchunk * const chunk);
    void                    sendToGui(procdata data, int chunk);

};

#endif // SIGNALPROCDISPATCHER_H
