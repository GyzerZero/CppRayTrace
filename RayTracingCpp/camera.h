#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "geometry.h"
#include "ray.h"
#include "vec3.h"

#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

class Camera
{
  public:
    int imageWidth;
    double aspectRatio;
    double hFov;        // horizontal field-of-view
    double focalLength; // distance between camera eye and viewport
    vec3 lookAt;        // Camera look-at point
    vec3 position;      // Camera position
    vec3 up;

    void renderScene();

  private:
    int imageHeight;

    double viewportWidth; // viewport_width = 2 * focal_length * tan(fov / 2)
    double viewportHeight;

    // Camera direction (normalized look-at point)
    vec3 direction;

    // Basis vectors

    vec3 w; // forward (same as direction)
    vec3 u; // right
    vec3 v; // true up

    // Vectors across viewport edges

    vec3 viewportU; // horizontal edge
    vec3 viewportV; // vertical edge

    // Distance between pixels from viewport width/height to image width/height

    vec3 pixelDeltaU; // horizontal distance
    vec3 pixelDeltaV; // vertical distance

    // Upper-left pixel coordinate (first pixel)

    vec3 viewportUpperLeft; // world-space coordinate on the viewport (edge)
    vec3 pixel00Location;   // world-space center location of the first pixel when i=0, j=0

    void initialize();

    inline ray getRay(int i, int j)
    {
        vec3 pixelCenter = pixel00Location + (i * pixelDeltaU) + (j * pixelDeltaV);
        vec3 rayDirection = pixelCenter - position;
        return ray{pixelCenter, rayDirection};
    }

    vec3 rayColor(ray r, TriangleMesh m1);
};

#endif