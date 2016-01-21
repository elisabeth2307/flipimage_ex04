#include <stdio.h>
#include <stdlib.h>
#include "img.h"

int main (int argc, char* argv[]){
	int error = RET_PBM_OK;

	// check if correct number of commandline arguments
	if (argc !=3){
		fprintf(stderr, "You haven't inserted input and output file!\n");
		return -1;
	}

	// read file
	FILE *f;
	f = fopen(argv[1], "r");
	// call function for read from stream
	PbmImage* image = pbm_image_load_from_stream(f, &error);

	printf("Error: %d\n", error);

	// check if image is empty
	if(image == NULL) {
		fprintf(stderr, "Sorry, something went wrong!\n");
		return -1;
	}



	// allocate memory for input file here or in image?
	// 

	// int pbm_image_flip(PbmImage* image); -> int pbm_image_write_to_stream(PbmImage* img, FILE* targetStream);

	// free input file memory

	return 0;
}
