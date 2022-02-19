#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <string>

using namespace std;

class Image
{
private:
    int width;
    int height;
    int channels;
    size_t size;
    uint8_t *data;

public:
    Image();
    Image(string src);
    ~Image();

    // setter
    void setData(uint8_t *_data);
    void setWidth(int _width);
    void setHeight(int _height);
    void setChannels(int _channels);
    void setSize(size_t _size);

    // getter
    uint8_t *getData() const;
    int getWidth() const;
    int getHeight() const;
    int getChannels() const;
    size_t getSize() const;

    void load(Image *img, const char *fname);
    void create(Image *img, int width, int height, int channels);
    void save(const Image *img, const char *fname);
    void convertToGrey(Image *img);
    void free(Image *img);

    void merge(Image *img1, Image *img2);
    void resize(Image *img1, Image *img2);
};
