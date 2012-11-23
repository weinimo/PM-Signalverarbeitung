#ifndef XCORRCALC_H
#define XCORRCALC_H

#include "abstractcalc.h"

#include <pthread.h>

class XCorrCalc : public AbstractCalc
{
public:
    XCorrCalc();
    procdata                calc(bufferchunk * const sampledata);

    static pthread_mutex_t  m_fftw;

private:
    int32_t                 calcDirection(bufferchunk * const sampledata);
};

#endif // XCORRCALC_H

