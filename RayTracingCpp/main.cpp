#include <iostream>
#include "vec3.h"

int main() {
	vec3 a = { 1, 2, 3 };
	vec3 c = a.normalize();

	std::cout << c.x << " " << c.y << " " << c.z << std::endl;
	std::cout << dot(c, c) << std::endl;

	return 0;
}