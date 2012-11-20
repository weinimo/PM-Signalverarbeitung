#include "signalprocworker.h"
#include "signalprocdispatcher.h"

#include <time.h> // TODO entfernen

SignalProcWorker::SignalProcWorker(bufferchunk *const chunk) :
    chunk(chunk)
{
}


void SignalProcWorker::calc()
{
    procdata data;
    sleep(5);
    emit calcFinished(data, (int)chunk);
    emit finished();
}

int32_t SignalProcWorker::calcDirUsingXCorr()
{
    // TODO: try "#pragma omp parallel for" for parallel loop execution.
    return 0; //TODO
}
