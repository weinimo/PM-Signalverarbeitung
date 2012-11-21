#ifndef ABSTRACTCALC_H
#define ABSTRACTCALC_H

#include "basicdefinitions.h"

class AbstractCalc
{
public:
    AbstractCalc();
    virtual procdata calc(bufferchunk * const sampledata) = 0;

protected:
    int32_t calcPowerLevel(bufferchunk * const sampledata);
    virtual int32_t calcDirection(bufferchunk * const sampledata) = 0;

};


#endif // ABSTRACTCALC_H
