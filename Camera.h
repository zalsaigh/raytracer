#ifndef CAMERA_H
#define CAMERA_H

#include "Utils.h"
#include "Hittable.h"
#include "Colour.h"
#include "Material.h"

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

      // See https://raytracing.github.io/images/fig-1.18-cam-view-geom.jpg
      double mVerticalFOV = 90; // Vertical view angle (centered around the z-axis at z = focalLength). On either side of z-axis is h units, with h = tan(mVerticalFOV/2) assuming focalLength = 1
      // This is the viewing angle from edge to edge of the viewport (vertically, so the horizontal edges on top and bottom of viewport)
      Point3 mLookFrom = Point3(0, 0, -1);  // Point camera is looking from
      Point3 mLookAt = Point3(0, 0, 0);  // Point camera is looking at
      Vec3 mVecUp = Vec3(0, 1, 0);  // Camera-relative "up" direction
      

    void Render(const Hittable& world)
    {
      Initialize();

      // Render
      std::cout << mImgFormat << "\n";
      std::cout << mImgWidth << " " << mImgHeight << "\n";
      std::cout << mMaxValueForColorChannel << "\n";

      for (int j = 0; j < mImgHeight; ++j) {
        std::cerr << "\rScanlines remaining: " << mImgHeight - j << ' ' << std::flush;
        for (int i = 0; i < mImgWidth; ++i) {
            Colour pixelColour(0,0,0);
            for (int sample = 0; sample < mSamplesPerPixel; ++sample)
            {
                Ray r = GetRayToShoot(i, j);
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
    Vec3 mPixel00Location;  // Center of the upper left pixel
    Vec3 mPixelHorizontalSpacing; // The horizontal and vertical delta vectors from pixel to pixel
    Vec3 mPixelVerticalSpacing;
    Vec3 mBasisU, mBasisV, mBasisW;  // Camera frame unit basis vectors. U points to camera's right, V points to camera's up, and W points opposite the view direction.

    void Initialize()
    {
      mImgHeight = static_cast<int>(mImgWidth / mAspectRatio);
      mImgHeight = (mImgHeight < 1) ? 1 : mImgHeight;

      mCameraOrigin = mLookFrom;

      // Viewport dimensions. Viewport is the rectangle that defines our pixels through which we send rays into the scene.
      double focalLength = (mLookFrom - mLookAt).Length(); // Distance from camera to viewport in z-axis
      double theta = DegreesToRadians(mVerticalFOV);
      double heightAboveZAxis = tan(theta/2);
      double viewportHeight = 2 * heightAboveZAxis * focalLength;
      double viewportWidth = viewportHeight * (static_cast<double>(mImgWidth) / mImgHeight);  // We re-do division here to calculate aspect ratio because of rounding errors with C++.

      mBasisW = UnitVector(mLookFrom - mLookAt);
      mBasisU = UnitVector(Cross(mVecUp, mBasisW));  // Recall that cross product produces a vector orthogonal to both inputs
      mBasisV = Cross(mBasisW, mBasisU);

      // Both edges are defined so that the upper left corner is where they originate from
      Vec3 viewportHorizontalEdge = viewportWidth * mBasisU;
      Vec3 viewportVerticalEdge = viewportHeight * -mBasisV;

      mPixelHorizontalSpacing = viewportHorizontalEdge / mImgWidth;
      mPixelVerticalSpacing = viewportVerticalEdge / mImgHeight;

      // First subtraction gets us from camera origin to the center of the viewport (remember that mBasisW is positive in the opposite direction). The other two get us to upper left.
      Vec3 viewportUpperLeftCorner = mCameraOrigin - (focalLength * mBasisW) - viewportHorizontalEdge/2 - viewportVerticalEdge/2;
      mPixel00Location = viewportUpperLeftCorner + (mPixelHorizontalSpacing + mPixelVerticalSpacing)/2;
    }

    Ray GetRayToShoot(int i, int j) const
    {
       Point3 pixelCenter = mPixel00Location + (i * mPixelHorizontalSpacing) + (j * mPixelVerticalSpacing);
       Point3 pixelSample = pixelCenter + GetRandomPixelOffset();

       Vec3 rayDirection = pixelSample - mCameraOrigin;

       return Ray(mCameraOrigin, rayDirection);
    }

    Vec3 GetRandomPixelOffset() const 
    {
      // Gets offsets from -0.5 to 0.5, which assumes we are at pixel center. We scale -0.5 to 0.5 by the actual spacing (dimensions of each pixel).
      double horizontalOffset = -0.5 + RandomDouble0To1();
      double verticalOffset = -0.5 + RandomDouble0To1();
      return (horizontalOffset * mPixelHorizontalSpacing) + (verticalOffset * mPixelVerticalSpacing);
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
          Ray scattered;
          Colour attenuation;
          if (rec.material->Scatter(r, rec, attenuation, scattered))
          {
            return attenuation * RayColour(scattered, world, recursiveDepthLimit - 1);
          }
          // If scattering doesn't happen, that means the ray is absorbed. Return black.
          return Colour(0,0,0);
      }
      Vec3 unitDirection = UnitVector(r.GetDirection());
      double t = 0.5*(unitDirection.Y() + 1.0);
      return (1.0-t)*Colour(1.0, 1.0, 1.0) + t*Colour(0.5, 0.7, 1.0);
    }
};

#endif