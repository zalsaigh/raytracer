#include <iostream>
#include "colour.h"
#include "vec3.h"

int main() 
{
    const std::string imgFormat = "P3";
    const int imgHeight = 256;
    const int imgWidth = 256;
    const int maxValueForColorChannel = 255;

    std::cout << imgFormat << "\n";
    std::cout << imgHeight << " " << imgWidth << "\n";
    std::cout << maxValueForColorChannel << "\n";

    for (int i = 0; i < imgHeight; i++) {
        std::cerr << "\rScanlines remaining: " << imgHeight - i << " " << std::flush;
        for (int j = 0; j < imgWidth; j++) {
            colour pixel_colour(static_cast<double>(i)/(imgHeight - 1), static_cast<double>(j) / (imgWidth - 1), 0.25);
            write_colour(std::cout, pixel_colour);
        }
    }

    std::cerr << "\nDone\n";
}



