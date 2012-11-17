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

private:
    int32_t         calcDirUsingXCorr();

signals:
    void            finished(procdata data);
public slots:
    void            calc(bufferchunk * sampleData, int32_t dataSize);
};

#endif // SIGNALPROCWORKER_H
