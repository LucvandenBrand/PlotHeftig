#include <stdlib.h>
#include "FFTData.h"

#define MAXDOUBLE 300000

FFTData newFFTData(int window)
{
	FFTData data;
	data.samples = NULL;
	data.size = 0;
	data.maxSize = 0;
	data.window = window;
	return data;
}

void resize(FFTData* data)
{
	if (data->size >= data->maxSize) {
		while (data->size >= data->maxSize) 
			data->maxSize = (data->maxSize == 0) ? 2 : data->maxSize * 2;
		data->samples = realloc(data->samples, sizeof(double*) * data->maxSize);
		for (int i = data->size; i < data->maxSize; ++i)
			data->samples[i] = NULL;
	}
}

void addSample(FFTData* data, double* sample)
{
	resize(data);
	data->samples[data->size++] = sample;
}

void normalize(FFTData data)
{
	double maxValue = -1;
	double minValue = MAXDOUBLE;
	for (int y=0; y<data.window; y++) {
		for (int x=0; x<data.size; x++) {
			if (data.samples[x][y] > maxValue) {
				maxValue = data.samples[x][y];
			} else if (data.samples[x][y] < minValue) {
				minValue = data.samples[x][y];
			}
		}
	}
	double scaleValue = (maxValue - minValue);
	
	for (int y=0; y<data.window; y++) {
		for (int x=0; x<data.size; x++) {
			data.samples[x][y] -= minValue;
			data.samples[x][y] /= scaleValue;
		}
	}
}

double* analyseFFTData(FFTData data)
{
	double* samples = malloc(sizeof(double) * data.size);
	for (int x=0; x < data.size; ++x) {
		double sum = 0;
		for (int y=0; y < data.window; ++y) {
			sum += data.samples[x][y];
		}
		samples[x] = sum;
	}
	return samples;
}

double** getSamples(FFTData data) 
{
	return data.samples;
}

void freeFFTData(FFTData data)
{
	for (int i = 0; i < data.size; ++i)
		free(data.samples[i]);
	free(data.samples);
}
