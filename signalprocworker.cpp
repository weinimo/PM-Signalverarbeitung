#include "signalprocworker.h"
#include "signalprocdispatcher.h"

#include <time.h> // TODO entfernen

SignalProcWorker::SignalProcWorker(int chunknum) :
    chunknum(chunknum)
{
}


void SignalProcWorker::calc()
{
    procdata data;
    sleep(15);
    emit calcFinished(data, chunknum);
    emit finished();
}

int32_t SignalProcWorker::calcDirUsingXCorr()
{
    // TODO: try "#pragma omp parallel for" for parallel loop execution.
    return 0; //TODO
}
