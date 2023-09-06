#include <iostream>
#include "Camera.h"
#include "Colour.h"
#include "Ray.h"
#include "Vec3.h"
#include "Sphere.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Utils.h"
#include "Material.h"

int main() 
{
    // World
    HittableList world;
    
    // Metals
    auto materialGround = make_shared<Lambertian>(Colour(0.8, 0.8, 0.0));
    auto materialCenter = make_shared<Lambertian>(Colour(0.7, 0.3, 0.3));
    auto materialLeft = make_shared<Metal>(Colour(0.8, 0.8, 0.8), 0.3);
    auto materialRight = make_shared<Metal>(Colour(0.8, 0.6, 0.2), 1.0);

    world.Add(make_shared<Sphere>(Point3(0, -100.5, -1), 100, materialGround));  // This is the "ground", a sphere so large that it serves as earth lol
    world.Add(make_shared<Sphere>(Point3(0, 0, -1), 0.5, materialCenter));
    world.Add(make_shared<Sphere>(Point3(-1, 0, -1), 0.5, materialLeft));
    world.Add(make_shared<Sphere>(Point3(1, 0, -1), 0.5, materialRight));
    
    // Camera - x points left/right, y points up/down, z points in/out.
    // Recall that z is -1 because of the right hand rule: y is vertical, x is horizontal, so z goes towards the camera.
    // Thus, z going away from the camera (i.e. what we see) is negative.
    Camera camera;

    camera.Render(world);
}



