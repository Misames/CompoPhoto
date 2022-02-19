#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "pixel.h"

class Image
{
private :

	int width;
	int height;
	int channels;
	size_t size;
	uint8_t *data;
	std::vector<unsigned char> pixtab;

public :
	Image();
	Image(const Image* img);
	//~Image();
	//setter
	void setData(uint8_t* _data);
	void setWidth(int _width);
	void setHeight(int _height);
	void setChannels(int _channels);
	void setSize(size_t _size);
	void setpixtab(std::vector<unsigned char> _pixtab);

	//getter
	uint8_t* getData() const;
	int getWidth() const;
	int getHeight() const;
	int getChannels() const;
	size_t getSize() const;
	std::vector<unsigned char> getPixtab();

	void Image_load(Image* img, const char* fname);
	void Image_create(Image * img, int width, int height, int channels);
	void Image_save(const Image * img, const char* fname);
	void Image_to_gray(Image* img);
	void Image_free(Image * img);
	
	void Image_fusion(Image* img1, Image* img2);
	void Image_resize(Image* img1, Image* img2);
};

