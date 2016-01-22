#include "img.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define DATALENGTH 255
//#define DEBUG

void pbm_image_free(PbmImage* img) {
	free(img);
}


PbmImage* pbm_image_load_from_stream(FILE* stream, int* error) {
	printf("--------------IMAGE-READ-------------\n");
	// image which is returned in the end
	PbmImage* pbmimage = malloc (sizeof(PbmImage));

	//--------------------------------------------------------------------
	// open input-file and check if it's empty or not
	if (stream == NULL) {
		printf("File is empty\n");
		fclose(stream);
		*error = RET_PBM_ERROR;
		return NULL;
	} 

	printf("File successfully read\n");
	
	// if first line is not P5 -> exit programm
	//char str[3]; // 4 is the smallest possible amount of chars for this purpose
	fgets((*pbmimage).type, 4, stream);

	#ifdef DEBUG
		printf("%c\n", str[0]);
		printf("%c\n", str[1]);
		printf("%c\n", str[2]);
		printf("%c\n", str[3]);
	#endif

	if (!strcmp((*pbmimage).type, PBM_TYPE_P5)){
		printf("Unsupported format\n");
		fclose(stream);
		*error = RET_UNSUPPORTED_FILE_FORMAT;
		return NULL;
	}

	//--------------------------------------------------------------------
	// get type of image
	//char imgtype[3];
	//memcpy(imgtype, &str, 3*sizeof(*str));
	// store type in image struct
	//strcpy((*pbmimage).type, imgtype);

	//--------------------------------------------------------------------
	// skip comments
	char data[DATALENGTH];
	data[0] = PBM_COMMENT_CHAR; // necessary to get into while-loop
	while (data[0] == PBM_COMMENT_CHAR){
		fgets(data, DATALENGTH, stream);
	}

	//--------------------------------------------------------------------
	// while loop to get width (first number in line which is stored in data)
	int i = 0;
	int j = 0; // for height array
	char height[4]; // we only support images
	char width[4];	// up to 9999x9999 pixels

	while (data[i] != ' ') {
		width[i] = data[i];
		i++;
	}

	i++; // important to skip space
	
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
	(*pbmimage).width = widthInt;
	(*pbmimage).height = heightInt;

	printf("------------------------------------\n");
	printf("width: %d, height: %d\n", widthInt, heightInt);
	
	//--------------------------------------------------------------------
	// eliminate maximum intensity
	fgets(data, 5, stream);
	
	//--------------------------------------------------------------------
	// allocate memory for pixel-bytes
	(*pbmimage).data = malloc(widthInt*heightInt*sizeof(char));

	// read data from file and store in struct
	fread((*pbmimage).data, sizeof(char), widthInt*heightInt, stream);

	#ifdef DEBUG
	for (int k = 0; k<widthInt*heightInt; k++) {
		printf("%c", (*pbmimage).data[k]);
	}
	#endif

	printf("\n------------------------------------\n");
	return (pbmimage);
}



int pbm_image_write_to_stream(PbmImage* img, FILE* targetStream) {
	printf("-------------IMAGE-WRITE-------------\n");
	char* comment = "# FLIPPED by H&H";
	char* intensity = "255\n";
	int pixels = (*img).width * (*img).height;

	// write type, comment and width+height to file
	fprintf(targetStream, "%s%s\n%d %d\n", (*img).type, comment, (*img).width, (*img).height);  // comment + width and height
	fwrite (intensity, sizeof(char), strlen(intensity), targetStream); // intensity
	fwrite((*img).data, sizeof(char), pixels, targetStream); // type

	printf("File successfully written");

	return RET_PBM_OK;
}