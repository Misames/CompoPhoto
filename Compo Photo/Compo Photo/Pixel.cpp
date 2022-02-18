#include "pixel.h"

Pixel::Pixel() {
	this->color = RGB();
	this->x = 0;
	this->y = 0;
}
Pixel::Pixel(RGB Color , int X , int Y ) {
	this->color = Color;
	this->x = X;
	this->y = Y;
}

RGB::RGB() {
	this->A = 0;
	this->R = 0;
	this->G = 0;
	this->B = 0;
}

RGB::RGB(int r , int g, int b , float a) {
	this->A = a;
	this->R = r;
	this->G = g;
	this->B = b;
}