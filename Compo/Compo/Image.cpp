#include "Image.h"
using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../lib/stb/stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../lib/stb/stb_image_resize.h"

////////////////
//Constructeur//
////////////////

Image::Image() {
	this->width = 0;
	this->height = 0;
	this->channels = 0;
	this->data = 0;
	this->size = 0;
}

Image::Image(const Image* img) {
	this->width = img->width;
	this->height = img->height;
	this->channels = img->channels;
	this->data = img->data;
	this->size = img->size;
}
///////////////
//Destructeur//
///////////////

Image::~Image() {
	delete this;
}

//////////
//Setter//
//////////

void Image::setData(uint8_t* _data) {
	this->data = _data;
}
void Image::setWidth(int _width) {
	this->width = _width;
}
void Image::setHeight(int _height) {
	this->height = _height;
}
void Image::setChannels(int _channels) {
	this->channels = _channels;
}
void Image::setSize(size_t _size) {
	this->size = _size;
}

//////////
//Getter//
//////////

uint8_t* Image::getData() const {
	return this->data;
}
int Image::getWidth() const {
	return this->width;
}
int Image::getHeight() const {
	return this->height;
}
int Image::getChannels() const {
	return this->channels;
}
size_t Image::getSize() const {
	return this->size;
}



void Image::Image_load(Image* img, const char* fname) {
	if ((img->data = stbi_load(fname, &img->width, &img->height, &img->channels, 0)) != NULL) {
		img->size = (img->width * img->height) * img->channels;
	}
}


void Image::Image_create(Image* img, int width, int height, int channels) {
	size_t size = (width * height) * channels;

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
		for (int i = 0; i < img->size; i += img->channels) {
			// On fait la moyenne de la couleur de nos pixels puis on divise par 3 pour obtenir le niv de gris 
			int gray = (img->data[i] + img->data[i + 1] + img->data[i + 2]) / 3;
			memset(img->data + i, gray, 3);
		}
	}
}

void Image::Image_resize(Image* img1, Image* img2) {

	stbir_resize(img2->data, img2->width, img2->height, 0, img1->data, img1->width, img1->height, 0, STBIR_TYPE_UINT8, img2->channels, STBIR_ALPHA_CHANNEL_NONE, 0,
		STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP,
		STBIR_FILTER_BOX, STBIR_FILTER_BOX,
		STBIR_COLORSPACE_SRGB, nullptr);

}

void Image::Image_fusion(Image* img1, Image* img2) {

	for (int i = 0; i < img1->size; i++) {
		img1->data[i] += img2->data[i];
	}

}
