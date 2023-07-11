#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>


// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double Clamp(double x, double min, double max)
{
    if (x < min)
    {
        return min;
    }
    if (x > max)
    {
        return max;
    }
    return x;
}
inline double DegreesToRadians(double degrees) {
    return degrees * pi / 180.0;
}

inline double RandomDouble0To1()
{
    // Returns a random double in [0,1)
    return rand() / (RAND_MAX + 1);
}

inline double RandomDouble(double min, double max)
{
    // Returns a random double in [min, max)
    return min + (max - min) * RandomDouble0To1();

}

#endif