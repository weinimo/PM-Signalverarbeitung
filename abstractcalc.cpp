#include "abstractcalc.h"
#include "xcorrcalc.h"

AbstractCalc * AbstractCalc::calcPrototypes[] = {new XCorrCalc};

AbstractCalc::AbstractCalc()
{
}

AbstractCalc * AbstractCalc::makeInst(int choice)
{
    return calcPrototypes[choice]->clone();
}

int32_t AbstractCalc::calcPowerLevel()
{
    return 0; //TODO
}
