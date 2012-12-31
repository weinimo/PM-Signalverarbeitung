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
    int32_t directionFIRFilter(int32_t signedTheta);

    static int32_t          directionMem[XCORRCALC_DIRMEMSIZE];
};

#endif // XCORRCALC_H

