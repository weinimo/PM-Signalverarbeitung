#include "signalprocworker.h"

#include "signalprocdispatcher.h"

SignalProcWorker::SignalProcWorker()
{
}

void SignalProcWorker::run()
{

}

procdata SignalProcWorker::calc(bufferchunk * sampleData, int32_t dataSize)
{
    procdata data;
    emit finished(data);
}

int32_t SignalProcWorker::calcDirUsingXCorr()
{

}
