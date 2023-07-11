#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable
{
  public:
    HittableList() {}
    HittableList(shared_ptr<Hittable> hittableObject) { Add(hittableObject); }

    void Clear() { hittableObjects.clear(); }
    void Add(shared_ptr<Hittable> hittableObject) { hittableObjects.push_back(hittableObject); }

    bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const override;

    std::vector<shared_ptr<Hittable>> hittableObjects;
};

// The reason why I have implementations here and not in a .cpp file is because it's tedious 
// to keep updating the tasks.json file for the build task to include cpp files.
// If these files are not included in tasks.json, they will not be picked up.
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
#endif