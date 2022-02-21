#include "image.hpp"
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    string directory, optionProgram;

    vector<Image> mesImages;
    vector<Image> mesMasques;

    directory = "img/";

    // load mes 9 image de img/
    for (int i = 0; i < 9; i++)
    {
        string src = directory + to_string(i) + ".jpg";
        mesImages.push_back(Image(src));
    }

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
