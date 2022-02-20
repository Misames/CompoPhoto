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
    bufferPix = new Pixel[cpy.width*cpy.height];
    for (int i = 0; i<cpy.width*cpy.height;i++){
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
    cout<<src<<endl;
    data = stbi_load(src.c_str(), &width, &height, &channels, 0);
    if (data != nullptr)
    {
        size = (width * height) * channels;
        bufferPix = new Pixel[width*height];
        for(int i = 0; i<width*height; i++){
            bufferPix[i].setPixel(*(data+i*3),*(data+i*3+1),*(data+i*3+2));
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
    for(int i = 0;i< width*height;i++){
        *(data+i*3) = (unsigned int) bufferPix[i].r;
        *(data+i*3 + 1) = (unsigned int) bufferPix[i].g;
        *(data+i*3 + 2) = (unsigned int) bufferPix[i].b;
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

void Image::setBufferPix(Pixel* newBuffer)
{

    int s = (sizeof(newBuffer)/sizeof(*newBuffer));
    delete [] bufferPix;
    Pixel* bufferPix = new Pixel[size];
    for (int i = 0;i<size;i++){
        bufferPix[i] = newBuffer[i];
    }
        
    saveToData();
    
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

Pixel* Image::getPix() const
{

    return bufferPix;
}

////////////
// Methode /
////////////

void Image::print(string fname)
{
    saveToData();
    stbi_write_jpg(fname.c_str(), width, height, channels, data , width * channels);
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
        delete [] bufferPix;
    }
}

void Image::castToGrey()
{
    if (channels < 3)
        printf("Image déjà en niveau de gris\n");
    else
    {
        for (int i = 0; i < width*height; i++)
        {
            // On fait la moyenne de la couleur de nos pixels puis on divise par 3 pour obtenir le niv de gris
            int gray = (bufferPix[i].r + bufferPix[i].g + bufferPix[i].b) / 3;
            bufferPix[i].r = gray;
            bufferPix[i].g = gray;
            bufferPix[i].b = gray;
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

Image Image::resize(int w, int h)
{
    Image res = Image(w, h);
    res.setBufferPix(this->getPix());				 					 	   	  

    float sx = width/w;					 					 	   	  
    float sy = height/h;				 					 	   	  
    for (int x = 0; x < this->width; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            res.bufferPix[x + y * width] = this->bufferPix[(int)(x * sx + y * sy)];
        }
    }

    return res;
}

Image Image::crop(int top, int left, int bottom, int right)
{
    Image res = Image(*this);
    // algo de crop sur image copier
    return res;
}