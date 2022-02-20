
class Pixel{
    public:
    int r;
    int g;
    int b;

    Pixel();
    Pixel(int nr,int ng, int nb);
    Pixel(const Pixel &p);
    void setPixel(int nr,int ng, int nb);

};