#include "Image.h"

int main(int argc, char* argv[])
{
	Image lena, image1;


	lena.Image_load(&lena, "lena.jpg");
	image1.Image_load(&image1, "image1.jpg");
	image1.Image_resize(&lena, &image1);
	image1.Image_fusion(&lena,&image1);
	lena.Image_free(&lena);
	image1.Image_free(&image1);
	
}

