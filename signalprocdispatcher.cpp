#include "signalprocdispatcher.h"


SignalProcDispatcher::SignalProcDispatcher(QObject *parent, int clientID) :
    QObject(parent), clientID(clientID), pktCounter(0), osciPoller(this),
    nWorkerThreads(SPROC_NBUFFERCHUNKS), usedBuffer(SPROC_NBUFFERCHUNKS)
{
    osciPoller.setInterval(1000);           // Set polling intervall in msecs
    connect(&osciPoller, SIGNAL(timeout()), this, SLOT(pollOsciForData()));
    // TODO: osciPoller.start()
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
}

void SignalProcDispatcher::getDataFromOsci()
{
    // TODO
}
