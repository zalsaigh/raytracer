#ifndef MATERIAL_H
#define MATERIAL_H

#include "Colour.h"
#include "Hittable.h"
#include "Ray.h"
#include "Utils.h"

class Material
{
  public:
    virtual ~Material() = default;

    virtual bool Scatter(const Ray& incomingRay, const HitRecord& record, Colour& outAttenuation, Ray& outScattered) const = 0;
};

// Recall: Lambertian materials are diffuse, meaning they scatter at many angles (typical of rough surfaces).
class Lambertian : public Material
{
  public:
    Lambertian(const Colour& attenuation) : mAttenuation(attenuation) {}

    // add randompointinunitsphere to get a point < 1 length away from (hitpoint + normal)
    // UPDATE: RandomPointOnSurfaceOfUnitSphere gives us a better distribution of angles between target and normal (distribution scales by cos(phi) instead of cos^3(phi)) 
    // which means more angles, which means better randomizing. This is known as true lambertian reflection.
    bool Scatter(const Ray& incomingRay, const HitRecord& record, Colour& outAttenuation, Ray& outScattered) const override
    {
      auto scatterDirection = record.normal + RandomPointOnSurfaceOfUnitSphere();

      // AKA in case RandomPointOnSurfaceOfUnitSphere is the opposite of the normal
      if (scatterDirection.NearZero())
      {
        scatterDirection = record.normal;
      }
      outScattered = Ray(record.hitPoint, scatterDirection);
      outAttenuation = mAttenuation;
      return true;
    }

    Colour mAttenuation;
};

class Metal: public Material
{
  public:
    Metal(const Colour& attenuation, double fuzz) : mAttenuation(attenuation), mFuzz(fuzz) {}

    bool Scatter(const Ray& incomingRay, const HitRecord& record, Colour& outAttenuation, Ray& outScattered) const override
    {
      auto reflected = Reflect(UnitVector(incomingRay.GetDirection()), record.normal);
      outScattered = Ray(record.hitPoint, reflected + mFuzz*RandomPointOnSurfaceOfUnitSphere());
      outAttenuation = mAttenuation;

      // Because of the fuzz factor, edge case rays that graze the surface of the sphere MIGHT have their fuzz random vector go into the sphere.
      // In that case, we should just absorb the ray, not scatter it (i.e. return false)
      // Recall that Dot(x,y) returns > 0 if the angle between x and y is 0 < angle < 90 (i.e they point in the general same direction).
      return (Dot(outScattered.GetDirection(), record.normal) > 0); 
    }

    Colour mAttenuation;

    // A fuzz of zero means clear mirror reflection because scatter rays are not being fuzzed/manipulated in any way.
    double mFuzz;
};
#endif