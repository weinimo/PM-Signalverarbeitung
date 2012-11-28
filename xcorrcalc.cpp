#include "xcorrcalc.h"
#include "libxcorr/xcorr.h"
#include <QDebug>

QMutex XCorrCalc::m_fftw;

XCorrCalc::XCorrCalc()
{
}

procdata XCorrCalc::calc(bufferchunk * const sampledata)
{
    procdata data;
    data.doubleword = 0;
    fftw_complex * ch1data, * ch2data, * result;
    int const chDataSize        = SPROC_SAMPLEDATASIZE / 2;
    int const resultSize        = 2 * chDataSize - 1;
    int const samplesPerPeriod  = 800; // TODO: Constant calculation formula

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

    m_fftw.lock();
    xcorr(ch1data, ch2data, result, chDataSize);
    m_fftw.unlock();

    int32_t delay = 0;      // Number of samples for the delay between both signals
    int peakSampleNum = 0; //TODO
    for (int i = 0; i < resultSize; i++) {
        if (result[i][0] > peakSampleNum) {
            peakSampleNum = result[i][0];
            delay = chDataSize - 1 - i;
        }
    }

    qDebug() << "calcdly " << delay << "peakSampleNum " << peakSampleNum;

    // Calculate direction in degrees
    if (delay < 0) {                                                            // For negative delays.
        delay *= -1;
        data.fields.direction = 360 - delay * 360 / samplesPerPeriod;
    }
    else {
        data.fields.direction = delay * 360 / samplesPerPeriod;
    }

    data.fields.powerLevel = 0;
    for (int i = 0; peakSampleNum > 10000000; i++) {
        data.fields.powerLevel |= 1 << i;                                       // The number of ones indicate the power level
        peakSampleNum -= 10000000;                                              // E.g. peakSampleNum = 116000000
    }                                                                           // => data.powerlevel = 0x07FF

    qDebug() << "Direction (degrees)" << data.fields.direction
             << "Power level" << data.fields.powerLevel;
    return data; //TODO
}
