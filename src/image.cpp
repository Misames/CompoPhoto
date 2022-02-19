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
    this->width = 0;
    this->height = 0;
    this->channels = 0;
    this->data = 0;
    this->size = 0;
}

Image::Image(string src)
{
    this->data = stbi_load(src.c_str(), &this->width, &this->height, &this->channels, 0);
    if (this->data != nullptr)
    {
        this->size = (this->width * this->height) * this->channels;
        this->bufferPix = vector<unsigned char>(this->data, this->data + this->width * this->height * 3);
    }
    else
    {
        this->width = 0;
        this->height = 0;
        this->channels = 0;
        this->data = 0;
        this->size = 0;
    }
}

///////////
// Setter /
///////////

void Image::setData(uint8_t *_data)
{
    this->data = _data;
}

void Image::setWidth(int _width)
{
    this->width = _width;
}

void Image::setHeight(int _height)
{
    this->height = _height;
}

void Image::setChannels(int _channels)
{
    this->channels = _channels;
}

void Image::setSize(size_t _size)
{
    this->size = _size;
}

///////////
// Getter /
///////////

uint8_t *Image::getData() const
{
    return this->data;
}

int Image::getWidth() const
{
    return this->width;
}

int Image::getHeight() const
{
    return this->height;
}

int Image::getChannels() const
{
    return this->channels;
}

size_t Image::getSize() const
{
    return this->size;
}

vector<unsigned char> Image::getPix() const
{
    return this->bufferPix;
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
    stbi_write_jpg(fname.c_str(), this->width, this->height, this->channels, this->data, 100);
}

void Image::free()
{
    if (this->data != nullptr)
    {
        stbi_image_free(this->data);
        this->data = NULL;
        this->width = 0;
        this->height = 0;
        this->channels = 0;
        this->size = 0;
    }
}

void Image::convertToGrey()
{
    if (this->channels < 3)
        printf("Image déjà en niveau de gris\n");
    else
    {
        for (int i = 0; i < this->size; i += this->channels)
        {
            // On fait la moyenne de la couleur de nos pixels puis on divise par 3 pour obtenir le niv de gris
            int gray = (this->data[i] + this->data[i + 1] + this->data[i + 2]) / 3;
            memset(this->data + i, gray, 3);
        }
    }
}

void Image::resize(int w, int h)
{
    float rotaX = this->width / w;
    float rotaY = this->height / h;
    for (int x = 0; x < this->width; x++)
    {
        for (int y = 0; y < this->width; y++)
        {
        }
    }
}

void Image::merge(Image img)
{
    for (int i = 0; i < this->size; i++)
        this->data[i] += this->data[i];
}
