#include <string>
#include <vector>
#include "image.hpp"

using namespace std;

enum options
{
    VERBOSE = 0,
    FADING = 1,
    OVERLAP = 2,
    STEP = 3,
    DISTANCE = 4
};

int main(int argc, char *argv[])
{
    string directory, optionProgram;
    vector<Image> mesImages;
    vector<Image> mesMasques;
    directory = "img/";

    for (int i = 0; i < 9; i++)
    {
        string src = directory + to_string(i) + ".jpg";
        mesImages.push_back(Image(src));
    }

    Image background = Image::getBackgroundMask(mesImages);

    for (int i = 0; i < 9; i++)
        mesMasques.push_back(mesImages[i].getImageMask(background, 15));

    Image composition = Image::composition(mesMasques, background);
    composition.print("composition.jpg");

    return 0;
}
