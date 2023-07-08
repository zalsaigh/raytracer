#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable
{
  public:
    Sphere() {}
    Sphere(Point3& center, double r) : center(center), radius(r) {};

    virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const override;

    Point3 center;
    double radius;
};

#endif