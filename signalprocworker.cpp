#include "signalprocworker.h"

#include "signalprocdispatcher.h"

SignalProcWorker::SignalProcWorker()
{
}

void SignalProcWorker::run()
{

}

void SignalProcWorker::calc(bufferchunk * const sampleData, int32_t dataSize)
{
    procdata data;
    emit calcFinished(data);
    emit finished();
}

int32_t SignalProcWorker::calcDirUsingXCorr()
{
    // TODO: try "#pragma omp parallel for" for parallel loop execution.
    return 0; //TODO
}
