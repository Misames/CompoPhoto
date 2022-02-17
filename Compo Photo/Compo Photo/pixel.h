#pragma once
#include "Image.h"

struct RGB {
	int R;
	int G;
	int B;
	float A;
	
	RGB();
};

class Pixel
{
	RGB color;
	int x;
	int y;

public :
	Pixel();

};

