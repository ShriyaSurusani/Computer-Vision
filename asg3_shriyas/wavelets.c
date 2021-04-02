#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "wavelets.h"

//Initializing Low-pass and high-pass filters (HAAR)
WVLT *wavelet()
{
	WVLT *filter;
	filter=(WVLT *)malloc(sizeof(WVLT));
	
	filter->len = 2;

	//Decomposition low-pass filter
	filter->h[0] = 0.7071067811865476;
	filter->h[1] = 0.7071067811865476;
	
	//Decomposition high-pass filter;
	filter->g[0] = -0.7071067811865476;
	filter->g[1] = 0.7071067811865476; 	
	
	//Reconstruction low-pass filter
	filter->ht[0] = 0.7071067811865476;
	filter->ht[1] = 0.7071067811865476;
	
	//Recontruction high-pass filter
	filter->gt[0] = 0.7071067811865476;
	filter->gt[1] = -0.7071067811865476;

	printf("Initialized filter \n");
	
	return filter;
	
}

	
	

	



