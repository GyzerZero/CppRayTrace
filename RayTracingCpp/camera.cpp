#include "camera.h"
#include "color.h"

void Camera::renderScene()
{
    std::cout << "Starting Render" << std::endl;

    initialize();

    std::vector<uint8_t> pixelBuffer(imageWidth * imageHeight * 3);

    for (int j = 0; j < imageHeight; j++)
    {
        std::cout << "Scanlines Remaining: " << imageHeight - j << " / " << imageHeight << "                \r";

        for (int i = 0; i < imageWidth; i++)
        {
            auto r = double(i) / (imageWidth - 1);
            auto g = double(j) / (imageHeight - 1);
            auto b = 0.0;

            int index = (j * imageWidth + i) * 3;
            write_color(vec3{r, g, b}, pixelBuffer, index);
        }
    }

    stbi_write_png("image.png", imageWidth, imageHeight, 3, pixelBuffer.data(), imageWidth * 3);

    std::cout << "Done.                                " << std::endl;
};