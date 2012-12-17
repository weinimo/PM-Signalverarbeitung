#ifndef XCORRCALC_H
#define XCORRCALC_H

#include "abstractcalc.h"

#include <QMutex>

#define XCORRCALC_DIRMEMSIZE 2

class XCorrCalc : public AbstractCalc
{
public:
    XCorrCalc();
    procdata                calc(bufferchunk * const sampledata);

    static QMutex           m_fftw;

private:
    uint16_t                directionFIRFilter(uint16_t newdirection);

    static int              directionMem[XCORRCALC_DIRMEMSIZE];
};

#endif // XCORRCALC_H

