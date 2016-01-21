#include "img.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define DATALENGTH 255

void pbm_image_free(PbmImage* img) {

}


PbmImage* pbm_image_load_from_stream(FILE* stream, int* error) {
	// image which is returned in the end
	PbmImage pbmimage;

	// open input-file and check if it's empty or not
	if (stream == NULL) {
		printf("File is empty\n");
		fclose(stream);
		*error = RET_PBM_ERROR;
		return NULL;
	} 

	printf("File successfully read\n");
	
	// if first line is not P5 -> exit programm
	char str[4]; // 4 is the smallest possible amount of chars for this purpose
	fgets(str, 4, stream);

	if (!strcmp(str, PBM_TYPE_P5)){
		printf("Unsupported format\n");
		fclose(stream);
		*error = RET_UNSUPPORTED_FILE_FORMAT;
		return NULL;
	}

	// get type of image
	char imgtype[3];
	memcpy(imgtype, &str, 3*sizeof(*str));
	// store type in image struct
	strcpy(pbmimage.type, imgtype);

	// skip comments
	char data[DATALENGTH];
	data[0] = '#'; // necessary to get into while-loop
	while (data[0]=='#'){
		fgets(data, DATALENGTH, stream);
	}

	// while loop to get width (first number in line which is stored in data)
	int i = 0;
	char width[4];
	while (data[i] != ' ') {
		width[i] = data[i];
		i++;
	}

	i++; // important to skip space
	int j = 0; // for height array
	char height[4];
	// while loop to get height (second number -> right after space)
	while (data[i] != 0) {
		height[j] = data[i];
		i++;
		j++;
	}

	// convert to integer
	int widthInt = atoi(width);
	int heightInt = atoi(height);

	// store in image struct
	pbmimage.width = widthInt;
	pbmimage.height = heightInt;

	printf("width: %d, height: %d\n", widthInt, heightInt);

	// allocate memory
	uint64_t* = malloc(widthInt*heightInt*sizeof(char));

	// store data in struct
	while(){

	}

	return NULL;
}



int pbm_image_write_to_stream(PbmImage* img, FILE* targetStream) {
	return 0;
}