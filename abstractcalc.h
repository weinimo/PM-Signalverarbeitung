#ifndef ABSTRACTCALC_H
#define ABSTRACTCALC_H

#include "basicdefinitions.h"

class AbstractCalc
{
public:
    AbstractCalc();
    virtual procdata calc(bufferchunk * const sampledata) = 0;
    virtual AbstractCalc * clone() = 0;

protected:
    int32_t calcPowerLevel();
    virtual int32_t calcDirection() = 0;

};

class AbstractCalcFactory
{
public:
    static AbstractCalc * makeInst(int choice);
private:
    static AbstractCalc * calcPrototypes[1];
};

#endif // ABSTRACTCALC_H
