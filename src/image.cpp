#include <algorithm>
#include "image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>

using namespace std;

/////////////////
// Constructeur /
/////////////////

Image::Image()
{
    this->width = 0;
    this->height = 0;
    this->channels = 0;
    this->fileName = "default.jpg";
    this->size = 0;
    this->data = 0;
    this->bufferPix = new Pixel[0];
}

Image::Image(const Image &cpy) : width(cpy.getWidth()), height(cpy.getHeight()), channels(cpy.getChannels()), data(cpy.getData()), size(cpy.getSize()), fileName(cpy.getFileName())
{
    bufferPix = new Pixel[cpy.width * cpy.height];
    for (int i = 0; i < cpy.width * cpy.height; i++)
    {
        bufferPix[i] = cpy.bufferPix[i];
    }
}

Image::Image(int w, int h)
{
    this->width = w;
    this->height = h;
    this->channels = 3;
    this->fileName = "default.jpg";
    this->size = w * h * 3;
    this->data = 0;
    this->bufferPix;
}

Image::Image(string src)
{
    data = stbi_load(src.c_str(), &width, &height, &channels, 0);
    if (data != nullptr)
    {
        size = (width * height) * channels;
        bufferPix = new Pixel[width * height];
        for (int i = 0; i < width * height; i++)
        {
            bufferPix[i].setPixel(*(data + i * 3), *(data + i * 3 + 1), *(data + i * 3 + 2));
        }
    }
    else
    {
        this->width = 0;
        this->height = 0;
        this->channels = 0;
        this->fileName = "default.jpg";
        this->data = 0;
        this->size = 0;
        this->bufferPix;
    }
}

///////////
// Setter /
///////////

void Image::setData(uint8_t *data)
{
    this->data = data;
}

void Image::saveToData()
{
    for (int i = 0; i < width * height; i++)
    {
        *(data + i * 3) = (unsigned int)bufferPix[i].r;
        *(data + i * 3 + 1) = (unsigned int)bufferPix[i].g;
        *(data + i * 3 + 2) = (unsigned int)bufferPix[i].b;
    }
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

void Image::setBufferPix(Pixel *newBuffer)
{

    int s = (sizeof(newBuffer) / sizeof(*newBuffer));
    delete[] bufferPix;
    Pixel *bufferPix = new Pixel[size];
    for (int i = 0; i < size; i++)
    {
        bufferPix[i] = newBuffer[i];
    }

    saveToData();
}

void Image::setPixel(int x, int y, Pixel p)
{

    bufferPix[x + y * width] = p;
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

Pixel *Image::getBufferPix() const
{

    return bufferPix;
}

////////////
// Methode /
////////////

void Image::print(string fname)
{
    saveToData();
    stbi_write_jpg(fname.c_str(), width, height, channels, data, width * channels);
}

// On libère les ressources d'un image
Image::~Image()
{
    if (data != nullptr)
    {
        stbi_image_free(data);
        data = nullptr;
        width = 0;
        height = 0;
        channels = 0;
        size = 0;
        delete[] bufferPix;
    }
}

// Renvoie l'image tout en gris, on conserve le channel 3
void Image::castToGrey()
{
    if (channels < 3)
        printf("Image déjà en niveau de gris\n");
    else
    {
        for (int i = 0; i < width * height; i++)
        {
            // On fait la moyenne de la couleur de nos pixels puis on divise par 3 pour obtenir le niv de gris
            int gray = bufferPix[i].grey();
            bufferPix[i].r = gray;
            bufferPix[i].g = gray;
            bufferPix[i].b = gray;
        }
    }
}

// Resize l'image à la bonne taille
Image Image::resize(int w, int h)
{
    Image res = Image(w, h);
    res.setBufferPix(this->getBufferPix());
    float sx = width / w;
    float sy = height / h;

    for (int x = 0; x < this->width; x++)
    {
        for (int y = 0; y < this->height; y++)
            res.bufferPix[x + y * width] = this->bufferPix[(int)(x * sx + y * sy)];
    }
    return res;
}

// Retourne une Crop l'image pour correspondre à la bonne taille
Image Image::crop(int top, int left, int nwidth, int nheight)
{
    Image res = Image(*this);
    res.width = nwidth;
    res.height = nheight;
    res.size = nwidth * nheight * channels;
    Pixel *newbuffer = new Pixel[nwidth * nheight];

    for (int x = left; x < nwidth; x++)
    {
        for (int y = top; y < nheight; y++)
            newbuffer[x + y * nwidth] = bufferPix[x + y * width];
    }

    delete[] res.bufferPix;
    res.bufferPix = newbuffer;
    return res;
}

// Renvoie le masque de l'image courrante comparé au background
Image Image::getImageMask(Image background, int threshold) const
{
    Image res = Image(background);
    int w = background.getWidth();
    int h = background.getHeight();
    Pixel *tmp = background.getBufferPix();

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            if (abs(bufferPix[x + y * w].grey() - tmp[x + y * w].grey()) < threshold)
                res.bufferPix[x + y * width] = Pixel(0, 0, 0);
            else
                res.bufferPix[x + y * width] = bufferPix[x + y * width];
        }
    }
    return res;
}

// Renvoie le background des images données
Image Image::getBackgroundMask(vector<Image> tabIm)
{
    Image res = Image(tabIm[0]);
    int l = tabIm.size();
    int med = l / 2;
    int w = tabIm[0].getWidth();
    int h = tabIm[0].getHeight();

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            int r[l];
            int g[l];
            int b[l];

            for (int i = 0; i < l; i++)
            {
                r[i] = tabIm[i].getBufferPix()[x + y * w].r;
                g[i] = tabIm[i].getBufferPix()[x + y * w].g;
                b[i] = tabIm[i].getBufferPix()[x + y * w].b;
            }

            sort(r, r + l);
            sort(g, g + l);
            sort(b, b + l);
            res.setPixel(x, y, Pixel(r[med], g[med], b[med]));
        }
    }
    return res;
}

// Fait la composition finale avec les masques et le background
Image Image::composition(vector<Image> tabMask, Image back)
{
    Image res = Image(back);

    int w = back.getWidth();
    int h = back.getHeight();
    int l = tabMask.size();
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            for (int i = 0; i < l; i++)
            {
                if (tabMask[i].getBufferPix()[x + y * w].grey() != 0)
                    res.bufferPix[x + y * w] = tabMask[i].getBufferPix()[x + y * w];
            }
        }
    }
    return res;
}