#include "sphere.h"

bool Sphere::Hit(const Ray& r, double tMin, double tMax, HitRecord& outRecord) const
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
    if (nearestT < tMin || nearestT > tMax)
    {
        // Falls outside of range
        return false;
    }

    outRecord.t = nearestT;
    outRecord.hitPoint = r.At(nearestT);
    Vec3 outwardNormal = UnitVector(outRecord.hitPoint - center); // Equivalent to (outRecord.hitPoint - center) / radius since radius is the length of that vector.
    outRecord.SetFaceAndNormal(r, outwardNormal);

    return true;
}