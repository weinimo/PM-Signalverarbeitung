#ifndef SIGNALPROCWORKER_H
#define SIGNALPROCWORKER_H

#include <QObject>

#include "basicdefinitions.h"

class SignalProcWorker : public QObject
{
    Q_OBJECT
public:
    explicit        SignalProcWorker(int chunknum);

private:
    int             chunknum;
    int32_t         calcDirUsingXCorr();

signals:
    //void            calcFinished(procdata data, bufferchunk * const chunk);
    void            calcFinished(procdata data, int chunknum);
    void            finished();
public slots:
    void            calc();
};

#endif // SIGNALPROCWORKER_H
