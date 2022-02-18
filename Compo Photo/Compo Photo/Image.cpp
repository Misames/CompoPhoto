#include "Image.h"
#include <iostream>
#include <stdlib.h>
#include "pixel.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

Image::Image() {
	this->Source = "";
	this->ListPixel ;
	this->Height = 0;
	this->Width = 0;
	this->DominantColor = RGB();
}

Image::Image(string Source) {
	this->Source = Source;
	int channel;
	unsigned char* img = stbi_load("lena.jpg",&this->Height, &this->Width, &channel,0);


	this->ListPixel;
	this->Height = 0;
	this->Width = 0;
	this->DominantColor = RGB();
}

Image::Image(string source, list<Pixel> *pixlist, int h , int w , RGB color) {
	this->Source = source;
	this->ListPixel = pixlist;
	this->Height = h;
	this->Width = w;
	this->DominantColor = color;
}

int Image::loadImage(const char* path) {

	


}

int Image::getHeight() {
	return this->Height;
}