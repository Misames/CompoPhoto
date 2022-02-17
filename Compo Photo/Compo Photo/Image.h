#pragma once
#include <iostream>
#include "pixel.h"
#include <list>

class Image 
{
protected:
	std::string Source;
	std::list <pixel> ListPixel;
	int Height;
	int Weight;
	RGB DominantColor;

public :
	Image();
	Image(std::string ,std::list<pixel>,int,int,RGB);

	Image FindMask();
	RGB FindDominance();
	Image CompositionImage();

};

