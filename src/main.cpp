#include "image.hpp"

int main(int argc, char *argv[])
{
    Image lena;
    lena.load(&lena, "lena.jpg");
    lena.converToGrey(&lena);
    lena.save(&lena, "lenaGray.jpg");
    lena.free(&lena);
}
