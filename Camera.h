#ifndef CAMERA_H
#define CAMERA_H

#include "Utils.h"
#include "Hittable.h"
#include "Colour.h"

#include <iostream>

class Camera
{
  public:
      double mAspectRatio = 16.0/9.0;
      int mImgWidth = 400;
      std::string mImgFormat = "P3";
      int mMaxValueForColorChannel = 255;
      int mSamplesPerPixel = 100;
      int mMaxRayColourRecursiveDepth = 50;

    void Render(const Hittable& world)
    {
      Initialize();

      // Render
      std::cout << mImgFormat << "\n";
      std::cout << mImgWidth << " " << mImgHeight << "\n";
      std::cout << mMaxValueForColorChannel << "\n";

      for (int j = mImgHeight-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < mImgWidth; ++i) {
            Colour pixelColour(0,0,0);
            for (int sample = 0; sample < mSamplesPerPixel; ++sample)
            {
                auto u = (i + RandomDouble0To1()) / (mImgWidth-1);
                auto v = (j + RandomDouble0To1()) / (mImgHeight-1);
                Ray r = GetRay(u, v);
                pixelColour += RayColour(r, world, mMaxRayColourRecursiveDepth);
            }
            WriteColour(std::cout, pixelColour, mSamplesPerPixel);
        }
      }
      std::cerr << "\nDone\n";
    }

  private:
    int mImgHeight;
    Point3 mCameraOrigin;
    Point3 mLowerLeftCorner;
    Vec3 mHorizontalAxis;
    Vec3 mVerticalAxis;

    void Initialize()
    {
      mImgHeight = static_cast<int>(mImgWidth / mAspectRatio);
      mImgHeight = (mImgHeight < 1) ? 1 : mImgHeight;

      mCameraOrigin = Point3(0,0,0);

      // x points left/right, y points up/down, z points in/out.
      double viewportHeight = 2.0;
      double viewportWidth = viewportHeight * (static_cast<double>(mImgWidth) / mImgHeight);  // We re-do division here to calculate aspect ratio because of rounding errors with C++.
      double focalLength = 1.0;

      mHorizontalAxis = Vec3(viewportWidth, 0, 0);
      mVerticalAxis = Vec3(0, viewportHeight, 0);
      mLowerLeftCorner = mCameraOrigin - mHorizontalAxis/2 - mVerticalAxis/2 - Vec3(0, 0, focalLength);
    }

    Ray GetRay(double u, double v) const
    {
      return Ray(mCameraOrigin, mLowerLeftCorner + u*mHorizontalAxis + v*mVerticalAxis - mCameraOrigin);
    }

    Colour RayColour(const Ray& r, const Hittable& world, int recursiveDepthLimit) const
    {
      HitRecord rec;

      // If we've exceeded recursive diffuse light bouncing limit, end here and gather no more light.
      if (recursiveDepthLimit <= 0)
      {
          return Colour(0,0,0);
      }

      if (world.Hit(r, Interval(0.0001, infinity), rec))
      {
          // add randompointinunitsphere to get a point < 1 length away from (hitpoint + normal)
          // UPDATE: RandomPointOnSurfaceOfUnitSphere gives us a better distribution of angles between target and normal (distribution scales by cos(phi) instead of cos^3(phi)) 
          // which means more angles, which means better randomizing. This is known as true lambertian reflection.
          Point3 target = rec.hitPoint + rec.normal + RandomPointOnSurfaceOfUnitSphere();
          return 0.5 * RayColour(Ray(rec.hitPoint, target - rec.hitPoint), world, recursiveDepthLimit - 1);
      }
      Vec3 unitDirection = UnitVector(r.GetDirection());
      double t = 0.5*(unitDirection.Y() + 1.0);
      return (1.0-t)*Colour(1.0, 1.0, 1.0) + t*Colour(0.5, 0.7, 1.0);
    }
};

#endif