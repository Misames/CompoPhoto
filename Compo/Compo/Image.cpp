#include "Image.h"


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>


void Image::Image_load(Image* img, const char* fname) {
	if ((img->data = stbi_load(fname, &img->width, &img->height, &img->channels, 0)) != NULL) {
		img->size = (img->width * img->height) * img->channels;
	}
}


void Image::Image_create(Image* img, int width, int height, int channels) {
	size_t size = (width * height )* channels;

	if (img->data != NULL) {
		img->width = width;
		img->height = height;
		img->channels = channels;
		img->size = size;
	}
}


void Image::Image_save(const Image* img, const char* fname) {

	stbi_write_jpg(fname, img->width, img->height, img->channels, img->data, 100);
}


void Image::Image_free(Image* img) {

	if (img->data != NULL) {
		stbi_image_free(img->data);
		img->data = NULL;
		img->width = 0;
		img->height = 0;
		img->channels = 0;
		img->size = 0;
	}

}

void Image::Image_to_gray(Image* img) {

	if (img->channels < 3) {
		printf("Image déja en niveau de gris \n ");
	}
	else {
		for (int i = 0; i < img->size; i+=img->channels) {
			// On fait la moyenne de la couleur de nos pixels puis on divise par 3 pour obtenir le niv de gris 
			int gray = (img->data[i] + img->data[i + 1] + img->data[i + 2]) /3;
			memset(img->data + i, gray, 3);
		}
	}
}

void Image::setData(uint8_t* _data) {
	this->data = _data;
}
