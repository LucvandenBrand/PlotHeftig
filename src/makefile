all: KissFFT FFTData
	gcc -o ph kiss_fft.o FFTData.o plotHeftig.c  -lm
KissFFT: KissFFT/kiss_fft.c
	gcc -c KissFFT/kiss_fft.c -lm
FFTData: FFTData.c
	gcc -c FFTData.c
