#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"

#include <iostream>

const double COLOUR_MULT_FACTOR = 255.99;

void WriteColour(std::ostream& out, Colour pixelColour)
{
    // Write the translated [0, 255] value of each colour component.
    // Multiply by COLOUR_MULT_FACTOR to get a double between 0 and 255.99 - static casting reduces to 0 -> 255.
    out << static_cast<int>(COLOUR_MULT_FACTOR * pixelColour.x()) << ' ' 
        << static_cast<int>(COLOUR_MULT_FACTOR * pixelColour.y()) << ' '
        << static_cast<int>(COLOUR_MULT_FACTOR * pixelColour.z()) << "\n";
}

#endif