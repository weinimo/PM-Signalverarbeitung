#ifndef OSCIDRIVER_H
#define OSCIDRIVER_H

#include "basicdefinitions.h"

class OsciDriver
{
public:
    OsciDriver(bool demoMode = false);
    void getDemoData();
    void getSampleData(int channel, int32_t * sampledata, int32_t datasize);

private:
    bool demoMode;

    void writeOsciSettings();
};

#endif // OSCIDRIVER_H
