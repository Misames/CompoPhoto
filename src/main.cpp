#include "image.hpp"
#include <string>
#include <vector>
#include <filesystem>

using namespace std;
using namespace filesystem;

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
    string diretory, imgOutput, optionProgram;
    vector<Image> mesImage;

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

    for (uint8_t i = 0; i < 9; i++)
    {
        Image img = Image(diretory + to_string(i) + ".jpg");
        img.resize(700, 300);
        img.castToGrey();
        img.print(to_string(i) + imgOutput);
    }

    return 0;
}
