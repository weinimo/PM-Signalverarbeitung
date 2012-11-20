#include "oscidriver.h"
#include "signalprocdispatcher.h"

OsciDriver::OsciDriver(bool demoMode):
    demoMode(demoMode)
{
    if (!demoMode)
        writeOsciSettings();
}


void OsciDriver::writeOsciSettings()
{
}

void OsciDriver::fillChunk(int chunknum)
{
    if (demoMode)
        getDemoData(SignalProcDispatcher::getBufferChunk(chunknum));
    else
        getSampleData(SignalProcDispatcher::getBufferChunk(chunknum));
    emit chunkFilled(chunknum);
}

/**
 * TOTEST
 * @brief OsciDriver::getDemoData
 * @param chunk
 */
void OsciDriver::getDemoData(bufferchunk * const chunk)
{
    // simulate a random delay
    uint32_t randdly = qrand() % 7;

#pragma omp parallel for
    for (int i = 0; i < SPROC_SAMPLEDATASIZE / 2 ; i++) {
        chunk->channels.first[i] = i % 300;
        chunk->channels.second[i+randdly] = i % 300;
    }
}

void OsciDriver::getSampleData(bufferchunk * const chunk)
{
    // TODO
}

