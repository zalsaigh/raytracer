#include <iostream>

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
            std::cout << i << " " << j << " 0 \n";
        }
    }

    std::cerr << "\nDone\n";
}



