#ifndef XCORRCALC_H
#define XCORRCALC_H

#include "abstractcalc.h"

class XCorrCalc : public AbstractCalc
{
public:
    XCorrCalc();
    procdata            calc(bufferchunk * const sampledata);

private:
    int32_t             calcDirection(bufferchunk * const sampledata);
};

#endif // XCORRCALC_H

