#include "signalprocworker.h"
#include "signalprocdispatcher.h"
#include "abstractcalc.h"

#include <time.h> // TODO entfernen

SignalProcWorker::SignalProcWorker(int chunknum) :
    chunknum(chunknum)
{
    calcInst = AbstractCalc::makeInst(chunknum);
}


void SignalProcWorker::calc()
{
    procdata data;
    sleep(7);

    AbstractCalc * calcInst = AbstractCalc::makeInst(0);         // Create a XCorrCalc Instance
    data = calcInst->calc(SignalProcDispatcher::getBufferChunk(chunknum));
    delete calcInst;

    emit calcFinished(data, chunknum);
    emit finished();
}

int32_t SignalProcWorker::calcDirUsingXCorr()
{
    // TODO: try "#pragma omp parallel for" for parallel loop execution.
    return 0; //TODO
}
