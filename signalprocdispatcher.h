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
    //explicit SignalProcDispatcher(QObject *parent = 0);
    explicit                SignalProcDispatcher(QObject *parent, int clientID, bool demoMode);
    static bufferchunk *    getUsedBufferChunk();
    static void             freeUsedBufferChunk(bufferchunk * chunk, procdata data);

private:
    int const               clientID;
    int const               nWorkerThreads;
    uint32_t                pktCounter;
    bufferchunk             sampleBuffer[SPROC_NBUFFERCHUNKS];
    bool                    usedBufferChunks[SPROC_NBUFFERCHUNKS];

    NetworkDriver           netDriver;
    OsciDriver              osciDriver;
    SignalProcWorker        worker[SPROC_NBUFFERCHUNKS];

    QSemaphore              freeBuffer;
    QMutex                  m;
    QTimer                  osciPoller;
    QThread                 thread[SPROC_NBUFFERCHUNKS];
    QSemaphore              usedBuffer;

    void                    sendToGui(procdata data);
    void                    fillFreeBufferChunk(int32_t * data, int32_t dataSize);
    void                    getDataFromOsci();
    
signals:
    void                    bufferReadyForSampledata(bufferchunk * chunk);
    
public slots:

private slots:
    void                    pollOsciForData();
    
};

#endif // SIGNALPROCDISPATCHER_H
