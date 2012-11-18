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

private:
    int const               clientID;
    int const               nWorkerThreads;
    uint32_t                pktCounter;
    bufferchunk             sampleBuffer[SPROC_NBUFFERCHUNKS];
    bool                    usedBufferChunks[SPROC_NBUFFERCHUNKS];

    NetworkDriver           netDriver;
    OsciDriver              osciDriver;

    QSemaphore              freeBuffer;
    QMutex                  m;
    QTimer                  osciPoller;
    QSemaphore              usedBuffer;

    void                    getDataFromOsci();

signals:
    void                    chunkReadyForFilling(bufferchunk * const chunk);

public slots:
    void                    procChunk(bufferchunk * const chunk);
    void                    sendToGui(procdata data);

private slots:
    void                    pollOsciForData();

};

#endif // SIGNALPROCDISPATCHER_H
