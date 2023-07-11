#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include "Utils.h"
#include "Vec3.h"

class Camera
{
  public:
    Camera() {
      const double aspectRatio = 16.0/9.0;

      // x points left/right, y points up/down, z points in/out.
      double viewportHeight = 2.0;
      double viewportWidth = viewportHeight * aspectRatio;
      double focalLength = 1.0;

      cameraOrigin = Point3(0,0,0);
      horizontalAxis = Vec3(viewportWidth, 0, 0);
      verticalAxis = Vec3(0, viewportHeight, 0);
      lowerLeftCorner = cameraOrigin - horizontalAxis/2 - verticalAxis/2 - Vec3(0, 0, focalLength);
    }

    Ray GetRay(double u, double v) const
    {
      return Ray(cameraOrigin, lowerLeftCorner + u*horizontalAxis + v*verticalAxis - cameraOrigin);
    }

  private:
    Point3 cameraOrigin;
    Point3 lowerLeftCorner;
    Vec3 horizontalAxis;
    Vec3 verticalAxis;
};

#endif