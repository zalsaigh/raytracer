#ifndef INTERVAL_H
#define INTERVAL_H

#include "Utils.h"

class Interval
{
  public:
    double mMin, mMax;

    Interval() : mMin(+infinity), mMax(-infinity) {} // Default interval is empty

    Interval(double _min, double _max) : mMin(_min), mMax(_max) {}

    bool Contains(double x) const
    {
      return mMin <= x && mMax >= x;
    }

    bool Surrounds(double x) const
    {
      return mMin < x && mMax > x;
    }

    double Clamps(double x) const
    {
      if (x < mMin) return mMin;
      if (x > mMax) return mMax;
      return x;
    }

    static const Interval sEmpty, sUniverse;
};

const static Interval sEmpty();
const static Interval sUniverse(-infinity, infinity);

#endif