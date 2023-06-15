#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray
{
  public:
    Point3 orig;
    Vec3 dir;
    
    Ray() {}
    Ray(const Point3& orig, const Vec3& dir) : orig(orig), dir(dir) {}
    Point3 getOrigin() const { return orig; }
    Vec3 getDirection() const { return dir; }

    Point3 at(double t) const 
    {
      return orig + t*dir;
    }

    
};

#endif