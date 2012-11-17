#include "signalprocworker.h"

#include "signalprocdispatcher.h"

SignalProcWorker::SignalProcWorker()
{
}

void SignalProcWorker::run()
{

}

void SignalProcWorker::calc(bufferchunk * sampleData, int32_t dataSize)
{
    procdata data;
    emit finished(data);
}

int32_t SignalProcWorker::calcDirUsingXCorr()
{
    return 0; //TODO
}
