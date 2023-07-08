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

    virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& record) const override;

    std::vector<shared_ptr<Hittable>> hittableObjects;
};
#endif