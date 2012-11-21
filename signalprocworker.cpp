#include "signalprocworker.h"
#include "signalprocdispatcher.h"
#include "xcorrcalc.h"

#include <time.h> // TODO entfernen

SignalProcWorker::SignalProcWorker(int chunknum) :
    chunknum(chunknum)
{
}


void SignalProcWorker::calc()
{
    procdata data;
    sleep(3);

    XCorrCalc c;         // Create a XCorrCalc Instance
    data = c.calc(SignalProcDispatcher::getBufferChunk(chunknum));

    emit calcFinished(data, chunknum);
    emit finished();
}
