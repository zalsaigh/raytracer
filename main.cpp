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
    
    // Materials
    auto materialGround = make_shared<Lambertian>(Colour(0.5, 0.5, 0.5));
    // auto materialCenter = make_shared<Lambertian>(Colour(0.1, 0.2, 0.5)); 
    // auto materialLeft = make_shared<Dielectric>(1.5); // 1.5 is the index of refraction for glass.
    // auto materialRight = make_shared<Metal>(Colour(0.8, 0.6, 0.2), 0.0);

    world.Add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, materialGround));  // This is the "ground", a sphere so large that it serves as earth lol
    // world.Add(make_shared<Sphere>(Point3(0, 0, -1), 0.5, materialCenter));
    // world.Add(make_shared<Sphere>(Point3(-1, 0, -1), 0.5, materialLeft));
    // world.Add(make_shared<Sphere>(Point3(-1, 0, -1), -0.4, materialLeft));
    // world.Add(make_shared<Sphere>(Point3(1, 0, -1), 0.5, materialRight));

    for (int i = -11; i < 11; i++)
    {
        for (int j = -11; j < 11; j++)
        {
            double chooseMaterial = RandomDouble0To1();
            Point3 center(i + 0.9 * RandomDouble0To1(), 0.2, j + 0.9 * RandomDouble0To1());

            if ((center - Point3(4, 0.2, 0)).Length() > 0.9)
            {
                shared_ptr<Material> sphereMaterial;

                if (chooseMaterial < 0.8)
                {
                    // Diffuse
                    Colour attenuation = RandomVector() * RandomVector();
                    sphereMaterial = make_shared<Lambertian>(attenuation);
                }
                else if (chooseMaterial < 0.95)
                {
                    // Metal
                    Colour attenuation = RandomVector(0.5, 1);
                    double fuzz = RandomDouble(0, 0.5);
                    sphereMaterial = make_shared<Metal>(attenuation, fuzz);
                } else
                {
                    // Glass
                    sphereMaterial = make_shared<Dielectric>(1.5);
                }
                world.Add(make_shared<Sphere>(center, 0.2, sphereMaterial));
            }
        }
    }

    auto materialLargeSphere1 = make_shared<Dielectric>(1.5);
    world.Add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, materialLargeSphere1));

    auto materialLargeSphere2 = make_shared<Lambertian>(Colour(0.4, 0.2, 0.1));
    world.Add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, materialLargeSphere2));

    auto materialLargeSphere3 = make_shared<Metal>(Colour(0.7, 0.6, 0.5), 0.0);
    world.Add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, materialLargeSphere3));

    // Camera - x points left/right, y points up/down, z points in/out.
    // Recall that z is -1 because of the right hand rule: y is vertical, x is horizontal, so z goes towards the camera.
    // Thus, z going away from the camera (i.e. what we see) is negative.
    Camera camera;
    camera.mImgWidth = 1200;
    camera.mVerticalFOV = 20;
    camera.mSamplesPerPixel = 10;
    camera.mLookFrom = Point3(13, 2, 3);
    camera.mLookAt = Point3(0, 0, 0);
    camera.mVecUp = Vec3(0, 1, 0);

    camera.Render(world);
}



