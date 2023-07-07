#include <iostream>
#include "colour.h"
#include "ray.h"
#include "vec3.h"

// Sphere eqn is (x - center.x)^2 + (y - center.y)^2 + (z - center.z)^2 = radius^2
// r.GetOrigin() - center gives you a vector that can be used from the center to get to r.
// Eg: center is (1,1,1) and r's origin is (5,4,3). That means using (4,3,2) from center
// gets you to r.
// Dot(r - center, r - center) gives the left hand side of sphere eqn
// To know if r hits sphere, we need to find when Dot(r-center, r-center) = radius^2
// Expand r = A + t*B (where A is origin and B is direction of r) and you get:
// Dot(B, B)*t^2 + 2*Dot(B, A - center)*t + Dot(A - center, A - center) - radius^2 = 0
// t is the unknown that we are solving for (i.e., at what t does the ray hit the sphere?)
// The overall equation is quadratic

// In the function below, a, b, and c are those from the quadratic formula. (a*t^2 + b*t + c)
// If there are two roots, then r hits the sphere at two locations, and b^2 - 4ac > 0
// If there is one root, then r hits the sphere at a tangent, and b^2-4ac = 0
// If there are no roots, r does not hit the sphere, and b^2 - 4ac < 0

bool HitSphere(const Point3& center, double radius, const Ray& r)
{
    Vec3 oc = r.GetOrigin() - center;
    double a = Dot(r.GetDirection(), r.GetDirection());
    double b = 2 * Dot(oc, r.GetDirection());
    double c = Dot(oc, oc) - radius*radius;
    double discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

Colour RayColour(const Ray& r) 
{
    if (HitSphere(Point3(0,0,-1), 0.5, r))
    {
        return Colour(1,0,0);  // Red.
    }
    // Recall that z is -1 because of the right hand rule: y is vertical, x is horizontal, so z goes into the screen.
    // Thus, z going out of the screen (i.e. what we see) is negative.
    Vec3 unitDirection = UnitVector(r.GetDirection());
    double t =  0.5*(unitDirection.Y() + 1.0);
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
    std::cout << imgWidth << " " << imgHeight << "\n";
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



