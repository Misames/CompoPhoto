#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../lib/stb/stb_image_write.h"


class Image
{
private :

	int width;
	int height;
	int channels;
	size_t size;
	uint8_t *data;

public :

	void Image_load(Image* img, const char* fname);
	void Image_create(Image * img, int width, int height, int channels);
	void Image_save(const Image * img, const char* fname);
	void Image_to_gray(Image* img);
	void Image_free(Image * img);

	void setData(uint8_t* _data);

};

