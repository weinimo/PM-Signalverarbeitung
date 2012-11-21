#include "xcorrcalc.h"
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
    float xcorrVector[SPROC_SAMPLEDATASIZE - 1];
    float chan1Vector[SPROC_SAMPLEDATASIZE - 1];

    int vectorSize = SPROC_SAMPLEDATASIZE - 1;
    int chanDataSize = SPROC_SAMPLEDATASIZE / 2;

    memset(xcorrVector, 0, vectorSize * sizeof(float));
    memset(chan1Vector, 0, (chanDataSize - 1) * sizeof(float));

#pragma omp parallel for
    for (int i = 0; i < chanDataSize; i++) {                                    // Prepare first channel vector
        chan1Vector[(chanDataSize - 1) + i] =
                sampledata->channels.first[i];
    }

    float peakVal = 0.0F;                                                       // Stores the maximal value of the x-corr
    int peakSampleNum = 0;                                                      // Stores the delay between the signals in sample periods.

    for (int i = 0; i < chanDataSize; i++) {
        for (int j = 0; j < vectorSize; j++) {                                  // Compute the x-corr calc.
            xcorrVector[i] +=
                    chan1Vector[j] * sampledata->channels.second[j];
        }

        if (xcorrVector[i] > peakVal) {                                         // Get the delay by finding the maximal value of xcorrVector
            peakVal = xcorrVector[i];
            peakSampleNum = i;
        }
    }

    qDebug() << "peakSampleNum " << peakSampleNum;
    return peakSampleNum; //TODO
}


procdata XCorrCalc::calc(bufferchunk * const sampledata)
{
    procdata data;

    int32_t dir = calcDirection(sampledata);
    return data; //TODO
}
