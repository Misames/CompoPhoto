#include "pixel.h"

pixel::pixel() {
	this->color = RGB();
	this->x = 0;
	this->y = 0;
}

RGB::RGB() {
	this->A = 0;
	this->R = 0;
	this->G = 0;
	this->B = 0;
}