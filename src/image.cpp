#include "image.hpp"

using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>

////////////////
// Constructeur/
////////////////

Image::Image()
{
    width = 0;
    height = 0;
    channels = 0;
    data = 0;
    size = 0;
}

Image::Image(string src)
{
    cout<<src<<endl;
    data = stbi_load(src.c_str(), &width, &height, &channels, 0);
    if (data != nullptr)
    {
        size = (width * height) * channels;
        bufferPix.reserve(size);
        
        for(int i = 0; i<size; i += channels){
            bufferPix.push_back({*(data+i),*(data+i+1),*(data+i+2)});
        }
    }
    else
    {
        width = 0;
        height = 0;
        channels = 0;
        data = 0;
        size = 0;
    }
}

///////////
// Setter /
///////////

void Image::setData(uint8_t *_data)
{
    data = _data;
}

void Image::setWidth(int _width)
{
    width = _width;
}

void Image::setHeight(int _height)
{
    height = _height;
}

void Image::setChannels(int _channels)
{
    channels = _channels;
}

void Image::setSize(size_t _size)
{
    size = _size;
}

///////////
// Getter /
///////////

uint8_t *Image::getData() const
{
    return data;
}

int Image::getWidth() const
{
    return width;
}

int Image::getHeight() const
{
    return height;
}

int Image::getChannels() const
{
    return channels;
}

size_t Image::getSize() const
{
    return size;
}

vector<vector<int>> Image::getPix() const
{
    return bufferPix;
}

void Image::create(Image *img, int width, int height, int channels)
{
    size_t size = (width * height) * channels;
    if (img->data != NULL)
    {
        img->width = width;
        img->height = height;
        img->channels = channels;
        img->size = size;
    }
}

void Image::save(string fname)
{
    stbi_write_jpg(fname.c_str(), width, height, channels, data, 100);
}

void Image::free()
{
    if (data != nullptr)
    {
        stbi_image_free(data);
        data = NULL;
        width = 0;
        height = 0;
        channels = 0;
        size = 0;
    }
}

void Image::convertToGrey()
{
    if (channels < 3)
        printf("Image déjà en niveau de gris\n");
    else
    {
        for (int i = 0; i < size; i += channels)
        {
            // On fait la moyenne de la couleur de nos pixels puis on divise par 3 pour obtenir le niv de gris
            int gray = (data[i] + data[i + 1] + data[i + 2]) / 3;
            memset(data + i, gray, 3);
        }
    }
}

void Image::resize(int w, int h)
{
    float rotaX = width / w;
    float rotaY = height / h;
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < width; y++)
        {
        }
    }
}

void Image::merge(Image img)
{
    for (int i = 0; i < size; i++)
        data[i] += data[i];
}
