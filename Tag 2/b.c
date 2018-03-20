#include <stdio.h>
#include <stdlib.h>

#include "bitmap.h"

int konvertiere(const bitmapRGB *original, bitmapGray *konvertierung);

void print_status(int status);

int main(int argc, char *argv[])
{
	int status;

	bitmapRGB src_bmp;
	bitmapGray kon_bmp;

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

	if(konvertiere(&src_bmp, &kon_bmp) != 0)
	{
		print_status(status);
		free(src_bmp.pixel);
		return 1;
	}

	printf("Erflogleich konvertiert!\n");

	if((status = saveBitmapGray(argv[2], &kon_bmp)) != BMP_OK)
	{
		print_status(status);
		free(src_bmp.pixel);
		free(kon_bmp.pixel);
		return 1;
	}

	printf("Bitmap erfolgreich konvertiert!\n");


	free(src_bmp.pixel);
	free(kon_bmp.pixel);

	return 0;
}

int konvertiere(const bitmapRGB *original, bitmapGray *konvertierung)
{
	unsigned int i;
	unsigned int size = original->width * original->height	;

	konvertierung->width = original->width;
	konvertierung->height = original->height;

	konvertierung->pixel = malloc(size * sizeof(pixelGray));
	if(konvertierung->pixel == NULL)
	{
		printf("Fehler beim allokieren der Pixel!\n");	
		return BMP_MEMORY_ERROR;
	}

	for(i = 0; i < size; i++)
	{
		konvertierung->pixel[i].luminance =	 0.299 * original->pixel[i].red 
										   + 0.587 * original->pixel[i].green 
										   + 0.114 * original->pixel[i].blue;
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