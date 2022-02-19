#pragma once
#include <iostream>
#include "pixel.h"
#include <list>


class Image 
{
private:
	std::string Source;
	std::list <Pixel>* ListPixel;
	int Height;
	int Width;
	RGB DominantColor;

public :
	Image();
	Image(std::string ,std::list<Pixel>*,int,int,RGB);
	Image(std::string Source);


	//Image FindMask();
	//RGB FindDominance();
	//Image CompositionImage();
	int loadImage(const char* path);
	int getHeight();



};

