#include "signalprocdispatcher.h"


SignalProcDispatcher::SignalProcDispatcher(QObject *parent, int clientID, bool demoMode) :
    QObject(parent), clientID(clientID), nWorkerThreads(SPROC_NBUFFERCHUNKS), pktCounter(0),
    osciDriver(demoMode), freeBuffer(SPROC_NBUFFERCHUNKS), osciPoller(this)
{
    osciPoller.setInterval(100);                                                // Set polling intervall in msecs

    // Set up connections
    connect(&osciPoller, SIGNAL(timeout()), this, SLOT(pollOsciForData()));     // Tries to get sample data
    connect(this, SIGNAL(chunkReadyForFilling(bufferchunk*const)),              // Fills buffer chunks with sample data
            &osciDriver, SLOT(fillChunk(bufferchunk*const)));
    connect(&osciDriver, SIGNAL(chunkFilled(bufferchunk*const)),                // Dispatch chunk processing
            this, SLOT(procChunk(bufferchunk*const)));

    for (int i = 0; i < SPROC_NBUFFERCHUNKS; i++)
        usedBufferChunks[i] = false;

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

void SignalProcDispatcher::sendToGui(procdata data, bufferchunk * const chunk)
{
    // TODO

    QTextStream cin(stdin, QIODevice::ReadOnly);
    QTextStream cout(stdout, QIODevice::WriteOnly);
    QTextStream cerr(stderr, QIODevice::WriteOnly);
    QMutexLocker locker(&m);
    int i = 0;
    while(&sampleBuffer[i] != chunk)                                            // Find the right chunk number.
        i++;
    cout << "sendToGui(). i: " << i << endl;
    usedBufferChunks[i] = false;                                                // Mark chunk unused.
    freeBuffer.release();

    netDriver.sendData(data);
}

void SignalProcDispatcher::pollOsciForData()
{
    // TODO
    QTextStream cin(stdin, QIODevice::ReadOnly);
    QTextStream cout(stdout, QIODevice::WriteOnly);
    QTextStream cerr(stderr, QIODevice::WriteOnly);
    cout << freeBuffer.available() << endl;
    if (freeBuffer.tryAcquire(1, 700)) {                                        // Try for 700 msecs to get a free Buffer chunk.
        freeBuffer.acquire();
        int i = 0;
        while (true == usedBufferChunks[i])                                     // Find first unused buffer..
            i++;
        cout << "pollOsciForData(). i: " << i << endl;
        usedBufferChunks[i] = true;                                             // Mark chunk used.
        emit chunkReadyForFilling(&sampleBuffer[i]);
    }
}

void SignalProcDispatcher::getDataFromOsci()
{
    // TODO
}


void SignalProcDispatcher::procChunk(bufferchunk * const chunk)
{
    QThread * thread = new QThread;
    SignalProcWorker * worker = new SignalProcWorker();
    worker->moveToThread(thread);
    //connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(calcFinished(procdata, bufferchunk * const)),
            this, SLOT(sendToGui(procdata, bufferchunk * const)));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
    worker->calc(chunk);
}
