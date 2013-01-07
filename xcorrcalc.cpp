#include "xcorrcalc.h"
#include "libxcorr/xcorr.h"
#include <QDebug>
#include <cmath>

QMutex  XCorrCalc::m_fftw;
int     XCorrCalc::directionMem[] = {0, 0};

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
    int const samplesPerPeriod  = 500;                                          // 1000 Samples for 2 Periods
    int const hypotenuse = samplesPerPeriod / 4;                                // Distance between both antennas = lambda / 4
    double signalAmplitude = 0.0;                                               // Holds the signal amplitude of the first channel.
    double signalAmplification = 1.0;                                           // Artificial amplification factor for the FFT calculation.
    double const pi = 3.14159265;

    ch1data = (fftw_complex*)
            fftw_malloc(sizeof(fftw_complex) * chDataSize);
    ch2data = (fftw_complex*)
            fftw_malloc(sizeof(fftw_complex) * chDataSize);
    result  = (fftw_complex*)
            fftw_malloc(sizeof(fftw_complex) * resultSize);

    for (int i = 0; i < chDataSize; i++) {                                      // Get signal amplitude
        if (sampledata->channels.first[i] > signalAmplitude) {
            signalAmplitude = sampledata->channels.first[i];
        }
    }

    // TODO: Set signalAmplification dependent on signalAmpllitude here.
    if (signalAmplitude <= 1e-9) {
        signalAmplification = 1.0e12;
    }
    else if ( (signalAmplitude > 1e-9) && (signalAmplitude <= 1e-6)) {
        signalAmplification = 1.0e9;
    }
    else if ( (signalAmplitude > 1e-6) && (signalAmplitude <= 1e-3)) {
        signalAmplification = 1.0e6;
    }
    else if ( (signalAmplitude > 1e-3) && (signalAmplitude <= 1.0)) {
        signalAmplification = 1.0e5;
    }

    for (int i = 0; i < chDataSize; i++) {
        ch1data[i][0] = signalAmplification * sampledata->channels.first[i];    // Store channel data as real values
        ch2data[i][0] = signalAmplification * sampledata->channels.second[i];
        ch1data[i][1] = ch2data[i][1] = 0.0;                                    // No complex numbers
    }

    m_fftw.lock();
    xcorr(ch1data, ch2data, result, chDataSize);
    m_fftw.unlock();

    int32_t delay = 0;      // Number of samples for the delay between both signals
    double peakSampleNum = 0; //TODO
    for (int i = 0; i < resultSize; i++) {
        if (result[i][0] > peakSampleNum) {
            peakSampleNum = result[i][0];
            delay = chDataSize - 1 - i;
        }
    }

    qDebug() << "calcdly " << delay << "peakSampleNum " << peakSampleNum;

    // Calculate direction in degrees
    /* Calculation principle:
     *                   x-- Antenna A
     *                  /|-- theta
     *                 / |hypothenuse
     *                /  |
     *         delay --\ |
     *                   x-- Antenna B
     * sin(theta) = delay / hypothenuse
     * theta: Direction angle
     */
    int32_t signedTheta = asin(delay * 1.0 / hypotenuse) * 180 / pi;            // Calculates Theta (signed)
    qDebug() << "theta (signed, unfiltered)" << signedTheta;
    signedTheta = directionFIRFilter(signedTheta);                              // Do lowpass filtering on angle values
    qDebug() << "theta (signed, filtered)" << signedTheta;
    uint16_t usignedTheta = 0;
    if (signedTheta < 0) {                                                      // For negative delays.
        usignedTheta = 360 + signedTheta;
    }
    else {
        usignedTheta = signedTheta;
    }
    qDebug() << "theta (unsigned)" << usignedTheta;

    data.fields.powerLevel = 0;
    for (int i = 0; peakSampleNum > 10000000; i++) {
        data.fields.powerLevel |= 1 << i;                                       // The number of ones indicate the power level
        peakSampleNum -= 10000000;                                              // E.g. peakSampleNum = 116000000
    }                                                                           // => data.powerlevel = 0x07FF

    data.fields.direction = usignedTheta;

    qDebug() << "Direction (degrees)" << data.fields.direction
             << "Power level" << data.fields.powerLevel;
    return data; //TODO
}

int32_t XCorrCalc::directionFIRFilter(int32_t signedTheta)
{
    int32_t sum = signedTheta;
    for (int i = 0; i < XCORRCALC_DIRMEMSIZE ; i++) {
        sum += directionMem[i];
    }

    for (int i = 1; i < XCORRCALC_DIRMEMSIZE; i++) {
        directionMem[i] = directionMem[i-1];
    }
    directionMem[0] = signedTheta;

    return (sum / (XCORRCALC_DIRMEMSIZE + 1));
}
