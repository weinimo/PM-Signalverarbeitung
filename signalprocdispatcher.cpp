#include <assert.h>

#include "signalprocdispatcher.h"

std::array<bufferchunk, SPROC_NBUFFERCHUNKS> SignalProcDispatcher::sampleBuffer;

SignalProcDispatcher::SignalProcDispatcher(QObject *parent, QString osciIP, QString netIP,
                                           int netPort, int clientID, bool demoMode) :
    QObject(parent), clientID(clientID), freeBuffer(SPROC_NBUFFERCHUNKS),
    netDriver(netIP, netPort), osciDriver(osciIP, demoMode), osciPoller(this)
{
    osciPoller.setInterval(400);                                                // Set polling intervall in msecs

    for (int i = 0; i < SPROC_NBUFFERCHUNKS; i++)
        usedBufferChunks[i] = false;

    qRegisterMetaType<bufferchunk>("bufferchunk");
    qRegisterMetaType<bufferchunk*>("bufferchunk*");
    //qRegisterMetaType<bufferchunk*const>("bufferchunk*const");
    qRegisterMetaType<procdata>("procdata");
    qRegisterMetaType<procdata*>("procdata*");

    // Set up connections
    connect(&osciPoller, SIGNAL(timeout()), this, SLOT(pollOsciForData()));     // Tries to get sample data
    connect(this, SIGNAL(chunkReadyForFilling(int)),              // Fills buffer chunks with sample data
            &osciDriver, SLOT(fillChunk(int)));
    connect(&osciDriver, SIGNAL(chunkFilled(int)),                // Dispatch chunk processing
            this, SLOT(procChunk(int)));
    osciPoller.start();
}

int SignalProcDispatcher::getFreeBufferChunkNum()
{
    QMutexLocker locker(&m);
    for (int i = 0; i < SPROC_NBUFFERCHUNKS; i++)
        if (usedBufferChunks[i] == false){
            //qDebug() << "getFreeBufferChunk(): " << i;
            usedBufferChunks[i] = true;
            memset(&SignalProcDispatcher::sampleBuffer.at(i), 0,
                   sizeof(SignalProcDispatcher::sampleBuffer.at(i)));
            return i;
        }
    qDebug() << "getFreeBufferChunk(): ERROR: Method was called when no buffer chunk was free.";
    assert(0);
}

bufferchunk * SignalProcDispatcher::getBufferChunk(int chunknum)
{
    if (chunknum >= 0 && chunknum < SPROC_NBUFFERCHUNKS) {
        return &SignalProcDispatcher::sampleBuffer.at(chunknum);
    }
    else assert(0);
}

void SignalProcDispatcher::sendToGui(procdata data, int chunknum)
{
    data.fields.clientID           = clientID;
    data.fields.protocolVersion    = 1;

    //qDebug() << "sendToGui(). chunknum: " << chunknum;
    freeUsedBufferChunk(chunknum);

    netDriver.sendData(data);
}

void SignalProcDispatcher::pollOsciForData()
{
    //qDebug() << "pollOsciForData(): freeBuffer.available() "
    //         << freeBuffer.available();
    if (freeBuffer.tryAcquire(1, 50)) {                                        // Try for 50 msecs to get a free Buffer chunk.
        int chknum = getFreeBufferChunkNum();
        //qDebug() << "pollOsciForData(). chknum: " << chknum;
        emit chunkReadyForFilling(chknum);
    }
}

void SignalProcDispatcher::procChunk(int chunknum)
{
    QThread * thread = new QThread;
    SignalProcWorker * worker = new SignalProcWorker(chunknum);
    worker->moveToThread(thread);
    connect(thread, SIGNAL(started()), worker, SLOT(calc()));
    //connect(worker, SIGNAL(calcFinished(procdata, bufferchunk * const)),
    //        this, SLOT(sendToGui(procdata, bufferchunk * const)));
    connect(worker, SIGNAL(calcFinished(procdata, int)),
            this, SLOT(sendToGui(procdata, int)));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}


void SignalProcDispatcher::freeUsedBufferChunk(int chunknum)
{
    //qDebug() << "freeUsedBufferChunk(): chunknum " << chunknum;
    usedBufferChunks[chunknum] = false;
    freeBuffer.release();
}
