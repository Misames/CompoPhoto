#include "image.hpp"
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    string diretory, imgOutput, optionProgram;
    vector<Image> mesImages;
    vector<Image> mesMasques;

    if (argc == 3)
    {
        diretory = argv[1];
        imgOutput = argv[2];
        optionProgram = argv[3];
    }
    else
    {
        diretory = "img/";
        imgOutput = "out_put.jpg";
        optionProgram = "";
    }

    // load mes 9 image de img/
    for (int i = 0; i < 9; i++)
    {
        string src = diretory + to_string(i) + ".jpg";
        mesImages.push_back(Image(src));
        //cout << mesImages[i].getBufferPix().size() << endl;
    }

    /*
    Image Lena("lena.jpg");
    Image greyLena(Lena);
    greyLena.castToGrey();
    greyLena.print("grey.jpg");
    */
    Image background = Image::getBackgroundMask(mesImages);
    //background.print("back.jpg");

    for (int i = 0; i < 9; i++)
    {   
        mesMasques.push_back(mesImages[i].getImageMask(background,15));
        //tmp.print("mask" + to_string(i) + ".jpg");
    }

    Image composition = Image::composition(mesMasques,background);
    composition.print("composition.jpg");


    return 0;
}
