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
    Image(string);

    // Setter
    void setData(uint8_t *);
    void setWidth(int);
    void setHeight(int);
    void setChannels(int);
    void setSize(size_t);
    void setBufferPix(vector<vector<int>>);

    // Getter
    int getWidth() const;
    int getHeight() const;
    int getChannels() const;
    string getFileName() const;
    size_t getSize() const;
    uint8_t *getData() const;
    vector<vector<int>> getBufferPix() const;

    // Method
    void print(string);
    void free();
    void castToGrey();
    Image merge(Image);
    Image resize(int, int);
    Image crop(int, int, int, int);
    Image createMask(vector<Image>);
};
