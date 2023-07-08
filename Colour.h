#ifndef COLOUR_H
#define COLOUR_H

#include "Vec3.h"

#include <iostream>

const double COLOUR_MULT_FACTOR = 255.99;

void WriteColour(std::ostream& out, Colour pixelColour)
{
    // Write the translated [0, 255] value of each colour component.
    // Multiply by COLOUR_MULT_FACTOR to get a double between 0 and 255.99 - static casting reduces to 0 -> 255.
    out << static_cast<int>(COLOUR_MULT_FACTOR * pixelColour.X()) << ' ' 
        << static_cast<int>(COLOUR_MULT_FACTOR * pixelColour.Y()) << ' '
        << static_cast<int>(COLOUR_MULT_FACTOR * pixelColour.Z()) << "\n";
}

#endif