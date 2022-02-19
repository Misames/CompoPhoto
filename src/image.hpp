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
    string fileName;
    size_t size;
    uint8_t *data;
    vector<vector<int>> bufferPix;

public:
    // Constructor
    Image();
    Image(int, int);
    Image(const Image &);
    Image(string src);

    // Setter
    void setData(uint8_t *_data);
    void setWidth(int _width);
    void setHeight(int _height);
    void setChannels(int _channels);
    void setSize(size_t _size);
    void setBufferPix(vector<unsigned int>);

    // Getter
    int getWidth() const;
    int getHeight() const;
    int getChannels() const;
    string getSrc() const;
    size_t getSize() const;
    vector<vector<int>> getPix() const;

    // Method
    void create(Image *img, int width, int height, int channels);
    void save(string fname);
    void convertToGrey();
    void free();
    void merge(Image);
    Image resize(int, int);
    Image crop(int, int, int, int);
};
