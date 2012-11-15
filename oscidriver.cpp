#include "oscidriver.h"

OsciDriver::OsciDriver(bool demoMode):
    demoMode(demoMode)
{
    if (!demoMode)
        writeOsciSettings();
}


void OsciDriver::writeOsciSettings()
{
}

void OsciDriver::fillBuffer(bufferchunk * const chunk)
{
    if (demoMode)
        getDemoData(chunk->data, SPROC_SAMPLEDATASIZE);
    // TODO else
}

void OsciDriver::getDemoData(int32_t * const sampledata, int32_t datasize)
{
    emit finished(sampledata);
}

void OsciDriver::getSampleData(int const channel, int32_t * const sampledata, int32_t datasize)
{
    emit finished(sampledata);
}

