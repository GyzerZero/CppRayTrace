#include "camera.h"
#include "color.h"

void Camera::initialize()
{
    imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    viewportWidth = 2 * focalLength * std::tan(hFov / 2); // Set because of isosceles triangle with base viewport width, hieght focal length, and angle hfov
    viewportHeight = viewportWidth / aspectRatio;

    w = lookAt.normalize();
    u = cross(w, up).normalize();
    v = cross(u, w);

    viewportU = vec3{viewportWidth, 0, 0};
    viewportV = vec3{0, -viewportHeight, 0};

    pixelDeltaU = viewportU / imageWidth;
    pixelDeltaV = viewportV / imageHeight;

    viewportUpperLeft = position - vec3{0, 0, focalLength} - viewportU / 2 - viewportV / 2;
    pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
}

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