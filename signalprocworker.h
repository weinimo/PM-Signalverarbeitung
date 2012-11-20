#ifndef SIGNALPROCWORKER_H
#define SIGNALPROCWORKER_H

#include <QObject>

#include "basicdefinitions.h"

class SignalProcWorker : public QObject
{
    Q_OBJECT
public:
    explicit        SignalProcWorker(bufferchunk * const chunk);

private:
    bufferchunk * const chunk;
    int32_t         calcDirUsingXCorr();

signals:
    //void            calcFinished(procdata data, bufferchunk * const chunk);
    void            calcFinished(procdata data, int chunk);
    void            finished();
public slots:
    void            calc();
};

#endif // SIGNALPROCWORKER_H
