#include "image.hpp"
#include <string>
#include <vector>

using namespace std;

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
        diretory = "/";
        imgOutput = "default.jpg";
        optionProgram = "";
    }

    string src = diretory + to_string(0) + ".jpg";
    Image uneImage = Image(src);

    return 0;
}
