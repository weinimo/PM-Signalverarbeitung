#ifndef SIGNALPROCWORKER_H
#define SIGNALPROCWORKER_H

#include <QObject>

#include "basicdefinitions.h"

class SignalProcWorker : public QObject
{
    Q_OBJECT
public:
    explicit        SignalProcWorker();
    void            run();
    void            calc(bufferchunk * const sampleData);

private:
    int32_t         calcDirUsingXCorr();

signals:
    void            calcFinished(procdata data, bufferchunk * const chunk);
    void            finished();
public slots:
};

#endif // SIGNALPROCWORKER_H
