#ifndef SIGNALPROCDISPATCHER_H
#define SIGNALPROCDISPATCHER_H

#include <QtCore>
#include <array>

#include "basicdefinitions.h"
#include "signalprocworker.h"
#include "networkdriver.h"
#include "oscidriver.h"

class SignalProcDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit                SignalProcDispatcher(QObject *parent, QString osciIP,
                                                 QString netIP, int netPort,
                                                 int clientID, bool demoMode);
    int                     getFreeBufferChunkNum();
    static bufferchunk *    getBufferChunk(int chunknum);
    void                    freeUsedBufferChunk(int chunknum);

private:
    int const               clientID;
    QSemaphore              freeBuffer;
    QMutex                  m;
    NetworkDriver           netDriver;
    OsciDriver              osciDriver;
    QTimer                  osciPoller;
    static std::array<bufferchunk, SPROC_NBUFFERCHUNKS> sampleBuffer;
    bool                    usedBufferChunks[SPROC_NBUFFERCHUNKS];

    void                    getDataFromOsci();

signals:
    void                    chunkReadyForFilling(int chunknum);

public slots:
    void                    procChunk(int chunknum);
    void                    pollOsciForData();
    //void                    sendToGui(procdata data, bufferchunk * const chunk);
    void                    sendToGui(procdata data, int chunknum);

};

#endif // SIGNALPROCDISPATCHER_H
