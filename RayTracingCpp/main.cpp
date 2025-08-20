#include "camera.h"
#include "vec3.h"
#include <iostream>

int main()
{
    Camera camera;

    camera.imageWidth = 1920;
    camera.aspectRatio = 16.0 / 9.0;
    camera.hFov = 90;
    camera.focalLength = 1.0;
    camera.lookAt = vec3{0, 0, 1};
    camera.position = vec3{0, 0, 0};
    camera.up = vec3{0, 1, 0};

    camera.renderScene();

    return 0;
}