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
    this->fileName = "default.jpg";
    this->size = 0;
    this->data = 0;
    this->bufferPix = {};
}

Image::Image(const Image &cpy) : width(cpy.getWidth()), height(cpy.getHeight()), channels(cpy.getChannels()), data(cpy.getData()), size(cpy.getSize()), fileName(cpy.getSrc()), bufferPix(cpy.getPix())
{
}

Image::Image(int w, int h)
{
    this->width = w;
    this->height = h;
    this->channels = 3;
    this->fileName = "default.jpg";
    this->size = w * h * 3;
    this->data = 0;
    this->bufferPix = {};
}

Image::Image(string src)
{
    this->data = stbi_load(src.c_str(), &this->width, &this->height, &this->channels, 0);
    if (this->data != nullptr)
    {
        this->fileName = src;
        this->size = (this->width * this->height) * this->channels;
        this->bufferPix = vector<unsigned int>(this->data, this->data + this->width * this->height * 3);
    }
    else
    {
        this->width = 0;
        this->height = 0;
        this->channels = 0;
        this->fileName = "default.jpg";
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

void Image::setBufferPix(vector<unsigned int> newBuffer)
{
    this->bufferPix = newBuffer;
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

vector<unsigned int> Image::getPix() const
{
    return this->bufferPix;
}

string Image::getSrc() const
{
    return this->fileName;
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

Image Image::resize(int w, int h)
{
    Image res = Image(w, h);
    float rotaX = this->width / w;
    float rotaY = this->height / h;
    res.setBufferPix(this->getPix());
    res.setData(this->getData());

    for (int x = 0; x < this->width; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            res.bufferPix[x + y * width] = this->bufferPix[x * rotaX + y * rotaY];
        }
    }

    return res;
}

void Image::merge(Image img)
{
    for (int i = 0; i < this->size; i++)
        this->data[i] += this->data[i];
}

Image Image::crop(int top, int left, int bottom, int right)
{
    Image res = Image(*this);
    // algo de crop sur image copier
    return res;
}