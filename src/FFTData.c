#include <stdlib.h>
#include "FFTData.h"

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
