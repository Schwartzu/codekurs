#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "bitmap.h"

typedef struct _blurFilter
{
	size_t width;
	size_t height;
	double *weights;
} blurFilter;

int erzeugeGaussFilter(int dim, blurFilter *filter);
int wendeFilterAn(const bitmapRGB *original, blurFilter *filter, bitmapRGB *filterung);

double gauss2dim(double sigma, int x, int y);

pixelRGB *getpixel(const bitmapRGB *map, int x, int y);

void print_status(int status);

int main(int argc, char *argv[])
{
	int status;
	int dimension;

	bitmapRGB src_bmp;
	bitmapRGB fil_bmp;
	blurFilter filter;

	if(argc != 4 || !isdigit(argv[3][0]))
	{
		printf("Ungueltige Eingabe!\n");
		return 1;
	}

	dimension = atoi(argv[3]);

	if(dimension % 2 == 0)
	{
		printf("Ungueltige Dimension!\n");
		return 1;
	}


	if((status = loadBitmapRGB(argv[1], &src_bmp)) != BMP_OK)
	{
		print_status(status);
		return 1;
	}

	if(!erzeugeGaussFilter(dimension, &filter))
	{
		print_status(status);
		free(src_bmp.pixel);
		return 1;
	}

	printf("Filter erfolgreich erstellt!\n");

	if(wendeFilterAn(&src_bmp, &filter, &fil_bmp))
	{
		print_status(status);
		free(filter.weights);
		free(src_bmp.pixel);
		free(fil_bmp.pixel);
		return 1;
	}

	printf("Filter erfolgreich angewandt!\n");

	if((status = saveBitmapRGB(argv[2], &fil_bmp)) != BMP_OK)
	{
		print_status(status);
		free(filter.weights);
		free(src_bmp.pixel);
		free(fil_bmp.pixel);
		return 1;
	}

	printf("Bitmap erfolgreich gespeichert!\n");

	free(filter.weights);
	free(src_bmp.pixel);
	free(fil_bmp.pixel);

	return 0;
}

int erzeugeGaussFilter(int dim, blurFilter *filter)
{
	double sigma;
	int x, y;

	if(dim % 2 == 0)
		return 1;

	filter->width = dim;
	filter->height = dim;

	sigma = (double) dim / 3;

	filter->weights = malloc(dim * dim * sizeof(double));

	if(filter->weights == NULL)
		return 1;

	for(y = 0; y < dim; y++)
		for(x = 0; x < dim; x++)
			filter->weights[y * dim + x] = gauss2dim(sigma, x - ((dim - 1) / 2), y - ((dim - 1) / 2));

	return 1;

}

int wendeFilterAn(const bitmapRGB *original, blurFilter *filter, bitmapRGB *filterung)
{
	int x, y, i, j;
	int size = original->width * original->height;
	double buff = 0;
	double sum = 0;
	int d_2 = filter->width / 2;

	filterung->width = original->width;
	filterung->height = original->height;

	filterung->pixel = malloc(size * sizeof(pixelRGB));
	if(filterung->pixel == NULL)
	{
		printf("Fehler beim allokieren der Pixel!\n");	
		return BMP_MEMORY_ERROR;
	}


	for(y = 0; y < original->width; y++)
		for(x = 0; x < original->height; x++)
		{
			buff = 0;
			sum = 0;
			for(i = 0; i < (int) filter->width; i++){
				for(j = 0; j < (int) filter->height; j++){
					if(!(x + j - d_2 < 0 || y + i - d_2 < 0 || x + j - d_2 >= original->width || y + i - d_2 >= original->height)){
						buff += getpixel(original, x + j - d_2, y + i - d_2)->green * filter->weights[i * filter->width + j];
						sum += filter->weights[i * filter->width + j];
					}
				}
			}
			filterung->pixel[y * original->width + x].green = (int) (buff/sum);	

			buff = 0;
			sum = 0;
			for(i = 0; i < (int) filter->width; i++){
				for(j = 0; j < (int) filter->height; j++){
					if(!(x + j - d_2 < 0 || y + i - d_2 < 0 || x + j - d_2 >= original->width || y + i - d_2 >= original->height)){
						buff += getpixel(original, x + j - d_2, y + i - d_2)->red * filter->weights[i * filter->width + j];
						sum += filter->weights[i * filter->width + j];
					}
				}
			}
			filterung->pixel[y * original->width + x].red = (int) (buff/sum);	

			buff = 0;
			sum = 0;
			for(i = 0; i < (int) filter->width; i++){
				for(j = 0; j < (int) filter->height; j++){
					if(!(x + j - d_2 < 0 || y + i - d_2 < 0 || x + j - d_2 >= original->width || y + i - d_2 >= original->height)){
						buff += getpixel(original, x + j - d_2, y + i - d_2)->blue * filter->weights[i * filter->width + j];
						sum += filter->weights[i * filter->width + j];
					}
				}
			}
			filterung->pixel[y * original->width + x].blue = (int) (buff/sum);
		}

	return 0;
}


double gauss2dim(double sigma, int x, int y)
{
	return exp(-((x * x + y * y) / (2 * (sigma * sigma))));
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

pixelRGB *getpixel(const bitmapRGB *map, int x, int y)
{
	return(&(map->pixel[y * map->width + x]));
}