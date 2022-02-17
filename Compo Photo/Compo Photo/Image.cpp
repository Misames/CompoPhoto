#include "Image.h"
#include <iostream>

using namespace std;

Image::Image() {
	this->Source = "";
	this->ListPixel =;
	this->Height = 0;
	this->Weight = 0;
	this->DominantColor = RGB();
}
Image::Image(std::string source, std::list<pixel> pixlist, int h , int w , RGB color) {
	this->Source = source;
	this->ListPixel = pixlist;
	this->Height = h;
	this->Weight = w;
	this->DominantColor = color;
}