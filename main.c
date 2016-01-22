#include <stdio.h>
#include <stdlib.h>
#include "img.h"
#include "flip.h"

int main (int argc, char* argv[]){
	int error = RET_PBM_OK;

	// check if correct number of commandline arguments
	if (argc !=3){
		fprintf(stderr, "You haven't inserted input and output file!\n");
		return -1;
	}

	//----------------------------------------------------------------------------
	// open files
	FILE *f;
	f = fopen(argv[1], "r");


	FILE *destf;
	destf = fopen(argv[2], "w");
	
	//----------------------------------------------------------------------------

	// call function for read from stream
	PbmImage* image = pbm_image_load_from_stream(f, &error);
	printf("Error: %d\n", error);

	// check if image is empty
	if(image == NULL) {
		fprintf(stderr, "Sorry, something went wrong!\n");
		return -1;
	}

	// flip image
	error = pbm_image_flip (image);
	printf("Error: %d\n", error);

	// write flipped image to out-file
	error = pbm_image_write_to_stream(image, destf);
	printf("Error: %d\n", error);


	// free input file memory

	// close files?

	return 0;
}
