#ifndef VEC3_H
#define VEC3_H

typedef struct {
    double x, y, z;

    vec3 operator+(const vec3 &other) const {
        return vec3{x + other.x, y + other.y, z + other.z};
    }

} vec3;

#endif