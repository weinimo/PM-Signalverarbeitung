#ifndef XCORRCALC_H
#define XCORRCALC_H

#include "abstractcalc.h"

#include <QMutex>

class XCorrCalc : public AbstractCalc
{
public:
    XCorrCalc();
    procdata                calc(bufferchunk * const sampledata);

    static QMutex           m_fftw;
};

#endif // XCORRCALC_H

