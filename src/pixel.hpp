
// classe pixel pour plus facilement gérer les composants r,g,b
class Pixel{
    public:
    int r;
    int g;
    int b;

    Pixel();
    Pixel(int nr,int ng, int nb);
    Pixel(const Pixel &p);
    void setPixel(int nr,int ng, int nb);
    bool operator==(const Pixel&);
    int grey() const;
};