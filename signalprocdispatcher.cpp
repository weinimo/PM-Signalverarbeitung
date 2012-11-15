#include "signalprocdispatcher.h"


SignalProcDispatcher::SignalProcDispatcher(QObject *parent, int clientID) :
    QObject(parent), clientID(clientID), pktCounter(0), osciPoller(this),
    nWorkerThreads(SPROC_NBUFFERCHUNKS), usedBuffer(SPROC_NBUFFERCHUNKS),
    osciDriver(true)
{
    osciPoller.setInterval(1000);           // Set polling intervall in msecs
    connect(&osciPoller, SIGNAL(timeout()), this, SLOT(pollOsciForData()));
    connect(this, SIGNAL(bufferReadyForSampledata(bufferchunk*)),   // Fills buffer chunks
            &osciDriver, SLOT(fillBufferWithSampledata(bufferchunk*)));
    // TODO: osciPoller.start()

    for (int i = 0; i < nWorkerThreads; i++) {
        worker[i].moveToThread(&thread[i]);
        //connect(&thread[i], SIGNAL(started()), &worker[i], SLOT(calc(bufferchunk*,int32_t))); //TODO: richtig machen
    }
}

bufferchunk * SignalProcDispatcher::getUsedBufferChunk()
{
    // TODO
    return nullptr;
}

void SignalProcDispatcher::freeUsedBufferChunk(bufferchunk * chunk, procdata data)
{
    // TODO
}

void SignalProcDispatcher::sendToGui(procdata data)
{
    // TODO
}

void SignalProcDispatcher::fillFreeBufferChunk(int32_t * data, int32_t dataSize)
{
    // TODO
}

void SignalProcDispatcher::pollOsciForData()
{
    // TODO
    if (freeBuffer.tryAcquire(1, 500)) {    // Try for 500 msecs to get a free Buffer chunk.
        int i;
        for (i = 0; i < SPROC_NBUFFERCHUNKS; i++)
            if (true == usedBufferChunks[i])
                break;
        usedBufferChunks[i] = false;        // Mark chunk used.
        emit bufferReadyForSampledata(&sampleBuffer[i]);
    }
}

void SignalProcDispatcher::getDataFromOsci()
{
    // TODO
}
