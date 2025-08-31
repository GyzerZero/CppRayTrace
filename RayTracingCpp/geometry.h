#pragma once

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "ray.h"
#include "vec3.h"

struct triangle
{
    vec3 vertexA, vertexB, vertexC;
    vec3 edge1, edge2;
    vec3 normal;

    vec3 color;

    triangle(const vec3 &a, const vec3 &b, const vec3 &c, const vec3 &color)
        : vertexA(a), vertexB(b), vertexC(c),
          edge1(b - a), edge2(c - a),
          normal((cross(edge1, edge2).normalize())), color(color) {}
};

// Möller–Trumbore algotithm
double intersect(ray &r, triangle &t);

struct pointLight
{
    vec3 position;
    double power;
};

struct world
{
    triangle **triangles;
    int triangle_count;

    pointLight light;

    world(triangle **triangles, int triangle_count, pointLight &light) : triangles(triangles), triangle_count(triangle_count), light(light) {}
};

#endif