#include <iostream>
#include "colour.h"
#include "ray.h"
#include "vec3.h"

Colour RayColour(const Ray& r) 
{
    Vec3 unitDirection = UnitVector(r.getDirection());
    double t =  0.5*(unitDirection.y() + 1.0);
    return (1.0-t)*Colour(1.0, 1.0, 1.0) + t*Colour(0.5, 0.7, 1.0);
}

int main() 
{
    // Image
    const std::string imgFormat = "P3";
    const double aspectRatio = 16.0/9.0;
    const int imgWidth = 400;
    const int imgHeight = static_cast<int>(imgWidth/aspectRatio);
    const int maxValueForColorChannel = 255;
    
    // Camera - x points left/right, y points up/down, z points in/out.
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * aspectRatio;
    double focalLength = 1.0;

    Point3 cameraOrigin = Point3(0,0,0);
    Vec3 horizontalAxis = Vec3(viewportWidth, 0, 0);
    Vec3 verticalAxis = Vec3(0, viewportHeight, 0);
    Vec3 lowerLeftCorner = cameraOrigin - horizontalAxis/2 - verticalAxis/2 - Vec3(0, 0, focalLength);

    // Render
    std::cout << imgFormat << "\n";
    std::cout << imgHeight << " " << imgWidth << "\n";
    std::cout << maxValueForColorChannel << "\n";

    for (int j = imgHeight-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imgWidth; ++i) {
            auto u = double(i) / (imgWidth-1);
            auto v = double(j) / (imgHeight-1);
            Ray r(cameraOrigin, lowerLeftCorner + u*horizontalAxis + v*verticalAxis - cameraOrigin);
            Colour pixelColour = RayColour(r);
            WriteColour(std::cout, pixelColour);
        }
    }

    std::cerr << "\nDone\n";
}



