#ifndef ABSTRACTCALC_H
#define ABSTRACTCALC_H

#include "basicdefinitions.h"

class AbstractCalc
{
public:
    AbstractCalc();
    virtual void clone() = 0;
    virtual procdata calc(bufferchunk * sampledata) = 0;

protected:
    int32_t calcPowerLevel();
    virtual int32_t calcDirection() = 0;
};

#endif // ABSTRACTCALC_H
