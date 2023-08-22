#include <iostream>
#include "Camera.h"
#include "Colour.h"
#include "Ray.h"
#include "Vec3.h"
#include "Sphere.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Utils.h"

int main() 
{
    // World
    HittableList world;
    
    world.Add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));  // This is the "ground", a sphere so large that it serves as earth lol
    world.Add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    
    // Camera - x points left/right, y points up/down, z points in/out.
    // Recall that z is -1 because of the right hand rule: y is vertical, x is horizontal, so z goes towards the camera.
    // Thus, z going away from the camera (i.e. what we see) is negative.
    Camera camera;

    camera.Render(world);
}



