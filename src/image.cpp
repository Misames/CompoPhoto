#include "image.hpp"

using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>

Image::~Image()
{
    if (data != nullptr)
        stbi_image_free(data);
    bufferPix.clear();
}

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

void Image::resize(int w, int h)
{
    auto *odata = (unsigned char *)malloc(w * h * channels);
    stbir_resize(this->data, this->width, this->height, 0, odata, w, h, 0,
                 STBIR_TYPE_UINT8, channels,
                 STBIR_ALPHA_CHANNEL_NONE, 0,
                 STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP,
                 STBIR_FILTER_BOX, STBIR_FILTER_BOX,
                 STBIR_COLORSPACE_SRGB, nullptr);
    setHeight(h);
    setWidth(w);
    setSize(w * h * channels);
    setData(odata);
}

Image Image::merge(Image img)
{
    Image res = Image(*this);
    for (int i = 0; i < size; i++)
        data[i] += data[i];
    return res;
}

Image Image::crop(int top, int left, int bottom, int right)
{
    Image res = Image(*this);
    // algo de crop sur image copier
    return res;
}

Image Image::createMask(vector<Image> images)
{
    Image res = Image(this->width, this->height);

    for (int i = 0; i < res.width; i += res.channels)
    {
        for (int j = 0; j < res.height; j += res.channels)
        {
            vector<int> Rvec;
            vector<int> Gvec;
            vector<int> Bvec;

            for (int k = 0; k < images.size(); k++)
            {
                Image tmp = images[k];
                int r, g, b;
                r = tmp.data[i + j * tmp.height];
                g = tmp.data[(i + j * tmp.height) + 1];
                b = tmp.data[(i + j * tmp.height) + 2];

                Rvec.push_back(r);
                Gvec.push_back(g);
                Bvec.push_back(b);
            }

            sort(Rvec.begin(), Rvec.end());
            sort(Gvec.begin(), Gvec.end());
            sort(Bvec.begin(), Bvec.end());

            res.data[i + j * res.height] = (int)Rvec[sizeof(Rvec) / 2];
            res.data[(i + j * res.height) + 1] = (int)Gvec[sizeof(Gvec) / 2];
            res.data[(i + j * res.height) + 2] = (int)Bvec[sizeof(Bvec) / 2];
        }
    }
    return res;
}