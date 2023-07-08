#include "HittableList.h"

bool HittableList::Hit(const Ray& r, double tMin, double tMax, HitRecord& outRecord) const
{
    HitRecord currentRecord;

    bool hitAnything = false;
    double closestSoFar = tMax;

    for (const auto& hittableObject : hittableObjects)
    {
      if (hittableObject->Hit(r, tMin, tMax, currentRecord))
      {
        hitAnything = true;
        closestSoFar = currentRecord.t;
        outRecord = currentRecord;
      }
    }

    return hitAnything;
}