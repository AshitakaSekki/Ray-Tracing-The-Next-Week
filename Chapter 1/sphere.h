#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"
#include "material.h"

class sphere :public hitable {
public:
	sphere() {}
	sphere(vec3 cen, float r, material *m) :center(cen), radius(r), mat_ptr(m) {};
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	vec3 center;
	float radius;
	material *mat_ptr;
};

//Formula:t*t*dot(B,B)+2*t*dot(B,A-C)+dot(A-C,A-C)-R*R=0
bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center; //A-C
	float a = dot(r.direction(), r.direction()); //a = dot(B,B)
	float b = dot(oc, r.direction()); //b = 2*dot(A-C,B) trick!: reduce 2*2
	float c = dot(oc, oc) - radius * radius; //c = dot(A-C,A-C)-R*R
	//Formula mathod:at^2+bt+c=0
	//determine if b^2-4ac > 0
	float discriminant = b * b - a*c; //trick!: reduce 2*2
	if (discriminant > 0) {
		//save the minimal root
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp<t_max&&temp>t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp<t_max&&temp>t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}

class moving_sphere :public hitable {
public:
	moving_sphere() {}
	moving_sphere(vec3 cen0, vec3 cen1, float t0, float t1, float r, material *m) :center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(m) {}
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	vec3 center(float time) const;
	vec3 center0, center1;
	float time0, time1;
	float radius;
	material *mat_ptr;
};

vec3 moving_sphere::center(float time) const {
	return center0 + ((time - time0) / (time1 - time0))*(center1 - center0);
}

// replace "center" with "center(r.time())"
bool moving_sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center(r.time()); //A-C
	float a = dot(r.direction(), r.direction()); //a = dot(B,B)
	float b = dot(oc, r.direction()); //b = 2*dot(A-C,B) trick!: reduce 2*2
	float c = dot(oc, oc) - radius * radius; //c = dot(A-C,A-C)-R*R
	//Formula mathod:at^2+bt+c=0
	//determine if b^2-4ac > 0
	float discriminant = b * b - a*c; //trick!: reduce 2*2
	if (discriminant > 0) {
		//save the minimal root
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp<t_max&&temp>t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center(r.time())) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp<t_max&&temp>t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center(r.time())) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}

#endif