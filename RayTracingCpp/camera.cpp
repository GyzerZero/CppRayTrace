#include "camera.h"

void Camera::renderScene()
{
    initialize();

    std::vector<uint8_t> pixelBuffer(imageWidth * imageHeight * 3);

    std::cout << "Starting Render" << std::endl;

    for (int j = 0; j < imageHeight; j++)
    {
        std::cout << "Scanlines Remaining: " << imageHeight - j << " / " << imageHeight << "                \r";

        for (int i = 0; i < imageWidth; i++)
        {
            auto r = double(i) / (imageWidth - 1);
            auto g = double(j) / (imageHeight - 1);
            auto b = 0.0;

            uint8_t ir = uint8_t(255.999 * r);
            uint8_t ig = uint8_t(255.999 * g);
            uint8_t ib = uint8_t(255.999 * b);

            int index = (j * imageWidth + i) * 3;
            pixelBuffer[index + 0] = ir;
            pixelBuffer[index + 1] = ig;
            pixelBuffer[index + 2] = ib;
        }
    }

    stbi_write_png("image.png", imageWidth, imageHeight, 3, pixelBuffer.data(), imageWidth * 3);
};