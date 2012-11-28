#ifndef XCORR
#define XCORR

#include <complex.h>
#include <fftw3.h>

#ifdef __cplusplus
extern "C" {
#endif

void xcorr(fftw_complex *, fftw_complex *, fftw_complex *, int);

#ifdef __cplusplus
}
#endif

#endif
