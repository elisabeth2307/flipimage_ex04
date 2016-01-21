#include <stdio.h>
#include <stdlib.h>
#include "flip.h"
#define DEBUG

int pbm_image_flip(PbmImage* image) {
	printf("----------------FLIP----------------\n");

	int len = (*image).width*(*image).height;
	char temp;

	// switch first pixel with last and so on
	for (int i = 0; i < len/2; i++) {
		temp = (*image).data[i]; 
		(*image).data[i] = (*image).data[len-i-1];
		(*image).data[len-i-1] = temp;
	}

	#ifdef DEBUG
	printf("Flipped image: \n");
	for (int j = 0; j < len; j++) {
		printf("%c", (*image).data[j]);
	}
	printf("\n------------------------------------\n");
	#endif

	return RET_PBM_OK;
}