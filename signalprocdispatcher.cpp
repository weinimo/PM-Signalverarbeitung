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

    for (int i = 0; i < nWorkerThreads; i++) {
        worker[i].moveToThread(&thread[i]);
        connect(&worker[i], SIGNAL(calcFinished(procdata),
                this, SLOT(sendToGui(procdata)));
    }

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
    // TODO
}

/*void SignalProcDispatcher::fillFreeBufferChunk(int32_t * data, int32_t dataSize)
{
    // TODO
}*/

void SignalProcDispatcher::pollOsciForData()
{
    // TODO
    if (freeBuffer.tryAcquire(1, 700)) {                                        // Try for 700 msecs to get a free Buffer chunk.
        int i;
        for (i = 0; i < SPROC_NBUFFERCHUNKS; i++)
            if (true == usedBufferChunks[i])
                break;
        usedBufferChunks[i] = false;                                            // Mark chunk used.
        emit bufferReadyForSampledata(&sampleBuffer[i]);
    }
}

void SignalProcDispatcher::getDataFromOsci()
{
    // TODO
}
