#include "signalprocworker.h"
#include "signalprocdispatcher.h"

#include <time.h> // TODO entfernen

SignalProcWorker::SignalProcWorker()
{
}

void SignalProcWorker::run()
{

}

void SignalProcWorker::calc(bufferchunk * const sampleData)
{
    procdata data;
    sleep(2);
    emit calcFinished(data, sampleData);
    emit finished();
}

int32_t SignalProcWorker::calcDirUsingXCorr()
{
    // TODO: try "#pragma omp parallel for" for parallel loop execution.
    return 0; //TODO
}
