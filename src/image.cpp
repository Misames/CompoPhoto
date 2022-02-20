#include "image.hpp"

using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>

/////////////////
// Constructeur /
/////////////////

Image::Image()
{
    width = 0;
    height = 0;
    channels = 0;
    fileName = "default.jpg";
    size = 0;
    data = 0;
    bufferPix = {};
}

Image::Image(int w, int h)
{
    width = w;
    height = h;
    channels = 3;
    fileName = "default.jpg";
    size = w * h * 3;
    data = 0;
    bufferPix = {};
}

Image::Image(const Image &cpy) : width(cpy.getWidth()), height(cpy.getHeight()), channels(cpy.getChannels()), data(cpy.getData()), size(cpy.getSize()), fileName(cpy.getFileName()), bufferPix(cpy.getPix())
{
}

Image::Image(string src)
{
    data = stbi_load(src.c_str(), &width, &height, &channels, 0);
    if (data != nullptr)
    {
        fileName = src;
        size = (width * height) * channels;
        bufferPix.reserve(size);
        for (int i = 0; i < size; i += channels)
            bufferPix.push_back({*(data + i), *(data + i + 1), *(data + i + 2)});
    }
    else
    {
        width = 0;
        height = 0;
        channels = 0;
        fileName = "default.jpg";
        data = 0;
        size = 0;
        bufferPix = {};
    }
}

///////////
// Setter /
///////////

void Image::setData(uint8_t *data)
{
    this->data = data;
}

void Image::setWidth(int w)
{
    width = w;
}

void Image::setHeight(int h)
{
    height = h;
}

void Image::setChannels(int channel)
{
    this->channels = channel;
}

void Image::setSize(size_t size)
{
    this->size = size;
}

void Image::setBufferPix(vector<vector<int>> newBuffer)
{
    this->bufferPix = newBuffer;
}

///////////
// Getter /
///////////

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

string Image::getFileName() const
{
    return this->fileName;
}

size_t Image::getSize() const
{
    return size;
}

uint8_t *Image::getData() const
{
    return data;
}

vector<vector<int>> Image::getPix() const
{
    return bufferPix;
}

////////////
// Methode /
////////////

void Image::print(string fname)
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

void Image::castToGrey()
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

Image Image::merge(Image img)
{
    Image res = Image(*this);
    for (int i = 0; i < size; i++)
        data[i] += data[i];
    return res;
}

void Image::resize(int w, int h)
{
    stbir_resize(data, width, height, 0, data, w, h, 0,
                 STBIR_TYPE_UINT8, channels,
                 STBIR_ALPHA_CHANNEL_NONE, 0,
                 STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP,
                 STBIR_FILTER_BOX, STBIR_FILTER_BOX,
                 STBIR_COLORSPACE_SRGB, nullptr);
    setHeight(h);
    setWidth(w);
}

Image Image::crop(int top, int left, int bottom, int right)
{
    Image res = Image(*this);
    // algo de crop sur image copier
    return res;
}