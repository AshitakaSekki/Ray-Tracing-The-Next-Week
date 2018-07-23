#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray {
public:
	ray() {}
	ray(const vec3& a, const vec3& b, float ti = 0.0) { A = a; B = b; _time = ti; }

	vec3 origin() const { return A; }
	vec3 direction() const { return B; }
	// shutter interval time is basic of motion blur
	float time() const { return _time; }
	vec3 point_at_parameter(float t) const { return A + t * B; }

	vec3 A; //origin
	vec3 B; //diretion
	float _time;
};

#endif