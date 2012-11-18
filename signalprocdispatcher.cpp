#include "signalprocdispatcher.h"


SignalProcDispatcher::SignalProcDispatcher(QObject *parent, int clientID, bool demoMode) :
    QObject(parent), clientID(clientID), nWorkerThreads(SPROC_NBUFFERCHUNKS), pktCounter(0),
    osciDriver(demoMode), osciPoller(this), usedBuffer(SPROC_NBUFFERCHUNKS)
{
    osciPoller.setInterval(1000);                                               // Set polling intervall in msecs

    // Set up connections
    connect(&osciPoller, SIGNAL(timeout()), this, SLOT(pollOsciForData()));     // Tries to get sample data
    connect(this, SIGNAL(chunkReadyForFilling(bufferchunk*)),                   // Fills buffer chunks with sample data
            &osciDriver, SLOT(fillChunk(bufferchunk*)));
    connect(&osciDriver, SIGNAL(chunkFilled(bufferchunk*)),                     // Dispatch chunk processing
            this, SLOT(procChunk(bufferchunk*const)));

    osciPoller.start();
}

bufferchunk * SignalProcDispatcher::getUsedBufferChunk()
{
    // TODO
    return nullptr;
}

void SignalProcDispatcher::freeUsedBufferChunk(bufferchunk * const chunk, procdata data)
{
    // TODO
}

void SignalProcDispatcher::sendToGui(procdata data)
{
    QMutexLocker locker(&m);                                                    // Could be access by multiple threads at the same time.
    // TODO
}

void SignalProcDispatcher::pollOsciForData()
{
    // TODO
    if (freeBuffer.tryAcquire(1, 700)) {                                        // Try for 700 msecs to get a free Buffer chunk.
        int i;
        for (i = 0; i < SPROC_NBUFFERCHUNKS; i++)
            if (true == usedBufferChunks[i])
                break;
        usedBufferChunks[i] = false;                                            // Mark chunk used.
        emit chunkReadyForFilling(&sampleBuffer[i]);
    }
}

void SignalProcDispatcher::getDataFromOsci()
{
    // TODO
}


void SignalProcDispatcher::procChunk(bufferchunk *const chunk)
{
    QThread * thread = new QThread;
    SignalProcWorker * worker = new SignalProcWorker();
    worker->moveToThread(thread);
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(calcFinished(procdata)), this, SLOT(sendToGui(procdata)));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();

}
