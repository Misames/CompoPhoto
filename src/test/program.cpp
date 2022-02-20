#include <vector>
#include <string>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>

using namespace std;

void resize(string srcInputFile, string srcOutFile)
{
    int width, height, channels;
    unsigned char *img = stbi_load(srcInputFile.c_str(), &width, &height, &channels, 0);

    int ow = width / 2;
    int oh = height / 2;
    auto *odata = (unsigned char *)malloc(ow * oh * channels);

    if (img == nullptr)
    {
        cout << "Error in loading the image" << endl;
        exit(1);
    }

    stbir_resize(img, width, height, 0, odata, ow, oh, 0,
                 STBIR_TYPE_UINT8, channels,
                 STBIR_ALPHA_CHANNEL_NONE, 0,
                 STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP,
                 STBIR_FILTER_BOX, STBIR_FILTER_BOX,
                 STBIR_COLORSPACE_SRGB, nullptr);

    stbi_write_png(srcOutFile.c_str(), ow, oh, channels, odata, 0);
    stbi_image_free(img);
    stbi_image_free(odata);
}

void readDirectory(string path)
{
}

void algo(string options[])
{
    // calcul de l’image de fond
    // calcul du masque du sujet pour chaque image
    // choix des images à utiliser dans la composition
    // composition de l’image finale
}

string getValueArg(string arg)
{
    size_t pos = 0;
    string token;
    while ((pos = arg.find('=')) != string::npos)
    {
        token = arg.substr(pos + 1, arg.length());
        arg.erase(0, pos + string("=").length());
    }
    return token;
}

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
    vector<string> options;

    for (size_t i = 1; i < argc; i++)
    {
        string value = getValueArg(argv[i]);
        options.push_back(value);
    }

    string diretory = options[0];
    string imgOutput = options[1];
    int algoOption = atoi(options[2].c_str());

    switch (algoOption)
    {
    case VERBOSE:
        cout << VERBOSE << endl;
        break;
    case FADING:
        cout << FADING << endl;
        break;
    case OVERLAP:
        cout << OVERLAP << endl;
        break;
    case STEP:
        cout << STEP << endl;
        break;
    case DISTANCE:
        cout << DISTANCE << endl;
        break;
    default:
        break;
    }

    return 0;
}
