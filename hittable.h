#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class HitRecord
{
  public:
    Point3 hitPoint;
    Vec3 normal;
    double t;
    bool frontFace;  // True if the ray is hitting the outer face of the sphere, false if ray is "inside" sphere and hitting the inner face.

    void SetFaceAndNormal(const Ray& r, const Vec3& outwardNormal)
    {
      // If dot product is positive, they are in the same direction.
      // Thus, ray points outwards and thus ray is inside the sphere pointing to the outside.
      frontFace = !(Dot(r.GetDirection(), outwardNormal) > 0);

      // The idea is that we want the normal to point opposite the ray's direction.
      // frontFace tells us where the ray is pointing, and thus we can adjust normal accordingly.
      normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
  public:
    virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const = 0;
};

#endif