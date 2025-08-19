#pragma once

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

struct ray
{
    vec3 origin;
    vec3 direction;

    vec3 at(double t) const
    {
        return origin + direction * t;
    }
};

#endif