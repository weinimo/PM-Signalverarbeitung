#include "xcorrcalc.h"

XCorrCalc::XCorrCalc()
{
}

AbstractCalc *XCorrCalc::clone()
{
    return new XCorrCalc;
}


int32_t XCorrCalc::calcDirection()
{
    return 0; //TODO
}


procdata XCorrCalc::calc(bufferchunk *const sampledata)
{
    procdata data;
    return data; //TODO
}
