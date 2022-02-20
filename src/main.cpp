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
        diretory = "img/";
        imgOutput = "default.jpg";
        optionProgram = "";
    }

    // load mes 9 image de img/
    for (int i = 0; i < 9; i++)
    {
        string src = diretory + to_string(i) + ".jpg";
        mesImage.push_back(Image(src));
        //cout << mesImage[i].getPix().size() << endl;
    }

    return 0;
}
