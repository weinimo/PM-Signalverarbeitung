#ifndef SIGNALPROCWORKER_H
#define SIGNALPROCWORKER_H

#include <QObject>
#include <QThread>

#include "basicdefinitions.h"

class SignalProcWorker : public QObject
{
    Q_OBJECT
public:
    explicit SignalProcWorker(QObject *parent = 0);
    void run();

private:
    procdata calc(bufferchunk * sampleData, int32_t dataSize);
    int32_t calcDirUsingXCorr();

signals:

public slots:

};

#endif // SIGNALPROCWORKER_H
