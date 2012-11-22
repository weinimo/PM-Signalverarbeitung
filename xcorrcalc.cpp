#include "xcorrcalc.h"
#include "libxcorr/xcorr.h"
#include <QDebug>

XCorrCalc::XCorrCalc()
{
}

/**
 * @brief XCorrCalc::calcDirection
 * Calcutates the sender direction using cross-correlation.
 * @param sampledata
 * @return
 */
int32_t XCorrCalc::calcDirection(bufferchunk * const sampledata)
{
    fftw_complex * ch1data, * ch2data, * result;
    int const chDataSize = SPROC_SAMPLEDATASIZE / 2;
    int const resultSize = 2 * chDataSize - 1;

    ch1data = (fftw_complex*)
            fftw_malloc(sizeof(fftw_complex) * chDataSize);
    ch2data = (fftw_complex*)
            fftw_malloc(sizeof(fftw_complex) * chDataSize);
    result  = (fftw_complex*)
            fftw_malloc(sizeof(fftw_complex) * resultSize);

    for (int i = 0; i < chDataSize; i++) {
        ch1data[i][0] = sampledata->channels.first[i];                          // Store channel data as real values
        ch2data[i][0] = sampledata->channels.second[i];
        ch1data[i][1] = ch2data[i][1] = 0.0;                                    // No complex numbers
    }

    xcorr(ch1data, ch2data, result, chDataSize);

    int delay = 0;      // Number of samples for the delay between both signals
    int peakSampleNum = 0; //TODO
    for (int i = 0; i < resultSize; i++) {
        if (result[i][0] > peakSampleNum) {
            peakSampleNum = result[i][0];
            delay = chDataSize - 1 - i;
        }
    }

    qDebug() << "calcdly " << delay << "peakSampleNum " << peakSampleNum;
    return delay; //TODO
}


procdata XCorrCalc::calc(bufferchunk * const sampledata)
{
    procdata data;

    int32_t dir = calcDirection(sampledata);
    return data; //TODO
}
