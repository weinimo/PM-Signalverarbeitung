#ifndef SIGNALPROCDISPATCHER_H
#define SIGNALPROCDISPATCHER_H

#include <QObject>
#include <QSemaphore>
#include <QMutex>
#include <QTimer>

#include "basicdefinitions.h"
#include "signalprocworker.h"

class SignalProcDispatcher : public QObject
{
    Q_OBJECT
public:
    //explicit SignalProcDispatcher(QObject *parent = 0);
    explicit                SignalProcDispatcher(QObject *parent, int clientID);
    static bufferchunk *    getUsedBufferChunk();
    static void             freeUsedBufferChunk(bufferchunk * chunk, procdata data);

private:
    int const               clientID;
    uint32_t                pktCounter;
    int const               nWorkerThreads;
    bufferchunk             sampleBuffer[SPROC_NBUFFERCHUNKS];
    bool                    usedBufferChunks[SPROC_NBUFFERCHUNKS];

    QMutex                  m;
    QSemaphore              freeBuffer;
    QSemaphore              usedBuffer;
    QTimer                  osciPoller;

    void                    sendToGui(procdata data);
    void                    fillFreeBufferChunk(int32_t * data, int32_t dataSize);
    void                    getDataFromOsci();
    
signals:
    
public slots:

private slots:
    void                    pollOsciForData();
    
};

#endif // SIGNALPROCDISPATCHER_H