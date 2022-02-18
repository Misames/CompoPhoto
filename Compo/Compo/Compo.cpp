

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Image.h"


int main()
{
	Image lena;


	lena.Image_load(&lena, "lena.jpg");
	lena.Image_to_gray(&lena);
	lena.Image_save(&lena, "lenaGray.jpg");
	lena.Image_free(&lena);
	
}

