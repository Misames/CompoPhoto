#include <iostream>
#include <string>
#include <glm.hpp>
#include "../../libs/glm/glm.hpp"
#include "Pixel.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>

using namespace std;
using namespace glm;

int main()
{
    int width, height, channels;
    unsigned char *img = stbi_load("lena.jpg", &width, &height, &channels, 0);

    int ow = width / 2;
    int oh = height / 2;
    auto *odata = (unsigned char *)malloc(ow * oh * channels);

    if (img == nullptr)
    {
        printf("Error in loading the image\n");
        exit(1);
    }

    stbir_resize(img, width, height, 0, odata, ow, oh, 0, STBIR_TYPE_UINT8, channels, STBIR_ALPHA_CHANNEL_NONE, 0,
                 STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP,
                 STBIR_FILTER_BOX, STBIR_FILTER_BOX,
                 STBIR_COLORSPACE_SRGB, nullptr);
    stbi_write_png("output.jpeg", ow, oh, channels, odata, 0);
    stbi_image_free(img);
    stbi_image_free(odata);
    return 0;
}
