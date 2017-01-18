all: KissFFT
	gcc -o ph kiss_fft.o plotHeftig.c -lm
KissFFT: KissFFT/kiss_fft.c
	gcc -c KissFFT/kiss_fft.c -lm
