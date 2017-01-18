#include <stdlib.h>
#ifndef FFTDATA
#define FFTDATA

typedef struct {
	double** samples;
	int window;
	int size;
	int maxSize;
} FFTData;

FFTData newFFTData(int window);
void addSample(FFTData* data, double* sample);
double** getSamples(FFTData data);
void freeFFTData(FFTData data);
void normalize(FFTData data);
double* analyseFFTData(FFTData data);
#endif
