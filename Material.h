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

class Dielectric: public Material
{
  public:
  // Eta is the index of refraction from Snell's law. Air = 1.0, glass = 1.3 to 1.7, diamond = 2.4.
  // The higher eta is, the ray will be refracted closer to the normal. The lower, the more the ray will be refracted away from the normal and closer to the surface.
    Dielectric(double eta): mEta(eta) {}

    bool Scatter(const Ray& incomingRay, const HitRecord& record, Colour& outAttenuation, Ray& outScattered) const override
    {
      outAttenuation = Colour(1.0, 1.0, 1.0); // attenuation is 1 meaning there is no absorption by glass/dielectric.

      // Air refractive index is 1.0, frontFace means going from air into the dielectric, and by Snell's law, this means etaAir/etaDielectric
      double refractionRatio = record.frontFace ? (1.0/mEta) : mEta; 

      // Unit direction so that cos(theta) is super easy to calculate (Dot product relies on norm, norm of unit vec is 1.)
      Vec3 unitDirection = UnitVector(incomingRay.GetDirection());
      double cosTheta = fmin(Dot(-unitDirection, record.normal), 1.0);
      double sinTheta = sqrt(1.0 - cosTheta * cosTheta); // Trig identity

      // Critical angle: recall that refractionRatio * sinTheta is sinThetaPrime. However, if refractionRatio > 1, then
      // sin theta has to compensate so that the overall sinThetaPrime <= 1 (since -1 <= sin <= 1).
      bool cannotRefract = refractionRatio * sinTheta > 1.0;
      Vec3 finalDirection;

      // Reflectance probability should be randomized to produce an approximation close enough to reality.
      // That is why we do a random double. Sometimes we reflect, sometimes we refract.
      if (cannotRefract || Reflectance(cosTheta, refractionRatio) > RandomDouble0To1())
      {
        finalDirection = Reflect(unitDirection, record.normal);
      } else {
        finalDirection = Refract(unitDirection, record.normal, refractionRatio);
      }
      
      outScattered = Ray(record.hitPoint, finalDirection);
      return true;
    }

    static double Reflectance(double cosTheta, double eta) {
      // Use Schlick's approximation for reflectance: https://en.wikipedia.org/wiki/Schlick%27s_approximation
      auto r0 = (1 - eta) / (1 + eta);
      r0 = r0 * r0;
      return r0 + (1 - r0)*pow((1-cosTheta), 5);
    }

    double mEta; // Index of refraction
};
#endif