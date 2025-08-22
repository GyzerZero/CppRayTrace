#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "camera.h"
#include "color.h"
#include "geometry.h"

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

    triangle t1 = {vec3{0.5, 0.5, -1},
                   vec3{0.5, -0.5, -1},
                   vec3{0, -0.5, -1}};

    TriangleMesh m1 = {{&t1}, 1};

    for (int j = 0; j < imageHeight; j++)
    {
        std::cout << "Scanlines Remaining: " << imageHeight - j << " / " << imageHeight << "                \r";

        for (int i = 0; i < imageWidth; i++)
        {
            ray currentRay = getRay(i, j);
            vec3 pixelColor = rayColor(currentRay, m1);

            int index = (j * imageWidth + i) * 3;
            write_color(pixelColor, pixelBuffer, index);
        }
    }

    stbi_write_png("image.png", imageWidth, imageHeight, 3, pixelBuffer.data(), imageWidth * 3);

    std::cout << "Done.                                " << std::endl;
};

vec3 Camera::rayColor(ray r, TriangleMesh m1)
{
    double t = testRay(r, m1);
    if (t > 0.0)
        return vec3{1, 0, 0};
    else
        return vec3{0, 0, 0};
}