#include "abstractcalc.h"
#include "xcorrcalc.h"

AbstractCalc * AbstractCalcFactory::calcPrototypes[] = {new XCorrCalc()};

AbstractCalc::AbstractCalc()
{
}

AbstractCalc * AbstractCalcFactory::makeInst(int choice)
{
    return AbstractCalcFactory::calcPrototypes[choice]->clone();
}

int32_t AbstractCalc::calcPowerLevel()
{
    return 0; //TODO
}
