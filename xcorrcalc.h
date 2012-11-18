#ifndef XCORRCALC_H
#define XCORRCALC_H

#include "abstractcalc.h"

class XCorrCalc : public AbstractCalc
{
public:
    XCorrCalc();
    void        clone();
    procdata    calc(bufferchunk * const sampledata);

private:
    int32_t     calcDirection();
};

#endif // XCORRCALC_H

