#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Image
{
private:
    int width;
    int height;
    int channels;
    size_t size;
    uint8_t *data;
    vector<unsigned char> bufferPix;

public:
    Image();
    Image(string src);

    // Setter
    void setData(uint8_t *_data);
    void setWidth(int _width);
    void setHeight(int _height);
    void setChannels(int _channels);
    void setSize(size_t _size);

    // Getter
    uint8_t *getData() const;
    int getWidth() const;
    int getHeight() const;
    int getChannels() const;
    size_t getSize() const;
    vector<unsigned char> getPix() const;

    void create(Image *img, int width, int height, int channels);
    void save(string fname);
    void convertToGrey();
    void free();
    void merge(Image);
    void resize(int, int);
};
