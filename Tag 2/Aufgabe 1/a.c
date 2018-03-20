#include <stdio.h>
#include <stdlib.h>

#include "bitmap.h"

int invertiere(const bitmapRGB *original, bitmapRGB *invertiert);

void print_status(int status);

int main(int argc, char *argv[])
{
	int status;

	bitmapRGB src_bmp;
	bitmapRGB inv_bmp;

	if(argc != 3)
	{
		printf("Ungueltige Eingabe!\n");
		return 1;
	}

	if((status = loadBitmapRGB(argv[1], &src_bmp)) != BMP_OK)
	{
		print_status(status);
		return 1;
	}

	if(invertiere(&src_bmp, &inv_bmp) != 0)
	{
		print_status(status);
		free(src_bmp.pixel);
		return 1;
	}

	printf("Erflogleich invertiert!\n");

	if((status = saveBitmapRGB(argv[2], &inv_bmp)) != BMP_OK)
	{
		print_status(status);
		free(src_bmp.pixel);
		free(inv_bmp.pixel);
		return 1;
	}

	printf("Bitmap erfolgreich invertiert!\n");


	free(src_bmp.pixel);
	free(inv_bmp.pixel);

	return 0;
}

int invertiere(const bitmapRGB *original, bitmapRGB *invertiert)
{
	unsigned int i;
	unsigned int size = original->width * original->height	;

	invertiert->width = original->width;
	invertiert->height = original->height;

	invertiert->pixel = malloc(size * sizeof(pixelRGB));
	if(invertiert->pixel == NULL)
	{
		printf("Fehler beim allokieren der Pixel!\n");	
		return BMP_MEMORY_ERROR;
	}

	for(i = 0; i < size; i++)
	{
		invertiert->pixel[i].blue = 255 - original->pixel[i].blue;
		invertiert->pixel[i].green = 255 - original->pixel[i].green;
		invertiert->pixel[i].red = 255 - original->pixel[i].red;
	}

	return 0;
}

void print_status(int status)
{
	printf("error: %i\n", status);
	if(status == BMP_MEMORY_ERROR) printf("Bitmap memory error!\n");
	else if(status == BMP_READ_ERROR) printf("Bitmap read error!\n");
	else if(status == BMP_WRITE_ERROR) printf("Bitmap write error!\n");
	else if(status == BMP_FILE_ERROR) printf("Bitmap file error!\n");
	else if(status == BMP_FORMAT_NOT_IMPLEMENTED) printf("Bitmap format not implemented!\n");
	else if(status == BMP_FORMAT_ERROR) printf("Bitmap format error!\n");
	else printf("Unknown error!\n");

}