#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_DEPRECATE
#include <math.h>
#include "KissFFT/kiss_fft.h"
#include "FFTData.h"

#define WIN 512

FFTData getFFTData(char* music_file)
{
    FILE *in;
    char buf[WIN * 2];
    int nfft = WIN, i, fx;
    double intensity = 0;
    kiss_fft_cfg cfg;
    kiss_fft_cpx cx_in[WIN];
    kiss_fft_cpx cx_out[WIN];
    short *sh;

    cfg = kiss_fft_alloc(nfft, 0, 0, 0);
    in = fopen(music_file, "r");
    if (!in) {
        printf("unable to open file: %s\n", music_file);
        perror("Error");
        exit(EXIT_FAILURE);
    }
    fx = 0;
    
    FFTData data = newFFTData(WIN);
    while (fread(buf, 1, WIN * 2, in)) 
    {
        for (i = 0;i<WIN;i++) {
            sh = (short *)&buf[i * 2];
            cx_in[i].r = (float) (((double)*sh) / 32768.0);
            cx_in[i].i = 0.0;
        }

        kiss_fft(cfg, cx_in, cx_out);
        //Display the value of a position
        int position = 511;
        intensity = sqrt(pow(cx_out[position].r, 2) + pow(cx_out[position].i, 2));
        //printf("%9.4f\n", intensity);

        //Display all values
        
        double* sample = malloc(sizeof(double)*WIN);
        for (i = 0;i<WIN;i++) {
            //printf("Joe: cx_out[i].r:%f\n", cx_out[i].r);
            //printf("Joe: cx_out[i].i:%f\n", cx_out[i].i);
            intensity = sqrt(pow(cx_out[i].r,2) + pow(cx_out[i].i,2));
            //printf("%d - %9.4f\n", i, intensity);
			sample[i] = intensity;
        }
        addSample(&data, sample);
    }
    normalize(data);
    free(cfg);
    return data;
}

void fftDataToImage(char* imgName, FFTData fd)
{
	FILE *f = fopen(imgName, "wb");
	fprintf(f, "P6\n%i %i 255\n", fd.size, fd.window);
	for (int y=0; y<fd.window; y++) {
		for (int x=0; x<fd.size; x++) {
			fputc((char) (fd.samples[x][y]*255), f);   // 0 .. 255
			fputc((char) (fd.samples[x][y]*255), f); // 0 .. 255
			fputc((char) (fd.samples[x][y]*255), f);  // 0 .. 255
		}
	}
	fclose(f);
}

int main(int argc, char* argv[])
{
	if (argc < 2) 
	{
		printf("Usage: %s <audiofile>.wav\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	FFTData fftData = getFFTData(argv[1]);
	fftDataToImage("result.ppm", fftData);
	double* heftigheid = analyseFFTData(fftData);
	freeFFTData(fftData);
	return EXIT_SUCCESS;
}
