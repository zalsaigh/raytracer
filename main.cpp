#include <iostream>
#include "Camera.h"
#include "Colour.h"
#include "Ray.h"
#include "Vec3.h"
#include "Sphere.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Utils.h"

Colour RayColour(const Ray& r, const Hittable& world) 
{
    HitRecord rec;
    if (world.Hit(r, 0, infinity, rec))
    {
        return 0.5 * (rec.normal + Colour(1,1,1));
    }
    Vec3 unitDirection = UnitVector(r.GetDirection());
    double t = 0.5*(unitDirection.Y() + 1.0);
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
    const int samplesPerPixel = 100;

    // World
    HittableList world;
    // Recall that z is -1 because of the right hand rule: y is vertical, x is horizontal, so z goes towards the camera.
    // Thus, z going away from the camera (i.e. what we see) is negative.
    
    world.Add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));  // This is the "ground", a sphere so large that it serves as earth lol
    world.Add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    
    // Camera - x points left/right, y points up/down, z points in/out.
    Camera camera;

    // Render
    std::cout << imgFormat << "\n";
    std::cout << imgWidth << " " << imgHeight << "\n";
    std::cout << maxValueForColorChannel << "\n";

    for (int j = imgHeight-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imgWidth; ++i) {
            Colour pixelColour(0,0,0);
            for (int sample = 0; sample < samplesPerPixel; ++sample)
            {
                auto u = (i + RandomDouble0To1()) / (imgWidth-1);
                auto v = (j + RandomDouble0To1()) / (imgHeight-1);
                Ray r = camera.GetRay(u, v);
                pixelColour += RayColour(r, world);
            }
            WriteColour(std::cout, pixelColour, samplesPerPixel);
        }
    }

    std::cerr << "\nDone\n";
}



