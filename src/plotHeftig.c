#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "readWAV.h"


float** getHeftigheid(char* audiosource)
{
}

int main(int argc, char* argv[])
{
	if (argc < 2) 
	{
		printf("Usage: %s <audiofile>.wav\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	getHeftigheid(argv[1]);
	return EXIT_SUCCESS;
}
