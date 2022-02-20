#include "pixel.hpp"

Pixel::Pixel() : posX(0), posY(0), color(Color()) {}

Pixel::~Pixel() {}

Pixel::Pixel(const Pixel &newPixel) : posX(newPixel.posX), posY(newPixel.posY), color(newPixel.color) {}

Pixel::Pixel(unsigned int x, unsigned int y, Color color) : posX(x), posY(y), color(color) {}

void Pixel::setPixel(unsigned int x, unsigned int y)
{
    posX = x;
    posY = y;
}

void Pixel::setColor(const Color newColor)
{
    color = newColor;
}