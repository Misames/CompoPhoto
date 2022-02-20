#pragma once
#include <algorithm>
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
    ~Image();
    Image();
    Image(int, int);
    Image(const Image &);
    Image(string);

    // Setter
    void setData(uint8_t *newData);
    void setWidth(int newWidth);
    void setHeight(int newHeight);
    void setChannels(int newChannel);
    void setSize(size_t newSize);
    void setBufferPix(vector<vector<int>> newBuffer);

    // Getter
    int getWidth() const;
    int getHeight() const;
    int getChannels() const;
    string getFileName() const;
    size_t getSize() const;
    uint8_t *getData() const;
    vector<vector<int>> getPix() const;

    // Method
    void print(string fileOutPutName);
    void resize(int width, int height);
    void castToGrey();

    // à faire
    Image crop(int top, int left, int right, int bot);
    Image merge(Image secondImage);
    Image createMask(vector<Image> images);
};
