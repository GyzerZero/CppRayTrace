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

    triangle(const vec3 &a, const vec3 &b, const vec3 &c)
        : vertexA(a), vertexB(b), vertexC(c),
          edge1(b - a), edge2(c - a),
          normal((cross(edge1, edge2).normalize())) {}
};

// Möller–Trumbore algotithm
double intersect(ray &r, triangle &t);

struct TriangleMesh
{
    triangle **mesh;
    int triangle_count;

    TriangleMesh(triangle **mesh, int triangle_count) : mesh(mesh), triangle_count(triangle_count) {}
};

#endif