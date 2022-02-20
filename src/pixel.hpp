struct Color
{
    unsigned int R, G, B;
    Color() : R(0), G(0), B(0) {}
    Color(unsigned int r, unsigned int g, unsigned int b) : R(r), G(g), B(b) {}
};

class Pixel
{
private:
    unsigned int posX;
    unsigned int posY;
    Color color;

public:
    Pixel();
    ~Pixel();
    Pixel(const Pixel &newPixel);
    Pixel(unsigned int x, unsigned int y, Color colorRGB);

    void setPixel(unsigned int x, unsigned int y);
    void setColor(const Color colorRGB);
};