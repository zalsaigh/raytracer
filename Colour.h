#ifndef COLOUR_H
#define COLOUR_H

#include "Vec3.h"
#include "Interval.h"

#include <iostream>

const double COLOUR_MULT_FACTOR = 255;
using Colour = Vec3;

void WriteColour(std::ostream& out, Colour pixelColour, int samplesPerPixel)
{
    // The sqrt happens for gamma correction. Basically, almost all programs expect an image to be "gamma corrected", but we don't have gamma correction.
    // We are in "linear space" (default space).
    // A good approximation is to square root the channel value. This is because to go from gamma space to linear space (called "Gamma 2"), you square the number.
    // Thus, to go from linear to gamma space, you square root.
    double r = sqrt(pixelColour.X() / samplesPerPixel); 
    double g = sqrt(pixelColour.Y() / samplesPerPixel);
    double b = sqrt(pixelColour.Z() / samplesPerPixel);

    static const Interval intensity(0, 1);
    // Write the translated [0, 255] value of each colour component.
    // Multiply by COLOUR_MULT_FACTOR to get a double between 0 and 255.99 - static casting reduces to 0 -> 255.
    out << static_cast<int>(COLOUR_MULT_FACTOR * intensity.Clamps(r)) << ' ' 
        << static_cast<int>(COLOUR_MULT_FACTOR * intensity.Clamps(g)) << ' '
        << static_cast<int>(COLOUR_MULT_FACTOR * intensity.Clamps(b)) << "\n";
}

#endif