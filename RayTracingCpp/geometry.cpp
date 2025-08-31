#include "geometry.h"

double intersect(ray &r, triangle &t)
{
    vec3 h = cross(r.direction, t.edge2);

    double determinant = dot(t.edge1, h);
    double invdet = 1 / determinant;

    vec3 s = r.origin - t.vertexA;

    double beta = dot(s, h) * invdet;

    vec3 q = cross(s, t.edge1);

    double gamma = dot(r.direction, q) * invdet;

    double intersection = dot(t.edge2, q) * invdet;

    if (beta < 0 || beta > 1)
        return -1.0;
    else if (gamma < 0 || beta + gamma > 1)
        return -1.0;
    else if (intersection < 0)
        return -1.0;
    else
        return intersection;
}