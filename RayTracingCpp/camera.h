#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "stbi_image_write.h"

#include <cmath>
#include <iostream>
#include <vector>
#include <cstdint>

class Camera {
public:

	int imageWidth;
	double aspectRatio;
	double hFov;        // horizontal field-of-view
	double focalLength; // distance between camera eye and viewport
	vec3 lookAt; // Camera look-at point
	vec3 position; // Camera position
	vec3 up;

	void renderScene() {
		initialize();

		std::vector<uint8_t> pixelBuffer(imageWidth * imageHeight * 3);

		std::cout << "Starting Render" << std::endl;

		for (int j = 0; j < imageHeight; j++) {
			std::cout << "Scanlines Remaining: " << imageHeight - j << " / " << imageHeight << "                \r";

			for (int i = 0; i < imageWidth; i++) {
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

	void initialize() {
		imageHeight = int(imageWidth / aspectRatio);
		imageHeight = (imageHeight < 1) ? 1 : imageHeight;

		viewportWidth = 2 * focalLength * std::tan(hFov / 2); // Set because of isosceles triangle with base viewport width, hieght focal length, and angle hfov
		viewportHeight = viewportWidth / aspectRatio;

		w = lookAt.normalize();
		u = cross(w, up).normalize();
		v = cross(u, w);

		viewportU = vec3{ viewportWidth, 0, 0 };
		viewportV = vec3{ 0, -viewportHeight, 0 };

		pixelDeltaU = viewportU / imageWidth;
		pixelDeltaV = viewportV / imageHeight;

		viewportUpperLeft = position - vec3{ 0, 0, focalLength } - viewportU / 2 - viewportV / 2;
		pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
	}
};

#endif