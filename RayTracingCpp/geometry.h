#pragma once

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "ray.h"
#include "vec3.h"
#include <cstdbool>

struct triangle
{
    vec3 vertexA, vertexB, vertexC;

    // Möller–Trumbore method
    bool intersect(ray r) const
    {
        vec3 edge1 = vertexB - vertexA;
        vec3 edge2 = vertexC - vertexA;

        vec3 h = cross(r.direction, edge2);

        double determinant = dot(edge1, h);
        double invdet = 1 / determinant;

        vec3 s = r.origin - vertexA;

        double beta = dot(s, h) * invdet;

        vec3 q = cross(s, edge1);

        double gamma = dot(r.direction, q) * invdet;

        double t = dot(edge2, q) * invdet;

        if (beta < 0 or beta > 1)
            return false;

        else if (gamma < 0 or beta + gamma > 1)
            return false;

        else if (t < 0)
            return false;

        else
            return true;
    }
};

#endif