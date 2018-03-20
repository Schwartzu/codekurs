#include <stdio.h>
#include <stdlib.h>

#include "bitmap.h"

int spiegelH(const bitmapRGB *original, bitmapRGB *spiegelung);
int spiegelV(const bitmapRGB *original, bitmapRGB *spiegelung);

void print_status(int status);

int main(int argc, char *argv[])
{
	int status;

	bitmapRGB src_bmp;
	bitmapRGB inv_bmp;

	if(argc != 4 || argv[3][1] != '\0' || (argv[3][0] != 'h' && argv[3][0] != 'v'))
	{
		printf("Ungueltige Eingabe!\n");
		return 1;
	}

	if((status = loadBitmapRGB(argv[1], &src_bmp)) != BMP_OK)
	{
		print_status(status);
		return 1;
	}

	if(argv[3][0] == 'h')
		status = spiegelH(&src_bmp, &inv_bmp);
	else
		status = spiegelV(&src_bmp, &inv_bmp);

	if(status != 0)
	{
		printf("Fehler beim Spiegeln!\n");
		free(src_bmp.pixel);
		return 1;
	}
	printf("Erflogleich gespiegelt!\n");

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

int spiegelH(const bitmapRGB *original, bitmapRGB *spiegelung)
{
	unsigned int y, x;
	unsigned int width = original->width;
	unsigned int height = original->height;
	unsigned int size = width * height;

	spiegelung->width = width;
	spiegelung->height = height;

	spiegelung->pixel = malloc(size * sizeof(pixelRGB));
	if(spiegelung->pixel == NULL)
	{
		printf("Fehler beim allokieren der Pixel!\n");	
		return BMP_MEMORY_ERROR;
	}

	for(y = 0; y < height; y++)
		for(x = 0; x < width; x++)
			spiegelung->pixel[y * width + x] = original->pixel[(height - y) * width + x];

	return 0;
}

int spiegelV(const bitmapRGB *original, bitmapRGB *spiegelung)
{
	unsigned int y, x;
	unsigned int width = original->width;
	unsigned int height = original->height;
	unsigned int size = width * height;

	spiegelung->width = width;
	spiegelung->height = height;

	spiegelung->pixel = malloc(size * sizeof(pixelRGB));
	if(spiegelung->pixel == NULL)
	{
		printf("Fehler beim allokieren der Pixel!\n");	
		return BMP_MEMORY_ERROR;
	}

	for(y = 0; y < height; y++)
		for(x = 0; x < width; x++)
			spiegelung->pixel[y * width + x] = original->pixel[y * width + (width - x)];
		
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