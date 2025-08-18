#include <iostream>
#include "vec3.h"

int main() {
    vec3 a = {1, 2, 3};
    vec3 b = {2, 3, 4};
    vec3 c = a + b;

    std::cout << c.x << " " << c.y << " " << c.z << std::endl;

    return 0;
}