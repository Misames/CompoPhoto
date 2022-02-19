#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

class Image
{
private:
    int width;
    int height;
    int channels;
    size_t size;
    uint8_t *data;

public:
    void load(Image *img, const char *fname);
    void create(Image *img, int width, int height, int channels);
    void save(const Image *img, const char *fname);
    void converToGrey(Image *img);
    void free(Image *img);
    void setData(uint8_t *_data);
};
