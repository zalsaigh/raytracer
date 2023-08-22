// Sphere eqn is (x - center.x)^2 + (y - center.y)^2 + (z - center.z)^2 = radius^2
// r.GetOrigin() - center gives you a vector that can be used from the center to get to r.
// Eg: center is (1,1,1) and r's origin is (5,4,3). That means using (4,3,2) from center
// gets you to r.
// Dot(r - center, r - center) gives the left hand side of sphere eqn
// To know if r hits sphere, we need to find when Dot(r-center, r-center) = radius^2
// Expand r = A + t*B (where A is origin and B is direction of r) and you get:
// Dot(B, B)*t^2 + 2*Dot(B, A - center)*t + Dot(A - center, A - center) - radius^2 = 0
// t is the unknown that we are solving for (i.e., at what t does the ray hit the sphere?)
// The overall equation is quadratic

// In the function below, a, b, and c are those from the quadratic formula. (a*t^2 + b*t + c)
// If there are two roots, then r hits the sphere at two locations, and b^2 - 4ac > 0
// If there is one root, then r hits the sphere at a tangent, and b^2-4ac = 0
// If there are no roots, r does not hit the sphere, and b^2 - 4ac < 0

#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable
{
  public:
    Sphere() {}
    // center is not a Point3& so we can instantialize shared pointers with rvalues
    Sphere(Point3 center, double r) : center(center), radius(r) {};

    bool Hit(const Ray& r, Interval tInterval, HitRecord& outRecord) const override;

    Point3 center;
    double radius;
};

// The reason why I have implementations here and not in a .cpp file is because it's tedious 
// to keep updating the tasks.json file for the build task to include cpp files.
// If these files are not included in tasks.json, they will not be picked up.
bool Sphere::Hit(const Ray& r, Interval tInterval, HitRecord& outRecord) const
{
    Vec3 oc = r.GetOrigin() - center;
    double a = Dot(r.GetDirection(), r.GetDirection());
    double b = 2 * Dot(oc, r.GetDirection());
    double c = Dot(oc, oc) - radius*radius;
    double discriminant = b*b - 4*a*c;
    if (discriminant < 0)
    {
        // No roots.
        return false;
    }
    // Else, return the smaller of the two roots (the - of +/-) as it is the first hit point of t.
    auto nearestT = (-b - sqrt(discriminant)) / (2.0*a);
    if (!tInterval.Surrounds(nearestT))
    {
        nearestT = (-b + sqrt(discriminant)) / (2.0*a);
        if (!tInterval.Surrounds(nearestT))
        {
            // Falls outside of range
            return false;
        }
    }

    outRecord.t = nearestT;
    outRecord.hitPoint = r.At(nearestT);
    // hitPoint minus sphere center gives a vector that points orthogonally/90 degree angle from the sphere surface.
    Vec3 outwardNormal = UnitVector(outRecord.hitPoint - center); // Equivalent to (outRecord.hitPoint - center) / radius since radius is the length of that vector.
    outRecord.SetFaceAndNormal(r, outwardNormal);

    return true;
}

#endif